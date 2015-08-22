/**
 * @file		cbmdns.hpp
 * @brief		COSSB MDNS library (Responser)
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 20
 * @details	This library will support as Domain Name Server
 */

#ifndef _COSSB_SUPPORT_LIBCBMDNS_CBMDNS_HPP_
#define _COSSB_SUPPORT_LIBCBMDNS_CBMDNS_HPP_


#include "../../include/interface/iobject.hpp"
#include "../../include/net/udp.hpp"

namespace cossb {
namespace base {

class cbmdns : public interface::iobject {
public:
	cbmdns();
	virtual ~cbmdns();

private:
	void start_mdns();
	void stop_mdns();

private:
	net::udp* _udp_sock = nullptr;

};

} /* namespace base */
} /* namespace cossb */

#endif /* _COSSB_SUPPORT_LIBCBMDNS_CBMDNS_HPP_ */
