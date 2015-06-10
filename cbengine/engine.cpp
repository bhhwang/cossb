/**
 * @mainpage	COSSB(Component-based Open & Simple Service Broker)
 * @details	COSSB is a software framework to support IoT service interoperability among the networked devices or gadgets scattered in WLAN environment.
 */


/**
 * @file		engine.hpp
 * @brief		COSSB Engine
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 9
 * @details	COSSB Engine main routine
 */

#include <iostream>
#include <csignal>
#include "cossb.hpp"

using namespace std;

void sigc_interrupt(int s) { exit(0); }

/**
 * @brief	Main routine
 * @param	command
 * @details	Start with default components
 */
int main(int argc, char* argv[])
{
	signal(SIGINT, sigc_interrupt);
	return 0;
}
