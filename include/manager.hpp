/**
 * @file		manager.hpp
 * @brief		COSSB component manager
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details
 */

#ifndef _COSSB_MANAGER_HPP_
#define _COSSB_MANAGER_HPP_

#include "typedef.hpp"
#include <map>
#include <vector>
#include <string>
#include "arch/singleton.hpp"
#include "base/configreader.hpp"

using namespace std;

namespace cossb {
namespace base { template<class T> class libadopter; }
namespace interface {
	class ilog;
	class isimpleservice;
}
namespace manager {

/**
 * @brief	component manager derived from singleton pattern
 */

class component_manager : public arch::singleton<component_manager> {
public:
	component_manager();
	virtual ~component_manager();

	component_manager(const component_manager&) = delete;
	component_manager& operator = (const component_manager&) = delete;

	/**
	 * @brief	install specific component
	 */
	bool install(const char* component_name);

	/**
	 * @brief	uninstall specific component
	 */
	types::returntype uninstall(const char* component_name);
	types::returntype uninstall();


	/**
	 * @brief run specific component
	 */
	types::returntype run(const char* component_name);

	/**
	 * @brief run all components
	 */
	types::returntype run();

	/**
	 * @brief	stop specific component
	 */
	types::returntype stop(const char* component_name);

	/**
	 * @brief	stop all components
	 */
	types::returntype stop();

	/**
	 * @brief	get count of the installed components
	 */
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

	system_manager(const system_manager&) = delete;
	system_manager& operator = (const system_manager&) = delete;

	/**
	 * @brief	setup system configuration
	 */
	bool setup(base::configreader* config);

	/**
	 * @brief	check configured or not
	 */
	bool is_setup() const;


private:
	bool initialized = false;

	/**
	 * @brief	dependent libraries adopter
	 */
	base::libadopter<interface::ilog>* _log_adopter = nullptr;

	/**
	 * @brief	mdns library adopter
	 */
	base::libadopter<interface::isimpleservice>* _mdns_adopter = nullptr;
	map<std::string, base::libadopter<interface::isimpleservice>*> _srv_container;



};

#define cossb_system_manager	cossb::manager::system_manager::instance()


} /* namespace manager */
} /* namespace cossb */

#endif
