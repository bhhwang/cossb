/**
 * @file		driver.cpp
 * @brief		Component driver
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Load components with driver
 */

#include "driver.hpp"
#include <dlfcn.h>
#include <iostream>
#include "xmlprofile.hpp"
#include "logger.hpp"
#include "util/format.h"
#include <tuple>
#include "message.hpp"
#include "broker.hpp"
#include "exception.hpp"

using namespace std;

namespace cossb {
namespace driver {

component_driver::component_driver(const char* component_path)
{
	try {
		if(load(component_path))
		{
			string profile_path = fmt::format("{}.xml",component_path);

			if(_ptr_component) {
				_ptr_component->_profile = new profile::xmlprofile();
				if(!_ptr_component->_profile->load(profile_path.c_str()))
					unload();
				else
					regist_service_desc();
			}
		}
		else
			throw exception(excode::COMPONENT_LOAD_FAIL);
	}
	catch(driver::exception& e) {
		cossb_log->log(log::loglevel::ERROR, e.what(), log::color::COLOR);
	}
}

component_driver::~component_driver()
{
	try {
		unload();
	}
	catch(driver::exception& e) {
		cossb_log->log(log::loglevel::ERROR, e.what(), log::color::COLOR);
	}
}

bool component_driver::load(const char* component_path)
{
	string fullpath = fmt::format("{}.comp",component_path);

	_handle = dlopen(fullpath.c_str(), RTLD_LAZY|RTLD_GLOBAL);

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
	else
		throw exception(excode::COMPONENT_OPEN_ERROR, dlerror());

	return false;
}

void component_driver::unload()
{
	if(_ptr_component)
	{
		destroy_component pfdestroy = (destroy_component)dlsym(_handle, "destroy");

		destroy_task(_request_proc_task);

		if(pfdestroy) {
			pfdestroy();
		}
		else
			throw exception(excode::COMPONENT_UNLOAD_FAIL);

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
	if(_ptr_component) {
		_ptr_component->setup();
	}
}

void component_driver::run()
{
	if(_ptr_component)
	{
		if(!_request_proc_task) {
			_request_proc_task = create_task(component_driver::request_proc);
		}

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
	if(_ptr_component)
	{
		while(1)
		{
			try
			{
				boost::mutex::scoped_lock lock(_mutex);

				while(_mailbox.empty())
					_condition.wait(lock);

				while(!_mailbox.empty()) {
					_ptr_component->request(&_mailbox.front());
					_mailbox.pop();
				}

				boost::this_thread::sleep(boost::posix_time::milliseconds(1));
			}
			catch(thread_interrupted&) {
				break;
			}
		}
	}
}

void component_driver::regist_service_desc()
{
	if(_ptr_component) {
		interface::iprofile* profile = _ptr_component->get_profile();
		if(profile) {
			cossb_log->log(log::loglevel::INFO, fmt::format("{} has {} services", _ptr_component->get_name(), profile->get_service_descs()->size()).c_str());
			for(auto svc:*profile->get_service_descs()){
				cossb_broker->regist(_ptr_component, svc.topic);
			}
		}
	}
}



} /* namespace dirver */
} /* namespace cossb */
