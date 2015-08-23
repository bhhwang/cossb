/**
 * @file		exception.hpp
 * @brief		exception for network
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 23
 * @details	Network exception
 */

#ifndef _COSSB_NET_EXCEPTION_HPP_
#define _COSSB_NET_EXCEPTION_HPP_

#include <string>
#include <exception>

using namespace std;

namespace cossb {
namespace net {

struct net_exception : public exception {
	net_exception(const char* ex):str_exception(ex) { }
	~net_exception() throw() {}
	const char* what() const throw() {
		return str_exception.c_str();
	}
private:
	string str_exception;

};

} /* namespace net */
} /* namespace cossb */



#endif /* _COSSB_NET_EXCEPTION_HPP_ */
