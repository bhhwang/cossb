/**
 * @file		udp.hpp
 * @brief		COSSB UDP Library
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 24
 * @details	UDP Socket library
 */

#ifndef _COSSB_NET_UDP_HPP_
#define _COSSB_NET_UDP_HPP_

#include "sock.hpp"

namespace cossb {
namespace net {

class udp : public sock {
public:
	udp(netType type, net::endpoint_v4 address, int port):sock(type) {
		switch(type)
		{
		case netType::CLIENT: break;
		case netType::SERVER: break;
		}
	}
	udp(netType type, int port):sock(type) { }
	virtual ~udp() { }

	int open(int port) {
		this->sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		return this->sockfd;
	}

	void close() {

	}

private:

};

} /* namespace net */
} /* namespace cossb */

#endif /* _COSSB_NET_UDP_HPP_ */
