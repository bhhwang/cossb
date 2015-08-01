/**
 * @file		config.CPP
 * @brief		Config file loader
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Load config file to run the engine
 */

#include "config.hpp"

namespace cossb {
namespace base {

config* config::_instance = nullptr;
config* config::get()
{
	if(!_instance)
		_instance = new config;
	return _instance;
}

void config::destroy()
{
	if(_instance)
		delete _instance;
}

bool config::load(const char* manifest_conf)
{
	return true;
}



} /* namespace base */
} /* namespace cossb */
