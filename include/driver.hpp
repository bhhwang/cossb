/**
 * @file		driver.hpp
 * @brief		Component driver
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Load components with driver
 */

#ifndef _COSSB_DRIVER_HPP_
#define _COSSB_DRIVER_HPP_

#include <string>
#include "interface/icomponent.hpp"

using namespace std;

namespace cossb {
namespace driver {

class component_driver : private interface::icomponent {

	friend class manager::component_manager;

public:
	component_driver(const char* component_name);
	virtual ~component_driver();

	bool valid() { return _handle!=nullptr; }
	interface::icomponent* get_component() const { return _ptr_component; };

private:
	bool load(const char* component_name);
	void unload();

	//component interface
	void run();
	void stop();


private:
	interface::icomponent* _ptr_component = nullptr;
	void* _handle = nullptr;
	string _component_name;
};

} /* namespace driver */
} /* namespace cossb */

#endif
