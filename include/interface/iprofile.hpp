/**
 * @file		iprofile.hpp
 * @brief		Component Profile interface class
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Read component profile interface
 */


#ifndef _COSSB_IPROFILE_HPP_
#define _COSSB_IPROFILE_HPP_

#include <string>

using namespace std;

namespace cossb {
namespace profile {

class type {
public:
	type():_value("") { }

	template<typename T>
	inline T as(T default_value) {
		try {
			return std::to_string(_value);
		}
	}
private:
	string _value;
};
}


namespace interface {

class iprofile {
public:
	/**
	 * @brief
	 */
	virtual bool load(const char* filepath) = 0;

	/**
	 * @brief
	 */
	virtual bool save() = 0;

protected:
	/**
	 * @brief
	 */

};

} /* namespace interface */
} /* namespace cossb */

#endif
