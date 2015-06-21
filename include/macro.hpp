/**
 * @file		macro.hpp
 * @brief		COSSB Macro
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details
 */

#ifndef _COSSB_MACRO_HPP_
#define _COSSB_MACRO_HPP_

#include "interface/icomponent_base.hpp"

namespace cossb {

#define COMPONENT_EXPORT				extern "C" { interface::icomponent_base* create(); void destroy(void); }

#define COMPONENT_INSTANCE(classname)	static classname* _instance = nullptr;

#define COMPONENT_CREATE(classname) 	interface::icomponent_base* create(){ \
											if(_instance==nullptr) _instance = new classname(); \
											return _instance; }

#define COMPONENT_DESTROY 				void destroy(){ \
											if(_instance!=nullptr){ \
												delete _instance; _instance=nullptr; }	\
											}

#define COMPONENT(classname) #classname


} /* namespace cossb */



#endif /* _COSSB_MACRO_HPP_ */
