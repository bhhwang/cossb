/**
 * @file		ideplib.hpp
 * @brief		Interface for dependent shared library implementation
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 13
 * @details	COSSB dependent shared library interface can be loaded by general loader like component.
 */

#ifndef _COSSB_INTERFACE_IDEPLIB_HPP_
#define _COSSB_INTERFACE_IDEPLIB_HPP_

namespace cossb {
namespace interface {

template <class T>
class ideplib {
public:
	ideplib() {}
	virtual ~ideplib() {}
};

} /* namespace interface */
} /* namespace cossb */



#endif /* _COSSB_INTERFACE_IDEPLIB_HPP_ */
