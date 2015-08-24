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

	if(!_lib_container.empty()) {
		for(auto srv:_lib_container)
			delete srv.second;
		_lib_container.clear();
	}

	if(_log_adopter)	delete _log_adopter;
}

bool system_manager::setup(base::configreader* config)
{
	//1. load log library
	for(auto dep:*config->get_required()) {
		if(!dep->usefor.compare("log") && !dep->name.empty()) {
			_log_adopter = new base::libadopter<interface::ilog>(dep->name.c_str());
			cossb_log->adopt(_log_adopter->get_lib());
			cossb_log->log(log::loglevel::INFO, fmt::format("Load library : {}", dep->name).c_str());
		}
	}

	//2. load service library
	for(auto dep:*config->get_service()) {
		if(!dep.first.empty() && !dep.second.empty()) {
			_lib_container.insert(std::pair<string, base::libadopter<interface::iobject>*>(dep.first, new base::libadopter<interface::iobject>(dep.second.c_str())));
			cossb_log->log(log::loglevel::INFO, fmt::format("Load service : {}", dep.second).c_str());
		}
	}

	//3. load dependent components
	for(auto dep:*config->get_required()) {
		if(dep->type==base::requiredType::COMPONENT)
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
