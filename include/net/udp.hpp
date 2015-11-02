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
#include <exception.hpp>

namespace cossb {
namespace net {

class udp : public sock {
public:
	udp(netType type, net::endpoint_v4 address, int port):sock(type),_port(port) {
		switch(type)
		{
		case netType::CLIENT: break;
		case netType::HOST:
		{
			if((this->sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
				throw net::exception(net::excode::SOCKET_CREATE_FAIL);
			else {
				memset(&_address, 0, sizeof(_address));
				_address.sin_family = AF_INET;
				_address.sin_addr.s_addr = htonl(INADDR_ANY);
				_address.sin_port = htons(port);
			}
		}
			break;
		}
	}

	virtual ~udp() {
		close();
	}

protected:
	int open(int port) {
		if((this->sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))<0) {
			return -1;
		}
		return this->sockfd;
	}

	void close() {
		::close(this->sockfd);
	}

	int write(char* data, unsigned int len) {
		if(this->sockfd!=-1) {
			return ::write(this->sockfd, data, len);
		}
		else
			throw net::exception(excode::NET_OPEN_FAIL);
		return -1;
	}

	int writeto(net::endpoint_v4 dest, char* data, unsigned int len) {
		if(this->sockfd!=-1) {
			//return ::sendto(this->sockfd, data, len, 0, (struct sockaddr*)&dest, sizeof(de));
		}
		else
			throw net::exception(excode::NET_OPEN_FAIL);

		return -1;
	}

private:
	int _port;
};

} /* namespace net */
} /* namespace cossb */

#endif /* _COSSB_NET_UDP_HPP_ */
