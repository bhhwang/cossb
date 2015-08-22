/**
 * @file		endpoint.hpp
 * @brief		network endpoint
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 3
 * @details	IP address description
 */

#ifndef _COSSB_NET_ENDPOINT_HPP_
#define _COSSB_NET_ENDPOINT_HPP_

#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

namespace cossb {
namespace net {

/**
 * @brief	endpoint for IPv4
 */
struct endpoint_v4 : public sockaddr_in {
public:
	endpoint_v4() {
		memset(ipv4, 0x00, sizeof(ipv4));
	}
	endpoint_v4(const char* ipaddr){
		memset(ipv4, 0x00, sizeof(ipv4));
		inet_pton(AF_INET, ipaddr, &(this->sin_addr));
	}

private:
	char ipv4[INET_ADDRSTRLEN];
};

/**
 * @brief	endpoint for IPv6
 */
struct endpoint_v6 : public sockaddr_in6 {
public:
	endpoint_v6() {
		memset(ipv6, 0x00, sizeof(ipv6));
	}
	endpoint_v6(const char* ipaddr) {
		memset(ipv6, 0x00, sizeof(ipv6));
		inet_pton(AF_INET6, ipaddr, &(this->sin6_addr));
	}
private:
	char ipv6[INET6_ADDRSTRLEN];
};

} /* namespace net */
} /* namespace cossb */

#endif /* _COSSB_NET_ENDPOINT_HPP_ */
