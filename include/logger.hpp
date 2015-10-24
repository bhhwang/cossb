/**
 * @file		logger.hpp
 * @brief		ossb default console logger
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 9
 * @details	COSSB default logger
 */
#ifndef _COSSB_LOGGER_HPP_
#define _COSSB_LOGGER_HPP_

#include "arch/singleton.hpp"
#include "util/format.h"
#include "interface/ilog.hpp"

namespace cossb {

namespace manager { class system_manager; }

namespace log {

class logger : public arch::singleton<logger>
{

	friend class manager::system_manager;

public:
	logger();
	logger(interface::ilog* log);
	virtual ~logger();

	/**
	 * @brief	simple log interface function
	 */
	void log(const loglevel& level,  const char* logstr);
	void log(const log::loglevel& level, string logstr);


	/**
	 * @brief	to use another log interface dynamically
	 */
	void adopt(interface::ilog* intlog);

private:

	/**
	 * @brief	default log base function
	 */
	void log_base(const loglevel level, const char* str);


private:
	interface::ilog* _logger = nullptr;

};

#define cossb_log		cossb::log::logger::instance()

} /* namespace log */
} /* namespace cossb */

#endif /* _COSSB_LOGGER_HPP_ */
