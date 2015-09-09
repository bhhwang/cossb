/**
 * @file		broker.cpp
 * @brief		Component Broker
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details
 */

#include "broker.hpp"
#include "manager.hpp"

namespace cossb {
namespace broker {

component_broker::component_broker()
{

}

component_broker::~component_broker()
{

}

bool component_broker::regist(interface::icomponent* component, string topic_name)
{
	_topic_map.insert(topic_map::value_type(topic_name, component->get_name()));
	return true;
}

template<typename... Args>
bool component_broker::publish(interface::icomponent* component, const char* to_topic, const char* api, const Args&... args)
{
	auto range = _topic_map.equal_range(to_topic);
	for(topic_map::iterator itr = range.first; itr!=range.second; ++itr) {
		if(itr->second.compare(component->get_name())!=0) {
			driver::component_driver* _drv = cossb_component_manager->get_driver(itr->second.c_str());//->request(api, args...);
			/*if(_drv)
				_drv->request(api, args...);*/
		}
	}

	return true;
}

} /* namespace broker */
} /* namespace cossb */
