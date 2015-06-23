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

namespace cossb {
namespace manager {

class component_manager {
public:
	static component_manager* get();
	void destroy();

	types::returntype load_config(config* manifest);

	types::returntype install(const char* component_name);
	types::returntype uninstall(const char* component_name);
	types::returntype run(const char* component_name);
	types::returntype stop(const char* component_name);

	int count();

private:
	static component_manager* _instance;
	config* _conf = nullptr;

};


} /* namespace manager */
} /* namespace cossb */

#endif
