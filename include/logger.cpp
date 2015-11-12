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
void logger::log(const log::loglevel& level, const char* logstr, log::color color)
{
	if(_logger)
		_logger->log(level, logstr, color);
	else
	{
		switch(level)
		{
		case	loglevel::TRACE:	cout << "[TRACE]\t"	<< logstr << endl;	break;
		case	loglevel::DEBUG:	cout << "[DEBUG]\t"	<< logstr << endl;	break;
		case	loglevel::INFO:	cout << "[INFO]\t"	<< logstr << endl;	break;
		case	loglevel::NOTICE: cout << "[NOTICE]\t"	<< logstr << endl;	break;
		case	loglevel::WARN: cout << "[WARN]\t"	<< logstr << endl;	break;
		case	loglevel::ERROR: cout << "[ERROR]\t"	<< logstr << endl;	break;
		case	loglevel::CRITICAL: cout << "[CRITICAL]\t"	<< logstr << endl;	break;
		case	loglevel::ALERT: cout << "[ALERT]\t"	<< logstr << endl;	break;
		case	loglevel::EMERG: cout << "[EMERG]\t"	<< logstr << endl;	break;
		}
	}
}

void logger::log(const log::loglevel& level, string logstr, log::color color)
{
	if(_logger)
		_logger->log(level, logstr.c_str(), color);
	else
	{
		switch(level)
		{
		case	loglevel::TRACE:	cout << "[TRACE]\t"	<< logstr << endl;	break;
		case	loglevel::DEBUG:	cout << "[DEBUG]\t"	<< logstr << endl;	break;
		case	loglevel::INFO:	cout << "[INFO]\t"	<< logstr << endl;	break;
		case	loglevel::NOTICE: cout << "[NOTICE]\t"	<< logstr << endl;	break;
		case	loglevel::WARN: cout << "[WARN]\t"	<< logstr << endl;	break;
		case	loglevel::ERROR: cout << "[ERROR]\t"	<< logstr << endl;	break;
		case	loglevel::CRITICAL: cout << "[CRITICAL]\t"	<< logstr << endl;	break;
		case	loglevel::ALERT: cout << "[ALERT]\t"	<< logstr << endl;	break;
		case	loglevel::EMERG: cout << "[EMERG]\t"	<< logstr << endl;	break;
		}
	}
}

void logger::adopt(interface::ilog* intlog)
{
	_logger = intlog;
}

} /* namespace log */
} /* namespace cossb */
