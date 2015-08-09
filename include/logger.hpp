/**
 * @file		logger.hpp
 * @brief		system default console logger
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 9
 * @details	default logger
 */
#ifndef _COSSB_LOGGER_HPP_
#define _COSSB_LOGGER_HPP_

#include "interface/ilog.hpp"
#include "arch/singleton.hpp"

namespace cossb {
namespace log {

class logger : public interface::ilog, arch::singleton<logger> {
public:
	logger();
	virtual ~logger();

	void log(const char* logstr);
};

#define cossb_log		cossb::log::logger::instance()

} /* namespace log */
} /* namespace cossb */

#endif /* _COSSB_LOGGER_HPP_ */
