/**
 * @file		sysmanager.cpp
 * @brief		COSSB system manager
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 7. 29
 * @details
 */

#include "manager.hpp"
#include "logger.hpp"
#include "soloader.hpp"

namespace cossb {
namespace manager {

system_manager::system_manager()
{

}

system_manager::~system_manager()
{
	cossb_component_manager->destroy();
	cossb_log->destroy();
}

bool system_manager::setup(base::config* config)
{

	//1. load log library
	for(auto dep:*config->get_library()) {
		if(!dep->use.compare("log")) {
			cout << "load logger" << endl;
			cossb_log->_logger = base::soloader<interface::ilog>(dep->sofile.c_str()).load();
			cossb_log->log("this is test");

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
