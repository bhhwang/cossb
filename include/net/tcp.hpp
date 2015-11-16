/**
 * @file		tcp.hpp
 * @brief		tcp protocol class
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 10. 3
 * @details	TCP protocol
 */


#ifndef INCLUDE_NET_TCP_HPP_
#define INCLUDE_NET_TCP_HPP_

#include "sock.hpp"
#include "exception.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <fcntl.h>


namespace cossb {
namespace net {

enum class netType : int { SERVER=1, CLIENT };

class tcp : public sock {
public:
	tcp(netType type, const char* address, int port):_port(port) {
		switch(type)
		{
		case netType::CLIENT:
		{
			if((this->sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))==-1)
				throw net::exception(net::excode::SOCKET_CREATE_FAIL);
			else {
				memset(&_address_v4, 0, sizeof(_address_v4));
				_address_v4.sin_family = AF_INET;
				_address_v4.sin_addr.s_addr = inet_addr(address);
				_address_v4.sin_port = htons(port);
			}
			break;
		}
		case netType::SERVER:
		{
			if((this->sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))==-1)
				throw net::exception(net::excode::SOCKET_CREATE_FAIL);
			else {
				memset(&_address_v4, 0, sizeof(_address_v4));
				_address_v4.sin_family = AF_INET;
				_address_v4.sin_addr.s_addr = htonl(INADDR_ANY);
				_address_v4.sin_port = htons(port);
			}
		}
			break;
		}
	}

	virtual ~tcp() {
		close();
	}


	void async_connect() {
		if(fcntl(sockfd, F_SETFL, O_NONBLOCK | fcntl(sockfd, F_GETFL))==-1)
			return;
			//cossb_log->log(cossb::log::loglevel::ERROR, "Cannot change non-blocking mode..");

		int timeout = 1;
		int intvl = 1;
		int probes = 3;
		int on = 1;
		::setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, (void*) &on, sizeof(int));
		::setsockopt(sockfd, SOL_TCP, TCP_KEEPIDLE, (void*) &timeout, sizeof(int));
		::setsockopt(sockfd, SOL_TCP, TCP_KEEPINTVL, (void*) &intvl, sizeof(int));
		::setsockopt(sockfd, SOL_TCP, TCP_KEEPCNT, (void*) &probes, sizeof(int));

		::connect( this->sockfd, (struct sockaddr*)&_address_v4, sizeof(_address_v4));
	}

	void sync_connect() {
		if(::connect( this->sockfd, (struct sockaddr*)&_address_v4, sizeof(_address_v4))==-1)
			throw net::exception(net::excode::CONNECTION_FAIL);
	}

	void disconnect() {
		close();
	}


protected:

	int open(int port) {
		if((this->sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))<0) {
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

#endif /* INCLUDE_NET_TCP_HPP_ */
