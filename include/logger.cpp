/*
 * logger.cpp
 *
 *  Created on: 2015. 8. 9.
 *      Author: hwang-linux
 */

#include "logger.hpp"
#include <iostream>
#include "interface/ilog.hpp"
#include "util/format.h"

namespace cossb {
namespace log {

logger::logger(){ }
logger::logger(interface::ilog* log):_logger(log) { }

logger::~logger() {
	_logger = nullptr;

}
void logger::log(const log::loglevel level, const char* str)
{
	log_base(level, str);
}

void logger::log_base(const loglevel level, const char* str)
{
	if(_logger)
	{
		switch(level)
		{
		case	loglevel::TRACE:	_logger->trace(str);	break;
		case	loglevel::DEBUG:	_logger->debug(str);	break;
		case	loglevel::INFO:	_logger->info(str);	break;
		case	loglevel::NOTICE: _logger->notice(str);	break;
		case	loglevel::WARN: _logger->warn(str);	break;
		case	loglevel::ERROR: _logger->error(str);	break;
		case	loglevel::CRITICAL: _logger->critical(str);	break;
		case	loglevel::ALERT: _logger->alert(str);	break;
		case	loglevel::EMERG: _logger->emerg(str);	break;
		}
	}
	else
	{
		switch(level)
		{
		case	loglevel::TRACE:	cout << "[TRACE]\t"	<< str << endl;	break;
		case	loglevel::DEBUG:	cout << "[DEBUG]\t"	<< str << endl;	break;
		case	loglevel::INFO:	cout << "[INFO]\t"	<< str << endl;	break;
		case	loglevel::NOTICE: cout << "[NOTICE]\t"	<< str << endl;	break;
		case	loglevel::WARN: cout << "[WARN]\t"	<< str << endl;	break;
		case	loglevel::ERROR: cout << "[ERROR]\t"	<< str << endl;	break;
		case	loglevel::CRITICAL: cout << "[CRITICAL]\t"	<< str << endl;	break;
		case	loglevel::ALERT: cout << "[ALERT]\t"	<< str << endl;	break;
		case	loglevel::EMERG: cout << "[EMERG]\t"	<< str << endl;	break;
		}
	}
}

void logger::adopt(interface::ilog* intlog)
{
	_logger = intlog;
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
