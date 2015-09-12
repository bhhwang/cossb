/**
 * @file		comptcpserver.hpp
 * @brief		TCP Server component
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 25
 * @details		TCP server component (multiple client accessible)
 */


#ifndef SUPPORT_COMPONENT_COMPTCPSERVER_HPP_
#define SUPPORT_COMPONENT_COMPTCPSERVER_HPP_

#include "../../include/interface.hpp"

using namespace cossb;

class comptcpserver : public interface::icomponent {
public:
	comptcpserver();
	virtual ~comptcpserver();

	bool setup();
	bool run();
	bool stop();
	void request(message::message* msg);
};

COMPONENT_EXPORT

#endif /* SUPPORT_COMPONENT_COMPTCPSERVER_HPP_ */
