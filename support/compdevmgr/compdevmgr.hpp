/*
 * compdevmgr.hpp
 *
 *  Created on: 2015. 10. 27.
 *      Author: hwang
 */

#ifndef SUPPORT_COMPDEVMGR_COMPDEVMGR_HPP_
#define SUPPORT_COMPDEVMGR_COMPDEVMGR_HPP_

#include <interface.hpp>
#include <net/udpmulticast.hpp>

using namespace cossb;

class compdevmgr : public cossb::interface::icomponent {
public:
	compdevmgr();
	virtual ~compdevmgr();

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

#endif /* SUPPORT_COMPDEVMGR_COMPDEVMGR_HPP_ */
