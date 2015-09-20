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
	// TODO Auto-generated destructor stub
}

bool compzeroconf::setup()
{
	_zeroconf = new libzeroconf();

	return true;
}

bool compzeroconf::run()
{
	if(!_browse_task)
		_browse_task = create_task(compzeroconf::browse_task);

	if(_zeroconf)
	{
		_zeroconf->browse("_http._tcp","local");
		vector<string>* _list = _zeroconf->get_service_types("local");

		cossb_log->log(log::loglevel::INFO, fmt::format("found list : {}", _list->size()).c_str());
		cossb_log->log(log::loglevel::INFO, "call browse function");
	}

	return true;
}

bool compzeroconf::stop()
{
	destroy_task(_browse_task);

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

void compzeroconf::browse_task()
{
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
}
