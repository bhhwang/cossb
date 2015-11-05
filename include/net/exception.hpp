/*
 * exception.hpp
 *
 *  Created on: 2015. 11. 4.
 *      Author: hwang
 */

#ifndef INCLUDE_NET_EXCEPTION_HPP_
#define INCLUDE_NET_EXCEPTION_HPP_

#include <exception.hpp>

namespace cossb {
namespace net {

enum class excode : int {
	NET_OPEN_FAIL = 0,
	NET_WRITE_FAIL,
	NET_READ_FAIL,
	SOCKET_CREATE_FAIL,
	SOCKET_BIND_FAIL,
	SOCKET_SET_REUSE_FAIL,
	SOCKET_SET_ADDMEMBERSHIP_FAIL,
	SOCKET_SET_TIMEOUT_FAIL,
	SOCKET_SET_LOOPBACK_FAIL,
	CONNECTION_FAIL,
};

/**
 * @brief	network exception
 */
class exception : public cossb::exception::cossb_exception
{
public:
	exception(net::excode code, const char* err_msg = nullptr) {
		switch(code) {
		case excode::NET_OPEN_FAIL: set("Network open fail"); break;
		case excode::NET_WRITE_FAIL: set("Network write fail"); break;
		case excode::NET_READ_FAIL: set("Network read fail"); break;
		case excode::SOCKET_CREATE_FAIL: set("Network socket create fail"); break;
		case excode::SOCKET_BIND_FAIL: set("Network bind fail"); break;
		case excode::SOCKET_SET_REUSE_FAIL: set("Network reuse setting fail"); break;
		case excode::SOCKET_SET_ADDMEMBERSHIP_FAIL: set("Network add membership fail"); break;
		case excode::SOCKET_SET_TIMEOUT_FAIL: set("Network timeout setting fail"); break;
		case excode::SOCKET_SET_LOOPBACK_FAIL: set("Network loopback setting fail"); break;
		case excode::CONNECTION_FAIL: set("Connection fail"); break;
		default:
			set(fmt::format("Unknown exception({})", (int)code).c_str()); break;
		}
	}
};

} /* namespace net */
} /* namespace cossb */



#endif /* INCLUDE_NET_EXCEPTION_HPP_ */
