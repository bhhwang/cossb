/*
 * server.hpp
 *
 *  Created on: 2015. 10. 3.
 *      Author: hwang
 */

#ifndef INCLUDE_NET_SERVER_HPP_
#define INCLUDE_NET_SERVER_HPP_


namespace cossb {
namespace net {

class server {
public:
	server(sockType type);
	virtual ~server();
};

} /* namespace net */
} /* namespace cossb */


#endif /* INCLUDE_NET_SERVER_HPP_ */
