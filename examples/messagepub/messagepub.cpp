
#include "messagepub.hpp"
#include "../../include/componentpack.hpp"

using namespace std;

USE_COMPONENT_INTERFACE(messagepub)

template <typename T, size_t N>
T* _begin(T(&arr)[N]) { return &arr[0]; }
template <typename T, size_t N>
T* _end(T(&arr)[N]) { return &arr[0]+N; }

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
	/*while(1)
	{
		try {
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

		char packet[] = {255, 0, 0};
		vector<char> data(_begin(packet), _end(packet));

		try {
			int a = cossb_broker->publish(this, "service/mbed_rgb", "rgb", data);
			cossb_log->log(cossb::log::loglevel::INFO, fmt::format("sent : {}",a).c_str());

			cossb_log->log(cossb::log::loglevel::INFO, "sent message");
		} catch(cossb::broker::exception& e) {
			cossb_log->log(cossb::log::loglevel::ERROR, fmt::format("{}", e.what()).c_str());
		}
		}
		catch(thread_interrupted&)
		{
			break;
		}
	}*/
}
