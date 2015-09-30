
#include "messagepub.hpp"
#include "../../include/componentpack.hpp"

using namespace std;

COMPONENT_INSTANCE(messagepub)
COMPONENT_CREATE(messagepub)
COMPONENT_DESTROY

messagepub::messagepub()
:icomponent(COMPONENT(messagepub)){
	// TODO Auto-generated constructor stub

}

messagepub::~messagepub() {
	destroy_task(_pub_task);
}


bool messagepub::setup()
{
	cossb_broker->regist(this, "service/messagepub");
	return true;
}
bool messagepub::run()
{
	if(!_pub_task)
		_pub_task = create_task(messagepub::pub);
	return true;
}
bool messagepub::stop()
{
	destroy_task(_pub_task);
	return true;
}
void messagepub::request(cossb::message::message* msg)
{
	cossb_log->log(cossb::log::loglevel::INFO, "received message");
}

void messagepub::pub()
{
	while(1)
	{
		try {
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

		vector<unsigned char> data;
		data.push_back('a');
		try {
			cossb_broker->publish(this, "service/messagepub", "raw", data);
		} catch(cossb::broker::exception& e) {
			cossb_log->log(cossb::log::loglevel::ERROR, fmt::format("{}", e.what()).c_str());
		}
		}
		catch(thread_interrupted&)
		{
			break;
		}
	}
}
