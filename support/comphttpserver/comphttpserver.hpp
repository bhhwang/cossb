/**
 * @file		comphttpserver.hpp
 * @brief		HTTP Server
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 9. 29
 * @details	Light weight HTTP server component using microhttpd-dev
 */

#ifndef SUPPORT_COMPHTTPSERVER_COMPHTTPSERVER_HPP_
#define SUPPORT_COMPHTTPSERVER_COMPHTTPSERVER_HPP_

#include "../../include/interface.hpp"

using namespace cossb;

class comphttpserver : public interface::icomponent {
public:
	comphttpserver();
	virtual ~comphttpserver();

	bool setup();
	bool run();
	bool stop();
	void request(cossb::message::message* msg);
};

COMPONENT_EXPORT


#endif /* SUPPORT_COMPHTTPSERVER_COMPHTTPSERVER_HPP_ */
