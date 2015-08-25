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
		string profile_path = fmt::format("./{}.xml",component_name);
		if(!_ptr_component->set_profile(new profile::xmlprofile, profile_path.c_str()))
			unload();
		else
			cossb_log->log(cossb::log::loglevel::INFO, fmt::format("Component load success : {}", component_name).c_str());
	}
	else
		cossb_log->log(cossb::log::loglevel::ERROR, fmt::format("Component load failed : {}", component_name).c_str());
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

		_ptr_component = pfcreate();
		return true;
	}

	return false;
}

void component_driver::unload()
{
	if(_ptr_component)
	{
		destroy_component pfdestroy = (destroy_component)dlsym(_handle, "destroy");

		destroy_task(_request_proc_task);

		if(pfdestroy) {
			cossb_log->log(cossb::log::loglevel::INFO, fmt::format("Component unload success : {}", _ptr_component->get_name()).c_str());
			pfdestroy();
		}

		_ptr_component = nullptr;
	}

	if(_handle)
	{
		dlclose(_handle);
		_handle = nullptr;
	}
}

void component_driver::setup()
{
	if(_ptr_component)
		_ptr_component->setup();
}

void component_driver::run()
{
	if(_ptr_component)
	{
		if(!_request_proc_task)
			_request_proc_task = create_task(component_driver::request_proc);

		_ptr_component->run();
	}

}

void component_driver::stop()
{
	if(_ptr_component)
		_ptr_component->stop();

	destroy_task(_request_proc_task);
}

bool component_driver::set_profile(interface::iprofile* profile, const char* path)
{
	return true;
}

void component_driver::request_proc()
{
	if(_ptr_component) {
		while(1)
		{
			boost::mutex::scoped_lock __lock(_mutex);
			_condition.wait(__lock);

			while(!_mailbox.empty()) {
				_ptr_component->request(&_mailbox.front());
				_mailbox.pop();
			}

			boost::this_thread::sleep(boost::posix_time::milliseconds(0));
		}
	}
}


} /* namespace dirver */
} /* namespace cossb */
