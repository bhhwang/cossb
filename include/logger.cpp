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
	// TODO Auto-generated constructor stub

}

logger::~logger() {
	// TODO Auto-generated destructor stub
}

void logger::log(const char* logstr)
{
	cout << "Log Console : " << logstr << endl;
}

} /* namespace log */
} /* namespace cossb */
