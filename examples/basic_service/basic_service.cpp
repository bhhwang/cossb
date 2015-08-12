#include "basic_service.hpp"

using namespace std;

COMPONENT_INSTANCE(basic_service)
COMPONENT_CREATE(basic_service)
COMPONENT_DESTROY

basic_service::basic_service()
:icomponent(COMPONENT(basic_service))
{
	cossb_log->info("create basic service instance");
}
basic_service::~basic_service()
{
	cossb_log->info("destroy basic service instance");
}

bool basic_service::setup()
{
	cossb_log->info("basic service call : setup");
	return false;
}
bool basic_service::run()
{
	cossb_log->info("basic service call : run");
	return false;
}
bool basic_service::stop()
{
	cossb_log->info("basic service call : stop");
	return false;
}
void basic_service::request(cossb::interface::imessage* msg)
{
	cossb_log->info("basic service call : request");
}
