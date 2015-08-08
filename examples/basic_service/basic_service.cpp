#include "basic_service.hpp"
#include <iostream>

using namespace std;

COMPONENT_INSTANCE(basic_service)
COMPONENT_CREATE(basic_service)
COMPONENT_DESTROY

basic_service::basic_service()
:icomponent(COMPONENT(basic_service))
{
	cout << "create basic service instance" << endl;
}
basic_service::~basic_service()
{
	cout << "destroy basic service instance" << endl;
}

bool basic_service::setup()
{
	cout << "basic service call : setup" << endl;
	return false;
}
bool basic_service::run()
{
	cout << "basic service call : run" << endl;
	return false;
}
bool basic_service::stop()
{
	cout << "basic service call : stop" << endl;
	return false;
}
void basic_service::request(imessage* msg)
{
	cout << "basic service call : request" << endl;
}
