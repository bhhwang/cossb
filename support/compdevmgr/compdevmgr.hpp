/**
 * @file		compdevmgr.hpp
 * @brief		device connection management component
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 10. 27
 * @details		Device connection management component
 */

#ifndef SUPPORT_COMPDEVMGR_COMPDEVMGR_HPP_
#define SUPPORT_COMPDEVMGR_COMPDEVMGR_HPP_

#include <interface.hpp>
#include <net/udpmulticast.hpp>
#include <map>

using namespace cossb;
using namespace std;

typedef string	devicename;
typedef map<string, sockaddr_in> deviceinfo_container;

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
	/**
	 * @brief	UDP Responser
	 */
	cossb::net::udpmulticast* _udp_multicast = nullptr;

	/**
	 * @brief	UDP response task
	 */
	base::task _response_task;

	/**
	 * @brief	receive buffer
	 */
	char* _rcv_buffer = nullptr;

	/**
	 * @brief	device information container
	 */
	deviceinfo_container* _dev_container = nullptr;

};

COMPONENT_EXPORT

#endif /* SUPPORT_COMPDEVMGR_COMPDEVMGR_HPP_ */
