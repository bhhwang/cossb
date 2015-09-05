
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
	if(!_pub_task)
		_pub_task = create_task(messagepub::pub);

	return true;
}
bool messagepub::run()
{
	cossb_log->log(cossb::log::loglevel::INFO, "called messagepub run");
	return true;
}
bool messagepub::stop()
{
	cossb_log->log(cossb::log::loglevel::INFO, "called messagepub stop");
	return true;
}
void messagepub::request(cossb::interface::imessage* msg)
{
	cossb_log->log(cossb::log::loglevel::INFO, "called messagepub request");
}

void messagepub::pub()
{

}
