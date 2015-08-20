/**
 * @file		sysmanager.cpp
 * @brief		COSSB system manager
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 7. 29
 * @details
 */

#include "manager.hpp"
#include "logger.hpp"
#include "interface/ilog.hpp"
#include "base/libadopter.hpp"

namespace cossb {
namespace manager {

system_manager::system_manager()
{

}

system_manager::~system_manager()
{
	cossb_component_manager->destroy();
	cossb_log->destroy();

	if(_log_adopter)	delete _log_adopter;
}

bool system_manager::setup(base::configreader* config)
{
	//1. load log library
	for(auto dep:*config->get_library()) {
		if(!dep->use.compare("log")) {
			_log_adopter = new base::libadopter<interface::ilog>(dep->sofile.c_str());
			cossb_log->adopt(_log_adopter->get_lib());
		}
	}


	//2. load dependent components
	for(auto dep:*config->get_dependency()) {
		if(dep->type==base::dependencyType::COMPONENT)
			cossb_component_manager->install(dep->name.c_str());
	}

	return true;
}

bool system_manager::is_setup() const
{
	return initialized;
}


} /* namespace manager */
} /* namespace cossb */
