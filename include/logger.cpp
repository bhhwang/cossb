/*
 * logger.cpp
 *
 *  Created on: 2015. 8. 9.
 *      Author: hwang-linux
 */

#include "logger.hpp"
#include <iostream>
#include "interface/ilog.hpp"

namespace cossb {
namespace log {

logger::logger()
{

}

logger::~logger() {
	if(_logger)
		delete _logger;

}
void logger::log(const char* str)
{
	cout << "call log" << endl;
	if(_logger)
		_logger->info(str);

	/*switch(level)
	{
	case loglevel::TRACE:{	cout << "[TRACE] " << str << endl; }	break;
	}*/
}
/*
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
*/
} /* namespace log */
} /* namespace cossb */
