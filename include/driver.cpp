/**
 * @file		driver.cpp
 * @brief		Component driver
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Load components with driver
 */

#include "driver.hpp"
#include <dlfcn.h>

namespace cossb {
namespace driver {

component_driver::component_driver(const char* component_name)
:_component_name(component_name)
{
	if(load(component_name))
	{
		string profile_path = "./"+string(component_name)+".xml";
		if(!_ptr_component->set_profile(new profile::xmlprofile, profile_path.c_str()))
			unload();
	}
}

component_driver::~component_driver()
{
	unload();
}

bool component_driver::load(const char* component_name)
{
	string comp_path = "./"+string(component_name);

	_handle = dlopen(comp_path.c_str(), RTLD_LAZY|RTLD_GLOBAL);

	if(!_handle)
		return false;
	else
	{
		create_component pfcreate = (create_component)dlsym(_handle, "create");
		if(!pfcreate)
		{

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
	if(_ptr_component)
	{
		string comp_name = _ptr_component->get_name();

		destroy_component pfdestroy = (destroy_component)dlsym(_handle, "destroy");

		if(pfdestroy)
			pfdestroy();

		_ptr_component = nullptr;
	}

	if(_handle)
	{
		dlclose(_handle);
		_handle = nullptr;
	}
}

} /* namespace dirver */
} /* namespace cossb */
