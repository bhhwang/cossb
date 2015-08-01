/**
 * @file		xmlconfig.hpp
 * @brief		XML Configuration document
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 7. 28
 * @details	XML Configuration document
 */

#ifndef _COSSB_XMLCONFIG_HPP_
#define _COSSB_XMLCONFIG_HPP_

namespace cossb {

class xmlconfig : public interface::iconfigdoc {
public:
	xmlconfig();
	virtual ~xmlconfig();

	bool load(const char* filepath);
};

} /* namespace cossb */

#endif /* _COSSB_XMLCONFIG_HPP_ */
