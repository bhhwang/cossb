/**
 * @file		driver.hpp
 * @brief		Component driver
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Load components(shared library that support COSSB interface) and peripheral instances
 */

#ifndef _COSSB_DRIVER_HPP_
#define _COSSB_DRIVER_HPP_

#include <string>
#include <queue>
#include "interface/icomponent.hpp"
#include "interface/iprofile.hpp"
#include "interface/ilog.hpp"
#include "interface/imessage.hpp"
#include "manager.hpp"
#include "base/task.hpp"

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

	/**
	 * @brief	request message
	 */
	void request(interface::imessage* msg);

	/**
	 * @brief	request process task
	 */
	void request_proc();

	/**
	 * for test, insert message
	 */
	template<typename... Args>
	void query(const char* head, const Args&... args) {

	}

	/**
	 * @brief	request
	 */
	base::task		_request_proc_task;


private:
	interface::icomponent* _ptr_component = nullptr;

	void* _handle = nullptr;

	string _component_name;

	/**
	 * @brief	add mailbox
	 */
	std::queue<message::message> _mailbox;

	boost::condition_variable _condition;
	boost::mutex _mutex;

};

} /* namespace driver */
} /* namespace cossb */

#endif
