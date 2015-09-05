
#include "helloworld.hpp"
#include "../../include/componentpack.hpp"

using namespace std;

COMPONENT_INSTANCE(hello_world)
COMPONENT_CREATE(hello_world)
COMPONENT_DESTROY

hello_world::hello_world()
:icomponent(COMPONENT(hello_world))
{

}
hello_world::~hello_world()
{

}

bool hello_world::setup()
{
	cossb_log->log(cossb::log::loglevel::INFO, "called hello world setup");
	return true;
}
bool hello_world::run()
{
	cossb_log->log(cossb::log::loglevel::INFO, "called hello world run");
	return true;
}
bool hello_world::stop()
{
	cossb_log->log(cossb::log::loglevel::INFO, "called hello world stop");
	return true;
}
void hello_world::request(cossb::interface::imessage* msg)
{
	cossb_log->log(cossb::log::loglevel::INFO, "called hello world request");
}
