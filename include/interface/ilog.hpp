/**
 * @file		ilog.hpp
 * @brief		Log interface
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 21
 * @details	Log interface
 */


#ifndef _COSSB_ILOG_HPP_
#define _COSSB_ILOG_HPP_

class ilog {

public:
	ilog() { }
	virtual ~ilog() { }

	template<typename... Args> void trace(const char* fmt, const Args&... args);
	template<typename... Args> void debug(const char* fmt, const Args&... args);
	template<typename... Args> void info(const char* fmt, const Args&... args);
	template<typename... Args> void warn(const char* fmt, const Args&... args);
	template<typename... Args> void error(const char* fmt, const Args&... args);

	template<typename T> void trace(const T&);
	template<typename T> void debug(const T&);
	template<typename T> void info(const T&);
	template<typename T> void warn(const T&);
	template<typename T> void error(const T&);

};

#endif
