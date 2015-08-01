/**
 * @file		iauth.hpp
 * @brief		authentication interface
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 7. 29
 * @details	authentication interface class
 */

#ifndef _COSSB_INTERFACE_IAUTH_HPP_
#define _COSSB_INTERFACE_IAUTH_HPP_

namespace cossb {
namespace interface {

typedef struct {
	char code[16];
} authcode16;

typedef struct {
	char code[32];
} authcode32;

enum class authResponse : int {
	NOT_ACCESSIBLE = -1,	// Cannot access Auth system
	NOT_PERMIT = 1,		// Auth Fail
	SUCCESS = 10, 		// Auth Success
};

class iauth {
	virtual ~iauth() { }

	virtual bool authenticate16(authcode16* acode) = 0;
	virtual bool authenticate32(authcode32* acode) = 0;
};

} /* namespace interface */
} /* namespace cossb */



#endif /* _COSSB_INTERFACE_IAUTH_HPP_ */
