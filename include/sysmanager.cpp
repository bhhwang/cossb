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
	for(auto dep:config->get_required()) {

		//1. pre-load log library
		if(!dep->usefor.compare("log") && !dep->name.empty()) {
			string prefix = config->get_path()["library"];
			if(prefix.empty()) prefix = "./";

			_log_adopter = new base::libadopter<interface::ilog>((prefix+dep->name).c_str());
			cossb_log->adopt(_log_adopter->get_lib());
			cossb_log->log(log::loglevel::INFO, fmt::format("Load library : {}", dep->name).c_str());
		}
	}

	//2. pre-load package after loading libraries
	for(auto dep:config->get_required()) {
		if(dep->type==base::bundleType::PACKAGE) {

		}
	}

	//3. pre-load components after loading libraries
	for(auto dep:config->get_required()) {
		if(dep->type==base::bundleType::COMPONENT) {
			cossb_component_manager->install(dep->name.c_str());
		}
	}

	return true;
}

} /* namespace manager */
} /* namespace cossb */
