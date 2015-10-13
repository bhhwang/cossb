
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
	destroy_task(_task);
}

bool hello_world::setup()
{
	return true;
}
bool hello_world::run()
{
	if(!_task)
		_task = create_task(hello_world::hellotask);
	return true;
}
bool hello_world::stop()
{
	destroy_task(_task);
	return true;
}

void hello_world::request(cossb::message::messageframe* msg)
{
	cossb_log->log(cossb::log::loglevel::INFO, "received message");
}

void hello_world::hellotask()
{
	while(1)
	{
		cossb_log->log(cossb::log::loglevel::INFO, "hello world~");
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	}
}
