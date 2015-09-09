/**
 * @file		broker.hpp
 * @brief		Component Broker
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details
 */

#ifndef _COSSB_BROKER_HPP_
#define _COSSB_BROKER_HPP_

#include <map>
#include <string>
#include "interface/icomponent.hpp"
#include "arch/singleton.hpp"
#include "manager.hpp"

using namespace std;

namespace cossb {
namespace broker {

//(topic, component name) pair
typedef multimap<string, string> topic_map;

class component_broker : public arch::singleton<component_broker> {
public:
	component_broker();
	virtual ~component_broker();

	/**
	 *@brief	regist component with topic
	 */
	bool regist(interface::icomponent* component, string topic_name);

	template<typename... Args>
	bool publish(interface::icomponent* component, const char* to_topic, const char* api, const Args&... args);

	/*template<typename... Args>
	error::errorcode publish(const char* component_name, const char* to_topic, const char* api, const Args&... args) {
		error::errorcode code = error::errorcode::PLUN_NO_ERROR;
		if(_instance) {
			auto range = _topic_map.equal_range(to_topic);
			for(topic_map::iterator itr = range.first; itr!=range.second; ++itr) {
				if(itr->second.compare(component_name)!=0) {
					manager::component_manager::get()->get_driver(itr->second.c_str())->request(api, args...);
				}
			}
		}

		return code;
	}*/

private:
	topic_map	_topic_map;
};

#define cossb_broker		cossb::broker::component_broker::instance()

} /* namespace broker */
} /* namespace cossb */

#endif
