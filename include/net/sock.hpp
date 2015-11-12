/**
 * @file		sock.hpp
 * @brief		basic socket class
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 2
 * @details
 */

#ifndef _COSSB_NET_SOCK_HPP_
#define _COSSB_NET_SOCK_HPP_

#include "endpoint.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

namespace cossb {
namespace net {

/**
 * @brief	socket type (DGRAM=UDP socket, STREAM=tcp socket)
 */
enum class sockType : unsigned int { DGRAM=1, STREAM };


class sock {
public:
	sock() { }
	virtual ~sock() {
		if(sockfd)
			close(sockfd);
	}

	int* get_sock() { return &sockfd; }

protected:

	/**
	 * @brief	socket file descriptor
	 */
	int sockfd = -1;

	/**
	 * @brief	socket address for IPv4
	 */
	struct sockaddr_in	_address_v4;

};

} /* namespace net */
} /* namespace cossb */

#endif /* _COSSB_NET_SOCK_HPP_ */
