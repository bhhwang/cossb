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
#include <boost/lexical_cast.hpp>

using namespace std;

namespace cossb {
namespace interface { class iprofile; }

namespace profile {

typedef enum {
	info = 0,	//component information
	property, 	//properties
	resource,	//related resource
} section;

class type
{
public:
	type():value("") { }
	virtual ~type() { }

	friend class interface::iprofile;

	template<typename T>
	inline T as(T default_value) {
		try {
			T val = boost::lexical_cast<T>(value);
			return val;
		} catch( boost::bad_lexical_cast const& ) {
			return default_value;
		}
	}

	int asInt(int default_value) { return as(default_value); }
	unsigned int asUInt(unsigned int default_value) { return as(default_value); }
	unsigned long asUlong(unsigned long default_value) { return as(default_value); }
	double asDouble(double default_value) { return as(default_value); }
	float asFloat(float default_value) { return as(default_value); }
	bool asBool(bool default_value) { return as(default_value); }
	string asString(string default_value) { return as(default_value); }
	unsigned char asUChar(unsigned char default_value) { return as(default_value); }
	char asChar(char default_value) { return as(default_value); }

private:
	std::string value;

};
}


namespace interface {
class iprofile {
public:
	iprofile() { }
	virtual ~iprofile() { }

	/**
	 * @brief
	 */
	virtual bool load(const char* filepath) = 0;

	/**
	 * @brief
	 */
	virtual profile::type get(profile::section section, const char* element) = 0;

	/**
	 * @brief
	 */
	virtual bool save() = 0;

protected:
	/**
	 * @brief
	 */
	void set(profile::type& profile, string value) { profile.value = value; }

};

} /* namespace interface */
} /* namespace cossb */

#endif
