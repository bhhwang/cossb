/**
 * @file		compmanager.cpp
 * @brief		COSSB component manager
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details
 */

#include "manager.hpp"

namespace cossb {
namespace manager {

component_manager* component_manager::_instance = nullptr;

component_manager* component_manager::get()
{
	if(!_instance)
		_instance = new component_manager;
	return _instance;
}

void component_manager::destroy()
{
	if(_instance)
		delete _instance;
}

types::returntype component_manager::install(const char* component_name)
{
	return types::returntype::SUCCESS;
}

types::returntype component_manager::uninstall(const char* component_name)
{
	return types::returntype::SUCCESS;
}

types::returntype component_manager::run(const char* component_name)
{
	return types::returntype::SUCCESS;
}

types::returntype component_manager::stop(const char* component_name)
{
	return types::returntype::SUCCESS;
}

int component_manager::count()
{
	return 0;
}

} /* namespace manager */
} /* namespace cossb */
