/**
 * @file		singleton.hpp
 * @brief		Singleton pattern design template class
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 2
 * @details	Singleton pattern design for single global instance
 */

#ifndef _COSSB_ARCH_SINGLETON_HPP_
#define _COSSB_ARCH_SINGLETON_HPP_


namespace cossb {
namespace arch {

/**
 * @brief	singleton pattern on stack memory
 * @detail	if the template class allocate in the stack memory, might be taken care of memory limitation of the target machine.
 */
template <class T>
class singleton_s {

public:
	static T& get() {
		static T instance;
		return instance;
	}
	}

	singleton_s(singleton_s const& instance) = delete;			//for non-copyable idiom
	singleton_s& operator=(singleton_s const& instance) = delete;

};

/**
 * @brief	singleton pattern on heap memory
 * @detail	not apply the double check locking
 */
template <class T>
class singleton_h {
public:
	static T& get() {
		if(_instance==nullptr)
			_instance = new T;
		return _instance;
	}
	virtual ~singleton_h() {
		if(_instance) {
			delete _instance;
			_instance = nullptr;
		}
	}

private:
	static T* _instance = nullptr;
	singleton_h(singleton_h const& instance) = delete;
};

} /* namespace arch */
} /* namespace cossb */


#endif /* _COSSB_ARCH_SINGLETON_HPP_ */
