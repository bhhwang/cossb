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
#include <popt.h>
#include <memory>

#include "cossb.hpp"

using namespace std;


poptContext optionCon;


/**
 * @brief	destroy main instance
 * @details	It will be called by SIGINT signal
 */
void destroy()
{
	poptFreeContext(optionCon);
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

	char* config_file = nullptr;
	struct poptOption optionTable[] = {
			{"version", 'v', POPT_ARG_NONE, 0, 'v', "Version", "version"},
			{"config", 'c', POPT_ARG_STRING, (void*)config_file, 'c', "Open config file", "XML Config file"},
			{"debug", 'd', POPT_ARG_NONE, 0, 'd', "DEBUG mode", "Run in DEBUG mode"},
			POPT_AUTOHELP
			POPT_TABLEEND
	};
	optionCon = poptGetContext(NULL, argc, (const char**)argv, optionTable, 0);
	poptSetOtherOptionHelp(optionCon, "<option>");

	if(argc<2)
	{
		destroy();
		exit(0);
	}

	int opt = 0;
	while((opt = poptGetNextOpt(optionCon))>=0)
	{
		switch(opt)
		{
		// install components
		case 'v':
		{
			std::cout << COSSB_VERSION << " (Released " << __DATE__ << " " <<__TIME__ << ")" << std::endl;
			destroy();
			exit(0);

		} break;

		case 'c':
		{
			string config_file = (const char*)poptGetOptArg(optionCon);
			cout << "Config file : " << config_file << endl;
		}
			break;

		case 'd':
		{
			cout << "run in debug mode" << endl;
		}
			break;

		}
	}

	if (opt<-1)
	{
		cout << poptBadOption(optionCon, POPT_BADOPTION_NOALIAS) << ":" << poptStrerror(opt) << endl;
		destroy();
		exit(0);
	}

	pause();

	//notice, this function affects the checking memory leak, especially when you are using valgrind.
	poptFreeContext(optionCon);

	destroy();
	exit(0);

	return 0;
}
