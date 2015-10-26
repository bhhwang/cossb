/*
 * server.hpp
 *
 *  Created on: 2015. 10. 3.
 *      Author: hwang
 */

#ifndef INCLUDE_NET_SERVER_HPP_
#define INCLUDE_NET_SERVER_HPP_

#include <sys/socket.h>
#include <arpa/inet.h>
#include <util/uuid.hpp>


namespace cossb {
namespace net {

class server {
public:
	server(sockType type);
	virtual ~server();

private:
	struct sockaddr_in	_addr;
	util::uuid _session_uuid;
};

} /* namespace net */
} /* namespace cossb */


#endif /* INCLUDE_NET_SERVER_HPP_ */
