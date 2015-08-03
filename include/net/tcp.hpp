/**
 * @file		tcp.hpp
 * @brief		tc
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 2
 * @details		use for system base
 */
#ifndef _COSSB_NET_TCP_HPP_
#define _COSSB_NET_TCP_HPP_

#include "sock.hpp"
#include "../interface/icomm.hpp"

namespace cossb {
namespace net {

typedef enum nettype { SERVER = 1, CLIENT };

class tcp : public sock, public interface::icomm {
public:
	tcp();
	virtual ~tcp();

};

} /* namespace net */
} /* namespace cossb */

#endif /* _COSSB_NET_TCP_HPP_ */
