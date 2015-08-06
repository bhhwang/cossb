/**
 * @file		ilog.hpp
 * @brief		Log interface
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Log interface
 */


#ifndef _COSSB_ILOG_HPP_
#define _COSSB_ILOG_HPP_

/**
 * @brief	interface for simple log process
 */

namespace cossb {
namespace interface {

class ilog {
public:
	virtual ~ilog() { }

	virtual void log(const char* logstr) = 0;

};

} /* namespace interface */
} /* namespace cossb */

#endif
