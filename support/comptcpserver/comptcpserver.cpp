/*
 * comptcpserver.cpp
 *
 *  Created on: Aug 26, 2015
 *      Author: odroid
 */

#include "comptcpserver.hpp"
#include "../../include/component_util.hpp"

COMPONENT_INSTANCE(comptcpserver)
COMPONENT_CREATE(comptcpserver)
COMPONENT_DESTROY

comptcpserver::comptcpserver()
{

}

comptcpserver::~comptcpserver()
{

}

bool comptcpserver::setup()
{
	return true;
}

bool comptcpserver::run()
{
	return true;
}

bool comptcpserver::stop()
{
	return true;
}

void comptcpserver::request(cossb::interface::imessage* msg)
{

}
