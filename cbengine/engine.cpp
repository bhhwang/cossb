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
#include <cstdlib>
#include <unistd.h>
#include "cossb.hpp"

using namespace std;

/**
 * @brief	destroy main instance
 * @details	It will be called by SIGINT signal
 */
void destroy()
{

}

/**
 * @brief	SIGINT signal callback function
 * @details	Stop all services and destroy all instances
 */
void sigc_interrupt(int param) { destroy();	exit(0); }

/**
 * @brief	Main routine
 * @param	command
 * @details	Start with default components
 */
int main(int argc, char* argv[])
{
	signal(SIGINT, sigc_interrupt);

	pause();

	return 0;
}
