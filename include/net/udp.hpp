/**
 * @file		udp.hpp
 * @brief		COSSB UDP Library
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 24
 * @details	UDP Socket library (IPv4 Only)
 */

#ifndef _COSSB_NET_UDP_HPP_
#define _COSSB_NET_UDP_HPP_

#include "sock.hpp"
#include "exception.hpp"

namespace cossb {
namespace net {

class udp : public sock {
public:

	/**
	 * @brief UDP constructor for IPv4
	 */
	udp():_port(0) {
	}

	virtual ~udp() {
		close();
	}

	/**
	 * @brief	create socket
	 */
	void create(const char* address, int port)
	{
		if((this->sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1)
			throw net::exception(net::excode::SOCKET_CREATE_FAIL);
		else
		{
			memset(&_address_v4, 0, sizeof(_address_v4));

			_address_v4.sin_family = AF_INET;
			_address_v4.sin_addr.s_addr = INADDR_ANY;
			_address_v4.sin_port = htons(port);
		}
	}

	/**
	 * @brief	 close socket
	 */
	void close() {
		::close(this->sockfd);
	}

	/**
	 * @brief	set socket reuse option
	 */
	void set_reuse() {
		unsigned int reuse = 1;
		if(setsockopt(this->sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse))<0)
			throw net::exception(net::excode::SOCKET_SET_REUSE_FAIL);
	}

	/**
	 * @brief	set socket receive timeout option
	 */
	void set_timeout(int sec, int usec) {
		struct timeval timeout;
		timeout.tv_sec = sec;
		timeout.tv_usec = usec;

		if(setsockopt(this->sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout))<0)
			throw net::exception(net::excode::SOCKET_SET_TIMEOUT_FAIL);
	}

	/**
	 * @brief	set_loopback
	 */
	void set_loopback(bool loop) {
		if(setsockopt(this->sockfd, IPPROTO_IP, IP_MULTICAST_LOOP, &(int)loop, sizeof((int)loop))<0)
			throw net::exception(net::excode::SOCKET_SET_LOOPBACK_FAIL);
	}

	/**
	 * @brief	for udp multicast
	 */
	void join_group(const char* ipv4) {
		struct ip_mreq	_mreq;
		_mreq.imr_multiaddr.s_addr = inet_addr(ipv4);
		_mreq.imr_interface.s_addr = htonl(INADDR_ANY);
		if(setsockopt(this->sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &_mreq, sizeof(_mreq))<0)
			throw net::exception(net::excode::SOCKET_SET_ADDMEMBERSHIP_FAIL);
	}

protected:

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

	/**
	 * @brief	ip version
	 */

	/**
	 * @brief	socket address for IPv4
	 */
	//struct sockaddr_in	_address_v4;

};

} /* namespace net */
} /* namespace cossb */

#endif /* _COSSB_NET_UDP_HPP_ */
