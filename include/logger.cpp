/*
 * logger.cpp
 *
 *  Created on: 2015. 8. 9.
 *      Author: hwang-linux
 */

#include "logger.hpp"
#include <iostream>

namespace cossb {
namespace log {

logger::logger() {
	this->_stream = log::logstream::CONSOLE;
}

logger::~logger() {

}

void logger::trace(const char* logstr)
{
	cout << _time.current_formatted() << "[TRACE] " << logstr << endl;
}
void logger::debug(const char* logstr)
{
	cout << _time.current_formatted() << "[DEBUG] " << logstr << endl;
}
void logger::info(const char* logstr)
{
	cout << _time.current_formatted() << "[INFO] " << logstr << endl;
}
void logger::notice(const char* logstr)
{
	cout << _time.current_formatted() << "[NOTICE] " << logstr << endl;
}
void logger::warn(const char* logstr)
{
	cout << _time.current_formatted() << "[WARNING] " << logstr << endl;
}
void logger::error(const char* logstr)
{
	cout << _time.current_formatted() << "[RROR] " << logstr << endl;
}
void logger::critical(const char* logstr)
{
	cout << _time.current_formatted() << "[CRITICAL] " << logstr << endl;
}
void logger::alert(const char* logstr)
{
	cout << _time.current_formatted() << "[ALERT] " << logstr << endl;
}
void logger::emerg(const char* logstr)
{
	cout << _time.current_formatted() << "[EMERGENCY] " << logstr << endl;
}
} /* namespace log */
} /* namespace cossb */
