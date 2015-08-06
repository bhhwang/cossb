/**
 * @file		auth.hpp
 * @brief		Authentication module
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 7. 29
 * @details	Authentication for service component download, service license..
 */

#ifndef _COSSB_AUTH_HPP_
#define _COSSB_AUTH_HPP_

#include <string>
#include "interface/iauth.hpp"

using namespace std;

namespace cossb {
namespace auth {

class auth : public interface::iauth {
public:
	auth();
	virtual ~auth();

	/**
	 * @brief	authentication
	 */
	//bool authenticate(interface::iauth::authcode code, unsigned int len);
	bool authenticate(authcode code, unsigned int len);
};

} /* namesoace auth */
} /* namespace cossb */

#endif /* _COSSB_AUTH_HPP_ */
