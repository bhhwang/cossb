#include "basic_service.hpp"

COMPONENT_INSTANCE(basic_service)
COMPONENT_CREATE(basic_service)
COMPONENT_DESTROY

basic_service::basic_service()
:icomponent(COMPONENT(basic_service))
{

}
basic_service::~basic_service()
{

}

bool basic_service::setup()
{
	return false;
}
bool basic_service::run()
{
	return false;
}
bool basic_service::stop()
{
	return false;
}
void basic_service::request(imessage* msg)
{

}
