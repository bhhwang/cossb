/*
 * comphttpserver.cpp
 *
 *  Created on: 2015. 9. 29.
 *      Author: hwang
 */

#include "comphttpserver.hpp"
#include "../../include/componentpack.hpp"

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
	return true;
}

bool comphttpserver::stop()
{
	return true;
}

void comphttpserver::request(cossb::message::message* msg)
{

}
