/*
 * jsonprofile.hpp
 *
 *  Created on: 2015. 10. 14.
 *      Author: hwang
 */

#ifndef INCLUDE_JSONPROFILE_HPP_
#define INCLUDE_JSONPROFILE_HPP_

#include "ext/json.hpp"

namespace cossb {
namespace profile {

/**
 * @brief	json style profile
 */
class jsonprofile : public interface::iprofile {
public:
	jsonprofile();
	virtual ~jsonprofile();

	bool load(const char* filepath);

	type_value get(section section, const char* element);

	bool update(section section, const char* element, const char* value);

	bool save();
};

} /* namespace profile */
} /* namespace cossb */

#endif /* INCLUDE_JSONPROFILE_HPP_ */
