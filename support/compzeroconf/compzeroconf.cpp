/*
 * compzeroconf.cpp
 *
 *  Created on: 2015. 9. 12.
 *      Author: hwang
 */

#include "compzeroconf.hpp"
#include "../../include/componentpack.hpp"
#include "libzeroconf.hpp"
#include <vector>
#include <string>

using namespace std;

USE_COMPONENT_INTERFACE(compzeroconf)

compzeroconf::compzeroconf()
:interface::icomponent(COMPONENT(compzeroconf)){
	// TODO Auto-generated constructor stub

}

compzeroconf::~compzeroconf() {

	if(_zeroconf) {
		delete _zeroconf;
		_zeroconf = nullptr;
	}
}

bool compzeroconf::setup()
{
	return true;
}

bool compzeroconf::run()
{
	if(!_browse_task)
	{
		_zeroconf = new libzeroconf();
		_browse_task = create_task(compzeroconf::browse_task);
	}

	return true;
}

bool compzeroconf::stop()
{
	if(_zeroconf) {
		delete _zeroconf;
		_zeroconf = nullptr;
	}

	destroy_task(_browse_task);
	return true;
}

void compzeroconf::request(cossb::message::message* msg) const
{

}

void compzeroconf::browse_task()
{
	if(_zeroconf) {
		_zeroconf->browse("local", IProtocol::IPV4, compzeroconf::on_change);
	}
}

void compzeroconf::on_change()
{
	cossb_log->log(log::loglevel::INFO, "on change event occurred");
}
