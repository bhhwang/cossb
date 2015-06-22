/**
 * @file		manager.hpp
 * @brief		COSSB component manager
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details
 */

#ifndef _COSSB_MANAGER_HPP_
#define _COSSB_MANAGER_HPP_


namespace cossb {
namespace manager {

class component_manager {
public:
	static component_manager* get();
	void destroy();

private:
	static component_manager* _instance;
};


} /* namespace manager */
} /* namespace cossb */

#endif
