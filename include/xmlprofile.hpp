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

private:
	bool load(const char* filepath);
	profile::type get(profile::section section, const char* element);
	bool save();
	const char* get_error_str(int error) const;

private:
	XMLDocument _doc;
	bool _loaded = false;
	string _filepath;
};

} /* namespace profile */
} /* namespace cossb */

#endif /* _COSSB_XMLPROFILE_HPP_ */
