/*
 * udp.hpp
 *
 *  Created on: 2015. 8. 22.
 *      Author: hwang-linux
 */

#ifndef _COSSB_NET_UDP_HPP_
#define _COSSB_NET_UDP_HPP_

#include "sock.hpp"

namespace cossb {
namespace net {

class udp : public sock {
public:
	udp(netType type):sock(type) { }
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
