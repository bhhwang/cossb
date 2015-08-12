/**
 * @file		logger.hpp
 * @brief		ossb default console logger
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 9
 * @details	COSSB default logger
 */
#ifndef _COSSB_LOGGER_HPP_
#define _COSSB_LOGGER_HPP_

#include "interface/ilog.hpp"
#include "arch/singleton.hpp"
#include "util/localtime.hpp"

namespace cossb {
namespace log {


class logger : public interface::ilog {
public:
	logger();
	virtual ~logger();

	void trace(const char* logstr);
	void debug(const char* logstr);
	void info(const char* logstr);
	void notice(const char* logstr);
	void warn(const char* logstr);
	void error(const char* logstr);
	void critical(const char* logstr);
	void alert(const char* logstr);
	void emerg(const char* logstr);

private:
	util::systime _time;

};

} /* namespace log */
} /* namespace cossb */

#endif /* _COSSB_LOGGER_HPP_ */
