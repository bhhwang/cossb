/**
 * @file		cbmdns.hpp
 * @brief		COSSB MDNS library (Responser)
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 20
 * @details	This library will support as Domain Name Server
 */

#ifndef _COSSB_SUPPORT_LIBCBMDNS_CBMDNS_HPP_
#define _COSSB_SUPPORT_LIBCBMDNS_CBMDNS_HPP_


#include "../../include/interface/isimpleservice.hpp"

namespace cossb {
namespace base {

class cbmdns : public interface::isimpleservice {
public:
	cbmdns();
	virtual ~cbmdns();

	void start();
	void stop();
};

} /* namespace base */
} /* namespace cossb */

#endif /* _COSSB_SUPPORT_LIBCBMDNS_CBMDNS_HPP_ */
