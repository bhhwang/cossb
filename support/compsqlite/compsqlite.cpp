/*
 * compsqlite.cpp
 *
 *  Created on: 2015. 9. 29.
 *      Author: hwang
 */

#include "compsqlite.hpp"
#include "../../include/componentpack.hpp"

USE_COMPONENT_INTERFACE(compsqlite)

compsqlite::compsqlite()
:interface::icomponent(COMPONENT(compsqlite)){
	// TODO Auto-generated constructor stub

}

compsqlite::~compsqlite() {
	// TODO Auto-generated destructor stub
}

bool compsqlite::setup()
{
	return true;
}

bool compsqlite::run()
{
	return true;
}

bool compsqlite::stop()
{
	return true;
}

void compsqlite::request(cossb::message::message* msg)
{

}
