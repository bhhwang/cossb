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
namespace log {
enum class logstream : unsigned int { CONSOLE=1, FILE };
enum class loglevel: unsigned int { TRACE=1, DEBUG, INFO, NOTICE, WARN, ERROR, CRITICAL, ALERT, EMERG };
}


namespace driver { class component_driver; }

namespace interface {

class ilog {

	friend driver::component_driver;

public:
	ilog(log::logstream stream):_stream(stream) { }
	virtual ~ilog() { }

	/**
	 * @brief	log interface function
	 */
	virtual void log(const log::loglevel& level,  const char* logstr) = 0;


protected:
	log::logstream get_stream() const { return _stream; }

private:
	log::logstream _stream;

};

} /* namespace interface */
} /* namespace cossb */

#endif
