/*
 * comphttpserver.cpp
 *
 *  Created on: 2015. 9. 29.
 *      Author: hwang
 */

#include "comphttpserver.hpp"
#include "../../include/componentpack.hpp"
#include "libhttpserver.hpp"

COMPONENT_INSTANCE(comphttpserver)
COMPONENT_CREATE(comphttpserver)
COMPONENT_DESTROY

comphttpserver::comphttpserver()
:interface::icomponent(COMPONENT(comphttpserver)) {
	// TODO Auto-generated constructor stub

}

comphttpserver::~comphttpserver() {
	// TODO Auto-generated destructor stub
}

bool comphttpserver::setup()
{
	return true;
}

bool comphttpserver::run()
{
	if(!_libhttpserver)
		_libhttpserver = new libhttpserver();

	if(!_server_task)
		_server_task = create_task(comphttpserver::server_run);

	return true;
}

bool comphttpserver::stop()
{
	destroy_task(_server_task);

	if(_libhttpserver) {
		delete _libhttpserver;
		_libhttpserver = nullptr;
	}

	return true;
}

void comphttpserver::request(cossb::message::message* msg)
{

}

void comphttpserver::server_run()
{
	if(_libhttpserver)
	{
		cossb_log->log(log::loglevel::INFO, "HTTP server is running...");
		_libhttpserver->run();
	}
}
