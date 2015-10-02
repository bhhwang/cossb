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
	if(!_libhttpserver) {
		const int port = 8888;
		_libhttpserver = new libhttpserver(port);
		cossb_log->log(log::loglevel::INFO, fmt::format("HTTP server is running on port {}",port).c_str());
		_libhttpserver->run();
	}

	return true;
}

bool comphttpserver::stop()
{

	if(_libhttpserver) {
		delete _libhttpserver;
		_libhttpserver = nullptr;
	}

	return true;
}

void comphttpserver::request(cossb::message::message* msg)
{

}
