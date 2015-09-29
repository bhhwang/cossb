/*
 * comphttpserver.hpp
 *
 *  Created on: 2015. 9. 29.
 *      Author: hwang
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
