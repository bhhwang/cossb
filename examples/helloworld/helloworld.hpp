/**
 * @file	helloworld.hpp
 * @brief	hello world component
 * @author	Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 	2015. 8. 7
 * @details	hello world component
 */

#ifndef _COSSB_EXAMPLE_HELLOWORLD_HPP_
#define _COSSB_EXAMPLE_HELLOWORLD_HPP_

#include "../../include/interface.hpp"

class hello_world : public cossb::interface::icomponent {
public:
	hello_world();
	virtual ~hello_world();

	bool setup();
	bool run();
	bool stop();
	void request(cossb::interface::imessage* msg);
};

COMPONENT_EXPORT

#endif /* _COSSB_EXAMPLE_HELLOWORLD_HPP_ */

