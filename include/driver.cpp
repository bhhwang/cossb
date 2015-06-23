/**
 * @file		driver.cpp
 * @brief		Component driver
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Load components with driver
 */

#include "driver.hpp"
#include <dlfcn.h>
#include "util/spdlog/spdlog.h"

namespace cossb {
namespace driver {

component_driver::component_driver(const char* component_name)
:_component_name(component_name)
{
	if(load(component_name))
	{

	}
	else
		spdlog::get(_component_name)->error("Cannot load {}", component_name);
}

component_driver::~component_driver()
{

}

bool component_driver::load(const char* component_name)
{
	string comp_path = "./"+string(component_name);

	_handle = dlopen(comp_path.c_str(), RTLD_LAZY|RTLD_GLOBAL);

	if(!_handle)
	{
		spdlog::get("main_thread")->error("{}", dlerror());
		return false;
	}
	else
	{
		create_component pfcreate = (create_component)dlsym(_handle, "create");
		if(!pfcreate)
		{
			spdlog::get("main_thread")->error("{}",dlerror());

			dlclose(_handle);
			_handle = nullptr;

			return false;
		}
		else
		{
			_ptr_component = pfcreate();
			return true;
		}
	}
}

void component_driver::unload()
{

}

} /* namespace dirver */
} /* namespace cossb */
