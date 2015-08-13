/**
 * @file		driver.cpp
 * @brief		Component driver
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Load components with driver
 */

#include "driver.hpp"
#include <dlfcn.h>
#include "xmlprofile.hpp"
#include <iostream>
#include "logger.hpp"
#include "util/format.h"

using namespace std;

namespace cossb {
namespace driver {

component_driver::component_driver(const char* component_name)
:_component_name(component_name)
{
	if(load(component_name))
	{
		//1. profile setting
		string profile_path = fmt::format("./{}.xml",component_name);
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
	string component_path = fmt::format("./{}.comp",component_name);

	_handle = dlopen(component_path.c_str(), RTLD_LAZY|RTLD_GLOBAL);

	if(_handle)
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

	return false;
}

void component_driver::setup()
{
	if(_ptr_component)
		_ptr_component->setup();
}

void component_driver::unload()
{
	if(_ptr_component)
	{
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

void component_driver::run()
{
	if(_ptr_component)
		_ptr_component->run();
}

void component_driver::stop()
{
	if(_ptr_component)
		_ptr_component->stop();
}

bool component_driver::set_profile(interface::iprofile* profile, const char* path)
{
	return false;
}


} /* namespace dirver */
} /* namespace cossb */
