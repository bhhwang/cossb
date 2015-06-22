/**
 * @file		broker.cpp
 * @brief		Component Broker
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details
 */

#include "broker.hpp"

namespace cossb {
namespace broker {

component_broker* component_broker::_instance = nullptr;
component_broker* component_broker::get()
{
	if(!_instance)
		_instance = new component_broker;
	return _instance;
}

void component_broker::destroy()
{
	if(_instance)
		delete _instance;
}

bool component_broker::regist(interface::icomponent* component, topic topic_name)
{
	bool success = false;
	if(_instance) {
		_topic_map.insert(topic_map::value_type(topic_name, component->get_name()));
		success = true;
	}

	return success;
}

} /* namespace broker */
} /* namespace cossb */
