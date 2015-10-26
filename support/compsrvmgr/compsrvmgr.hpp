/*
 * compsrvmgr.hpp
 *
 *  Created on: 2015. 10. 26.
 *      Author: hwang
 *
 *      remove service management component
 */

#ifndef SUPPORT_COMPSRVMGR_COMPSRVMGR_HPP_
#define SUPPORT_COMPSRVMGR_COMPSRVMGR_HPP_

#include <interface.hpp>
#include <net/udpmulticast.hpp>

using namespace cossb;

class compsrvmgr : public cossb::interface::icomponent {
public:
	compsrvmgr();
	virtual ~compsrvmgr();

	bool setup();
	bool run();
	bool stop();
	void request(cossb::message::message* msg) const;

private:
	void response();

private:
	cossb::net::udpmulticast* _udp_multicast = nullptr;

	base::task _response_task;

};

COMPONENT_EXPORT

#endif /* SUPPORT_COMPSRVMGR_COMPSRVMGR_HPP_ */
