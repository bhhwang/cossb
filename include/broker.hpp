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

private:
	topic_map	_topic_map;
};

#define cossb_component_broker	cossb::broker::component_broker::instance()

} /* namespace broker */
} /* namespace cossb */

#endif
