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

namespace cossb {
namespace net {

class tcp : public sock {
public:
	tcp();
	virtual ~tcp();
};

} /* namespace net */
} /* namespace cossb */

#endif /* INCLUDE_NET_TCP_HPP_ */
