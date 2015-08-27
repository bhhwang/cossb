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
void logger::log(const log::loglevel& level, const char* str)
{
	if(_logger)
		_logger->log(level, str);
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
