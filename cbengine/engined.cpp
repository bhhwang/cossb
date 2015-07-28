/**
 * @file		engined.cpp
 * @brief		COSSB Engine Daemon
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 7. 28
 * @details	COSSB Engine Daemon
 */

#include <iostream>
#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include <popt.h>
#include <memory>
#include <syslog.h>
#include <fcntl.h>

#include "cossb.hpp"

using namespace std;
using namespace cossb;


/**
 * @brief	destroy main instance
 * @details	It will be called by SIGINT signal
 */
void destroy()
{
	manager::component_manager::get()->destroy();
	broker::component_broker::get()->destroy();
}

/**
 * @brief	SIGTERM signal callback function
 * @details	Stop all services and destroy all instances
 */
void sigc_terminate(int param) { destroy();	exit(0); }

/**
 * @brief	Main routine
 * @param	command
 * @details	Execute as daemon
 */

int main(int argc, char* argv[])
{
	signal(SIGTERM, sigc_terminate);

	pid_t pid;

	if(daemon(1,1)==-1)
	  return EXIT_FAILURE;

	if((pid=fork())<0)
	  return EXIT_FAILURE;
	else if(pid>0)
	  _exit(0);	//terminate parent


	char* config_file = nullptr;
	struct poptOption optionTable[] = {
			{"run", 'r', POPT_ARG_NONE, 0, 'r', "Run Engine with default configuration", ""},
			{"version", 'v', POPT_ARG_NONE, 0, 'v', "Version", "version"},
			{"config", 'c', POPT_ARG_STRING, (void*)config_file, 'c', "Open configuration file", "XML Configuration file"},
			{"debug", 'd', POPT_ARG_NONE, 0, 'd', "DEBUG mode", ""},
			{"reset", 'e', POPT_ARG_NONE, 0, 'e', "Reset All system", "Clear and initialize the configurations"},
			POPT_AUTOHELP
			POPT_TABLEEND
	};
	poptContext optionCon = poptGetContext(NULL, argc, (const char**)argv, optionTable, 0);
	poptSetOtherOptionHelp(optionCon, "<option>");

	if(argc<2)
	{
		std::cout << poptStrerror(POPT_ERROR_NOARG) << endl;
		destroy();
		_exit(0);
	}

	int opt = 0;
	while((opt = poptGetNextOpt(optionCon))>=0)
	{
		switch(opt)
		{
		// install components
		case 'v':
		{
			std::cout << COSSB_NAME << COSSB_VERSION << " (Released " << __DATE__ << " " <<__TIME__ << ")" << std::endl;
			destroy();
			_exit(0);

		} break;

		//load configuration file
		case 'c':
		{
			string config_file = (const char*)poptGetOptArg(optionCon);
			manager::component_manager::get()->load_config(new config(config_file.c_str()));
		}
			break;

		//run in debug mode
		case 'd':
		{
		}
			break;

		case 'r':
		{
			manager::component_manager::get()->load_config(new config("manifest.xml"));
		}
		break;

		}
	}

	if (opt<-1)
	{
		cout << poptBadOption(optionCon, POPT_BADOPTION_NOALIAS) << ":" << poptStrerror(opt) << endl;
		destroy();
		_exit(0);
	}

	pause();

	//notice, this function affects the checking memory leak, especially when you are using valgrind.
	poptFreeContext(optionCon);

	destroy();
	_exit(0);

	return 0;

}
