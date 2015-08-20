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

} /* namespace log */
} /* namespace cossb */
