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

using namespace std;

namespace cossb {
namespace driver {

class component_driver {
public:
	component_driver(const char* component_name);
	virtual ~component_driver();

	interface::icomponent* get_component() const;

private:
	bool load(const char* component_name);
	void unload();

private:
	interface::icomponent* _ptr_component = nullptr;
	void* _handle = nullptr;
	string _component_name;
};

} /* namespace driver */
} /* namespace cossb */

#endif
