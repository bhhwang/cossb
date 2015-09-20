/*
 * compzeroconf.cpp
 *
 *  Created on: 2015. 9. 12.
 *      Author: hwang
 */

#include "compzeroconf.hpp"
#include "../../include/componentpack.hpp"
#include "libzeroconf.hpp"

COMPONENT_INSTANCE(compzeroconf)
COMPONENT_CREATE(compzeroconf)
COMPONENT_DESTROY

compzeroconf::compzeroconf()
:interface::icomponent(COMPONENT(compzeroconf)){
	// TODO Auto-generated constructor stub

}

compzeroconf::~compzeroconf() {
	// TODO Auto-generated destructor stub
}

bool compzeroconf::setup()
{
	_zeroconf = new libzeroconf();

	return true;
}

bool compzeroconf::run()
{
	if(_zeroconf) {
	_zeroconf->browse("_http._tcp","local");
	cossb_log->log(log::loglevel::INFO, "call browse function");
	}
	return true;
}

bool compzeroconf::stop()
{
	if(_zeroconf)
	{
		delete _zeroconf;
		_zeroconf = nullptr;
	}
	return true;
}

void compzeroconf::request(cossb::message::message* msg)
{

}
