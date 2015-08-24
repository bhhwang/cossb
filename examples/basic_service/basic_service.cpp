#include "basic_service.hpp"
#include "../../include/component_util.hpp"

using namespace std;

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
	cout << "setup" << endl;
	return false;
}
bool basic_service::run()
{
	cout << "run" << endl;
	return false;
}
bool basic_service::stop()
{
	cout << "stop" << endl;
	return false;
}
void basic_service::request(cossb::interface::imessage* msg)
{
	cout << "request" << endl;
}
