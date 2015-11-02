
#include "helloworld.hpp"
#include "../../include/componentpack.hpp"
#include <ext/json.hpp>

using namespace std;

USE_COMPONENT_INTERFACE(helloworld)

helloworld::helloworld()
:icomponent(COMPONENT(helloworld))
{

}

helloworld::~helloworld()
{

}

bool helloworld::setup()
{
	return true;
}
bool helloworld::run()
{

	return true;
}
bool helloworld::stop()
{
	return true;
}

void helloworld::request(cossb::message::message* msg)
{
	cossb_log->log(cossb::log::loglevel::INFO, msg->get_from());
	cossb_log->log(cossb::log::loglevel::INFO, "hello world");
}


