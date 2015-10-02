/**
 * @file	mbed_rgb.hpp
 * @brief	ARM mbed RGB LED control component
 * @author	Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 	2015. 10. 2
 * @details	ARM mbed rgb LED control service component example
 */

#ifndef EXAMPLES_MBED_RGB_MBEDRGB_HPP_
#define EXAMPLES_MBED_RGB_MBEDRGB_HPP_

#include "../../include/interface.hpp"

class mbed_rgb : public cossb::interface::icomponent {
public:
	mbed_rgb();
	virtual ~mbed_rgb();

	bool setup();
	bool run();
	bool stop();
	void request(cossb::message::message* msg);
};

COMPONENT_EXPORT

#endif /* EXAMPLES_MBED_RGB_MBEDRGB_HPP_ */
