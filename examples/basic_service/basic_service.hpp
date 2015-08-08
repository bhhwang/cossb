/**
 * @file	basic_service.hpp
 * @brief	simple service component
 * @author	Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 	2015. 8. 7
 * @details	console print component
 */


#ifndef _COSSB_EXAMPLE_BASIC_SERVICE_HPP_
#define _COSSB_EXAMPLE_BASIC_SERVICE_HPP_

#include "../../include/interface.hpp"

using namespace cossb::interface;

class basic_service : public icomponent
{
public:
	basic_service();
	virtual ~basic_service();

	bool setup();
	bool run();
	bool stop();
	void request(imessage* msg);

};

COMPONENT_EXPORT


#endif /* _COSSB_EXAMPLE_BASIC_SERVICE_HPP_ */
