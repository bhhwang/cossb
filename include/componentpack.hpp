/**
 * @file		componentpack.hpp
 * @brief		header file for component
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 27
 * @details	component class header may be required this header
 */

#ifndef _COSSB_COMPONENTPACK_HPP_
#define _COSSB_COMPONENTPACK_HPP_


#if defined(__unix__) || defined(__gnu_linux__) || defined(linux) || defined(__linux__)

#include "logger.hpp"	//for base logger
#include "broker.hpp"	//for topic/message broker

#endif


#endif /* _COSSB_COMPONENTPACK_HPP_ */
