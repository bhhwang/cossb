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

} /* namespace broker */
} /* namespace cossb */
