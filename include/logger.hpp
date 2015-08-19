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

namespace cossb {

namespace manager { class system_manager; }
namespace interface { class ilog; }

namespace log {

enum class loglevel: unsigned int;

class logger : public arch::singleton<logger>
{

	friend class manager::system_manager;

public:
	logger();
	logger(interface::ilog* log);
	virtual ~logger();

	void log(const loglevel level,  const char* str);

	/*template<typename... Args>
	void log2(loglevel level, const char* str, Args... args) {
		//unsigned int size = sizeof...(args);
		cout << "[TRACE] " << str << endl;
	}*/


private:
	interface::ilog* _logger = nullptr;

};

#define cossb_log		cossb::log::logger::instance()

} /* namespace log */
} /* namespace cossb */

#endif /* _COSSB_LOGGER_HPP_ */
