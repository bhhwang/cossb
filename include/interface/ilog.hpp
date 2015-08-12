/**
 * @file		ilog.hpp
 * @brief		Log interface
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Log interface
 */


#ifndef _COSSB_ILOG_HPP_
#define _COSSB_ILOG_HPP_

#include <string>

using namespace std;

/**
 * @brief	interface for simple log process
 */

namespace cossb {
namespace log {
enum class logstream : unsigned int { CONSOLE=1, FILE };
}

namespace driver { class component_driver; }

namespace interface {

class ilog {

	friend driver::component_driver;

public:
	ilog(log::logstream stream, const char* session):_stream(stream), _session(session) { }
	virtual ~ilog() { }

protected:

	virtual void trace(const char* logstr) = 0;
	virtual void debug(const char* logstr) = 0;
	virtual void info(const char* logstr) = 0;
	virtual void notice(const char* logstr) = 0;
	virtual void warn(const char* logstr) = 0;
	virtual void error(const char* logstr) = 0;
	virtual void critical(const char* logstr) = 0;
	virtual void alert(const char* logstr) = 0;
	virtual void emerg(const char* logstr) = 0;

protected:
	log::logstream get_stream() const { return _stream; }

private:
	log::logstream _stream;
	string _session;

};

} /* namespace interface */
} /* namespace cossb */

#endif
