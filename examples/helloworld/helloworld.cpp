
#include "helloworld.hpp"
#include "../../include/component_util.hpp"

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
	return true;
}
bool hello_world::run()
{
	return true;
}
bool hello_world::stop()
{
	return true;
}
void hello_world::request(cossb::interface::imessage* msg)
{

}
