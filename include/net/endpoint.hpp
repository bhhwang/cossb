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

namespace cossb {
namespace net {

struct endpoint : protected sockaddr_in {
public:
	endpoint();
	endpoint(unsigned int port);
	endpoint(const char* ipaddr);
	endpoint(struct sockaddr_in);

private:
	char ip[16];
	unsigned int port;
};

} /* namespace net */
} /* namespace cossb */

#endif /* _COSSB_NET_ENDPOINT_HPP_ */
