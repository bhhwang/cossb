/**
 * @file		cblog.hpp
 * @brief		COSSB log library (on console stream)
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 13
 * @details	this library will support developer to debug your application
 */

#ifndef _COSSB_SUPPORT_LIBCBLOG_CBLOG_HPP_
#define _COSSB_SUPPORT_LIBCBLOG_CBLOG_HPP_

#include "../../include/interface/ilog.hpp"
#include "../../include/util/localtime.hpp"

namespace cossb {
namespace base {

class cblog : public interface::ilog {
public:
	cblog();
	virtual ~cblog();

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

} /* namespace base */
} /* namespace cossb */

#endif /* _COSSB_SUPPORT_LIBCBLOG_CBLOG_HPP_ */
