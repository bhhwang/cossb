/**
 * @file		driver.hpp
 * @brief		Component driver
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Load components with driver and their own peripheral instances
 */

#ifndef _COSSB_DRIVER_HPP_
#define _COSSB_DRIVER_HPP_

#include <string>
#include "interface/icomponent.hpp"
#include "interface/iprofile.hpp"
#include "interface/ilog.hpp"
#include "manager.hpp"

using namespace std;

namespace cossb {
namespace driver {

class component_driver {

	friend class manager::component_manager;

public:
	component_driver(const char* component_name);
	virtual ~component_driver();

	/**
	 * @brief	component validation for driving
	 */
	bool valid() { return _handle!=nullptr; }

	/**
	 * @brief	getting component pointer to access
	 */
	interface::icomponent* get_component() const { return _ptr_component; };

	/**
	 * @brief	redefine operator
	 */
	//virtual interface::icomponent* operator->() { return _ptr_component; }
	//virtual interface::icomponent& operator*() { return *_ptr_component; }

private:

	/**
	 * @brief	setup component
	 */
	void setup();

	/**
	 * @brief	run component
	 */
	void run();

	/**
	 * @brief	stop component
	 */
	void stop();

	/**
	 * @brief	load component by name
	 */
	bool load(const char* component_name);

	/**
	 * @brief	unload component
	 */
	void unload();

	/**
	 * @brief	component profile setup
	 */
	bool set_profile(interface::iprofile* profile, const char* path);


private:
	interface::icomponent* _ptr_component = nullptr;
	void* _handle = nullptr;
	string _component_name;
};

} /* namespace driver */
} /* namespace cossb */

#endif
