/**
 * @file		soloader.hpp
 * @brief		shared library loader
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 12
 * @details	dependent shared library loader
 */


#ifndef _COSSB_SOLOADER_HPP_
#define _COSSB_SOLOADER_HPP_

namespace cossb {
namespace base {

template<typename T>
class soloader {
public:
	soloader();
	virtual ~soloader();
};

} /* namespace soloader */
} /* namespace cossb */

#endif /* _COSSB_SOLOADER_HPP_ */
