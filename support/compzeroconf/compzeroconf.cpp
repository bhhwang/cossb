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

COMPONENT_INSTANCE(compzeroconf)
COMPONENT_CREATE(compzeroconf)
COMPONENT_DESTROY

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
		_browse_task = create_task(compzeroconf::browse_task);

	return true;
}

bool compzeroconf::stop()
{
	destroy_task(_browse_task);

	return true;
}

void compzeroconf::request(cossb::message::message* msg)
{

}

void compzeroconf::browse_task()
{
	_zeroconf = new libzeroconf();
	_zeroconf->browse("local", IPVersion::IPV4, on_change);

	cossb_log->log(log::loglevel::INFO, "browse services");
	if(_zeroconf) {
		delete _zeroconf;
		_zeroconf = nullptr;
	}


}

void compzeroconf::on_change()
{

}
