/*
 * udpmulticast.hpp
 *
 *  Created on: 2015. 10. 26.
 *      Author: hwang
 */

#ifndef INCLUDE_NET_UDPMULTICAST_HPP_
#define INCLUDE_NET_UDPMULTICAST_HPP_

#include "sock.hpp"
#include <exception.hpp>

namespace cossb {
namespace net {

class udpmulticast : public sock {
public:
	udpmulticast(netType type, const char* ipv4, int port):sock(type) {
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

				struct ip_mreq	_mreq;
				_mreq.imr_multiaddr.s_addr = inet_addr(ipv4);
				_mreq.imr_interface.s_addr = htonl(INADDR_ANY);

				//join network group
				if(::setsockopt(this->sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &_mreq, sizeof(_mreq))<0)
					throw net::exception(net::excode::SOCKET_SET_ADDMEMBERSHIP_FAIL);

				//receive timeout 3 sec
				struct timeval timeout = {3, 0};
				if(setsockopt(this->sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout))<0)
					throw net::exception(net::excode::SOCKET_SET_TIMEOUT_FAIL);

				//socket reuse
				unsigned int reuse = 1;
				if(setsockopt(this->sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse))<0)
					throw net::exception(net::excode::SOCKET_SET_REUSE_FAIL);

				if(::bind(this->sockfd, (struct sockaddr*)&_address, sizeof(_address))<0) {
					throw net::exception(net::excode::SOCKET_BIND_FAIL);
				}
			}
		}
			break;
		}
	}
	virtual ~udpmulticast() { }

};

} /* namespace net */
} /* namespace cossb */


#endif /* INCLUDE_NET_UDPMULTICAST_HPP_ */
