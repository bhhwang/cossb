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
#include <iostream>
#include <exception>
#include <stdexcept>
#include "logger.hpp"

using namespace std;


namespace cossb {
namespace exception {
class cossb_exception : public std::exception {
public:
	cossb_exception(const char* msg) : exception_str(msg) { }
	~cossb_exception() throw() { }
	virtual const char* what() const throw() {
		return exception_str.c_str();
	}
protected:
	void set(const char* msg) { exception_str = msg; }
private:
	std::string exception_str;
};
} /* namespace exception */

/**
 * @brief	broker exception
 */
namespace broker {
enum class excode : int { DRIVER_NOT_FOUND=0, };

class exception : public cossb::exception::cossb_exception {
public:
	exception(broker::excode code):cossb::exception::cossb_exception("unknown exception") {
		switch(code)
		{
		case	excode::DRIVER_NOT_FOUND: set("Driver cannot be found");  break;
		}
	}
};

} /* namespace broker */


} /* namespace cossb */


#endif /* _COSSB_EXCEPTION_HPP_ */
