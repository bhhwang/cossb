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

	virtual void trace(const char* logstr) = 0;
	virtual void debug(const char* logstr) = 0;
	virtual void info(const char* logstr) = 0;
	virtual void notice(const char* logstr) = 0;
	virtual void trace(const char* logstr) = 0;
	virtual void warn(const char* logstr) = 0;
	virtual void error(const char* logstr) = 0;
	virtual void critical(const char* logstr) = 0;
	virtual void alert(const char* logstr) = 0;
	virtual void emerg(const char* logstr) = 0;

};

} /* namespace interface */
} /* namespace cossb */

#endif
