/**
 * @file		manager.hpp
 * @brief		COSSB component manager
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details
 */

#ifndef _COSSB_MANAGER_HPP_
#define _COSSB_MANAGER_HPP_

#include "config.hpp"
#include "typedef.hpp"
#include <map>
#include <vector>

using namespace std;

namespace cossb {
namespace manager {

/**
 * @brief	component management
 */

class component_manager {
public:
	static component_manager* get();
	void destroy();

	types::returntype install(const char* component_name);
	types::returntype uninstall(const char* component_name);
	types::returntype run(const char* component_name);
	types::returntype stop(const char* component_name);

	int count();

private:
	static component_manager* _instance;

};

/**
 * @brief	system management (global configuration)
 */
class system_manager {
public:
	static system_manager* get();
	void destroy();

	/**
	 * @brief	setup system configuration
	 */
	bool setup(base::config* config);

	/**
	 * @brief	check configured or not
	 */
	bool is_setup() const;

private:
	static system_manager* _instance;
	bool initialized = false;
};


} /* namespace manager */
} /* namespace cossb */

#endif
