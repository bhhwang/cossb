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
#include "arch/singleton.hpp"

using namespace std;

namespace cossb {
namespace manager {

/**
 * @brief	component manager derived from singleton pattern
 */

class component_manager : public arch::singleton<component_manager> {
public:
	component_manager() { }
	virtual ~component_manager() { }

	bool install(const char* component_name);
	types::returntype uninstall(const char* component_name);
	types::returntype run(const char* component_name);
	types::returntype run();
	types::returntype stop(const char* component_name);
	types::returntype stop();

	int count();

};

#define cossb_component_manager	cossb::manager::component_manager::instance()

/**
 * @brief	system manager derived from singleton pattern
 */
class system_manager : public arch::singleton<system_manager> {

public:
	system_manager();
	virtual ~system_manager();
	/**
	 * @brief	setup system configuration
	 */
	bool setup(base::config* config);

	/**
	 * @brief	check configured or not
	 */
	bool is_setup() const;


private:
	bool initialized = false;
};

#define cossb_system_manager	cossb::manager::system_manager::instance()


} /* namespace manager */
} /* namespace cossb */

#endif
