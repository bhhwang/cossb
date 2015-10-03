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

enum class netType : unsigned int { SERVER=1, CLIENT };
enum class sockType : unsigned int { DGRAM=1, STREAM };

class sock {
public:
	sock(netType type):_type(type) { }
	virtual ~sock();

	virtual int write(char* data, unsigned int len) = 0;

protected:
	netType* get_type() { return &_type; }

protected:
	int sockfd = -1;

private:
	netType _type;
};

} /* namespace net */
} /* namespace cossb */

#endif /* _COSSB_NET_SOCK_HPP_ */
