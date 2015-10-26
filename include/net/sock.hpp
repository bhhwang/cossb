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

enum class netType : unsigned int { HOST=1, CLIENT };
enum class sockType : unsigned int { DGRAM=1, STREAM };

class sock {
public:
	sock(netType type):_type(type) { }
	virtual ~sock() {
			if(sockfd>0)
				close(sockfd);
	}

protected:
	netType* get_type() { return &_type; }

public:
	int sockfd = -1;

protected:
	struct sockaddr_in	_address;

private:
	netType _type;
};

} /* namespace net */
} /* namespace cossb */

#endif /* _COSSB_NET_SOCK_HPP_ */
