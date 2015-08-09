/**
 * @file		noncopyable.hpp
 * @brief		be non-copyable class
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 9
 * @details	Be non-copyable class
 */

#ifndef _COSSB_ARCH_NONCOYABLE_HPP_
#define _COSSB_ARCH_NONCOYABLE_HPP_


namespace cossb {
namespace arch {

template<class T>
class noncopyable {
protected:
	noncopyable() = default;
	~noncopyable() = default;

private:
	noncopyable(const noncopyable&);
	noncopyable& operator = (const noncopyable&);
};

} /* namespace arch */
} /* namespae cossb */


#endif /* _COSSB_ARCH_NONCOYABLE_HPP_ */
