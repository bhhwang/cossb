/**
 * @file		xmlprofile.hpp
 * @brief		XML component profile
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	XML component profile
 */

#ifndef _COSSB_XMLPROFILE_HPP_
#define _COSSB_XMLPROFILE_HPP_

#include "interface/iprofile.hpp"
#include <tinyxml2.h>
#include <string>

using namespace std;
using namespace tinyxml2;

namespace cossb {
namespace profile {

class xmlprofile : public interface::iprofile {
public:
	xmlprofile();
	virtual ~xmlprofile();

	/**
	 * @brief	load xml profile
	 */
	bool load(const char* filepath);

	/**
	 * @brief	getting profile value with matched type
	 */
	profile::type_value get(profile::section section, const char* element);

	/**
	 * @brief	update
	 */
	bool update(profile::section section, const char* element, const char* value);

	/**
	 * @brief	save
	 */
	bool save();

private:

	/**
	 * @brief	getting comment what error is occurred
	 */
	const char* get_error_str(int error) const;

private:
	XMLDocument _doc;
	bool _loaded = false;
	string _filepath;
};

} /* namespace profile */
} /* namespace cossb */

#endif /* _COSSB_XMLPROFILE_HPP_ */
