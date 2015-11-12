/**
 * @file		cblog.hpp
 * @brief		COSSB log library (on console stream)
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 13
 * @details	this library will support developer to debug your application
 */

#ifndef _COSSB_SUPPORT_LIBCBLOG_CBLOG_HPP_
#define _COSSB_SUPPORT_LIBCBLOG_CBLOG_HPP_

#include <interface/ilog.hpp>
#include <util/localtime.hpp>

namespace cossb {
namespace base {

class cblog : public interface::ilog {
public:
	cblog();
	virtual ~cblog();

	void log(const log::loglevel& level,  const char* logstr, log::color color= log::color::STATIC);

private:
	util::systime _time;
};

} /* namespace base */
} /* namespace cossb */

#endif /* _COSSB_SUPPORT_LIBCBLOG_CBLOG_HPP_ */
