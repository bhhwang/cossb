
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
	// TODO Auto-generated destructor stub
}


bool messagepub::setup()
{
	cossb_log->log(cossb::log::loglevel::INFO, "called hello world setup");
	return true;
}
bool messagepub::run()
{
	cossb_log->log(cossb::log::loglevel::INFO, "called hello world run");
	return true;
}
bool messagepub::stop()
{
	cossb_log->log(cossb::log::loglevel::INFO, "called hello world stop");
	return true;
}
void messagepub::request(cossb::interface::imessage* msg)
{
	cossb_log->log(cossb::log::loglevel::INFO, "called hello world request");
}
