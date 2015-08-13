#include "basic_service.hpp"
#include "../../include/component_util.hpp"

using namespace std;

COMPONENT_INSTANCE(basic_service)
COMPONENT_CREATE(basic_service)
COMPONENT_DESTROY

basic_service::basic_service()
:icomponent(COMPONENT(basic_service))
{
	//cossb_log->log("sample");
	//logger()->info("create basic service instance");
}
basic_service::~basic_service()
{
	//logger()->info("destroy basic service instance");
}

bool basic_service::setup()
{
	//logger()->info("basic service call : setup");
	return false;
}
bool basic_service::run()
{
	//logger()->info("basic service call : run");
	return false;
}
bool basic_service::stop()
{
	//logger()->info("basic service call : stop");
	return false;
}
void basic_service::request(cossb::interface::imessage* msg)
{
	//logger()->info("basic service call : request");
}
