/**
 * @file		compmdns.hpp
 * @brief		Multicast DNS Responser
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 25
 * @details		mDNS service for COSSB
 */

#ifndef _COSSB_SUPPORT_COMPONENT_COMPMDNS_HPP_
#define _COSSB_SUPPORT_COMPONENT_COMPMDNS_HPP_

#include "../../include/interface.hpp"

using namespace cossb;

class compmdns : interface::icomponent {
public:
	compmdns();
	virtual ~compmdns();

	bool setup();
	bool run();
	bool stop();
	void request(cossb::interface::imessage* msg);
};

COMPONENT_EXPORT

#endif /* _COSSB_SUPPORT_COMPONENT_COMPMDNS_HPP_ */
