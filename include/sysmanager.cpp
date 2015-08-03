/**
 * @file		sysmanager.cpp
 * @brief		COSSB system manager
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 7. 29
 * @details
 */

#include "manager.hpp"
#include "configloader.hpp"

namespace cossb {
namespace manager {

system_manager* system_manager::_instance = nullptr;

system_manager* system_manager::get()
{
	if(!_instance)
		_instance = new system_manager;
	return _instance;
}

void system_manager::destroy()
{
	if(_instance)
		delete _instance;
}

bool system_manager::setup(base::config* config)
{
	//1. read config file

	//2. setup the configuration to the database

	//3.run the default servers

	return true;
}

bool system_manager::is_setup() const
{
	return initialized;
}


} /* namespace manager */
} /* namespace cossb */
