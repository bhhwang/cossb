/*
 * cc3200led.hpp
 *
 *  Created on: 2015. 10. 29.
 *      Author: hwang
 */

#ifndef EXAMPLES_CC3200_LED_CC3200LED_HPP_
#define EXAMPLES_CC3200_LED_CC3200LED_HPP_

#include <interface.hpp>

class cc3200led : public cossb::interface::icomponent {
public:
	cc3200led();
	virtual ~cc3200led();
};

COMPONENT_EXPORT

#endif /* EXAMPLES_CC3200_LED_CC3200LED_HPP_ */
