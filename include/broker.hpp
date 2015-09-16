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
#include "logger.hpp"

using namespace std;

namespace cossb {
namespace broker {

//(topic, component name) pair
typedef multimap<string, string> topic_map;

class component_broker : public arch::singleton<component_broker> {
public:
	component_broker() { };
	virtual ~component_broker() { };

	/**
	 *@brief	regist component with topic
	 */
	bool regist(interface::icomponent* component, string topic_name) {
		_topic_map.insert(topic_map::value_type(topic_name, component->get_name()));
		return true;
	}

	/**
	 * @brief	publish data pack to specific service component
	 */
	template<typename... Args>
	bool publish(interface::icomponent* component, const char* to_topic, const char* api, const Args&... args) {
		auto range = _topic_map.equal_range(to_topic);
		for(topic_map::iterator itr = range.first; itr!=range.second; ++itr) {
			if(itr->second.compare(component->get_name())==0) {
				driver::component_driver* _drv = cossb_component_manager->get_driver(itr->second.c_str());
				if(_drv)
					_drv->request(api, args...);
			}
		}

		return true;
	}

private:
	topic_map	_topic_map;
};

#define cossb_broker		cossb::broker::component_broker::instance()

} /* namespace broker */
} /* namespace cossb */

#endif
