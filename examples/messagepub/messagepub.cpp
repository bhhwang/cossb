
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
	cossb_log->log(cossb::log::loglevel::INFO, "called messagepub setup");

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

}

void messagepub::pub()
{
	while(1)
	{
		cossb_log->log(cossb::log::loglevel::INFO, "message publish");
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	}
}
