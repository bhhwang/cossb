/**
 * @file		multicast.hpp
 * @brief		COSSB UDP Multicast
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015.11. 5
 * @details	UDP Multicast
 */

#ifndef INCLUDE_NET_MULTICAST_HPP_
#define INCLUDE_NET_MULTICAST_HPP_

#include "sock.hpp"
#include "exception.hpp"

namespace cossb {
namespace net {

/**
 * @brief	UDP multicast
 */
class multicast : public sock
{
public:
	multicast() { }
	virtual ~multicast() {
		close();
	}

	/**
	 * @brief	create socket
	 */
	void create(const char* group_address, int group_port)
	{
		if((this->sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
			throw net::exception(net::excode::SOCKET_CREATE_FAIL);
		else
		{
			memset(&_group_addr_v4, 0, sizeof(_group_addr_v4));

			_group_addr_v4.sin_family = AF_INET;
			_group_addr_v4.sin_addr.s_addr = inet_addr(group_address);
			_group_addr_v4.sin_port = htons(group_port);

			//join membership
			_mreq.imr_multiaddr = _group_addr_v4.sin_addr;
			_mreq.imr_interface.s_addr = htonl(INADDR_ANY);
			if(setsockopt(this->sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &_mreq, sizeof(_mreq))<0)
				throw net::exception(net::excode::SOCKET_SET_ADDMEMBERSHIP_FAIL);

			//socket reuse
			unsigned int reuse = 1;
			if(setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse))<0)
				throw net::exception(net::excode::SOCKET_SET_REUSE_FAIL);

			//timeout 1 sec
			struct timeval timeout = {1, 0};
			if(setsockopt(this->sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout))<0)
				throw net::exception(net::excode::SOCKET_SET_TIMEOUT_FAIL);

			//bind
			if(::bind(this->sockfd, (struct sockaddr*)&_group_addr_v4, sizeof(_group_addr_v4))<0)
				throw net::exception(net::excode::SOCKET_BIND_FAIL);
		}
	}

	/**
	 * @brief	 close socket
	 */
	void close() {
		::close(this->sockfd);
	}

private:
	sockaddr_in _group_addr_v4;
	struct ip_mreq _mreq;

};

}
}


#endif /* INCLUDE_NET_MULTICAST_HPP_ */
