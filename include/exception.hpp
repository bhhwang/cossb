/**
 * @file		exception.hpp
 * @brief		COSSB exception
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 23
 * @details	cossb exception header
 */


#ifndef _COSSB_EXCEPTION_HPP_
#define _COSSB_EXCEPTION_HPP_


#include <string>
#include <exception>

using namespace std;

namespace cossb {

struct cossb_exception : public exception {
	cossb_exception(const char* msg):str_exception(msg) { }
	cossb_exception(const string& msg):str_exception(msg) { }
	~cossb_exception() throw() {}
	const char* what() const throw() {
		return str_exception.c_str();
	}
private:
	string str_exception;

};

} /* namespace cossb */


#endif /* _COSSB_EXCEPTION_HPP_ */
