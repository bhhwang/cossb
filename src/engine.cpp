/**
 * @mainpage	COSSB(Component-based Open & Simple Service Broker)
 * @details	COSSB�뒗 �궗臾쇱씤�꽣�꽬(IoT) �쑀臾댁꽑 �꽕�듃�썙�겕 �솚寃쎌뿉�꽌 留먮떒 �옣移섍컙 �꽌鍮꾩뒪 �긽�샇�슫�슜�꽦(Inter-operability)怨� �솗�옣�꽦�쓣 吏��썝 �븯湲곗쐞�븳 �냼�봽�듃�썾�뼱 �봽�젅�엫�썙�겕�엯�땲�떎.
 */


/**
 * @file		engine.cpp
 * @brief		COSSB Engine
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 6. 9
 * @details	COSSB Engine main starter
 */

#include <iostream>
#include <csignal>
#include <cstdlib>
#include <popt.h>
#include <memory>

#include "cossb.hpp"

using namespace std;
using namespace cossb;

void destroy() {
	cossb::core::cossb_destroy();
	_exit(EXIT_SUCCESS);
}

/**
 * @brief	SIGINT signal callback function
 * @details	Stop all services and destroy all instances
 */
void sigc_interrupt(int param) {
	destroy();
}

/**
 * @brief	Main routine
 * @param	command
 * @details	Start with default components
 */
int main(int argc, char* argv[])
{
	signal(SIGINT, sigc_interrupt);

	char* config_file = nullptr;
	struct poptOption optionTable[] =
	{
		{"run",		'r', POPT_ARG_NONE, 0, 'r', "Run Engine with default configuration", ""},
		{"version",	'v', POPT_ARG_NONE, 0, 'v', "Version", "version"},
		{"config", 	'c', POPT_ARG_STRING, (void*)config_file, 'c', "Open configuration file", "XML Configuration file"},
		POPT_AUTOHELP
		POPT_TABLEEND
	};
	poptContext optionCon = poptGetContext(NULL, argc, (const char**)argv, optionTable, 0);
	poptSetOtherOptionHelp(optionCon, "<option>");

	if(argc<2)
	{
		std::cout << poptStrerror(POPT_ERROR_NOARG) << endl;
		_exit(EXIT_SUCCESS);
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
			_exit(EXIT_SUCCESS);

		} break;

		//load configuration file
		case 'c':
		{
			string manifest = (const char*)poptGetOptArg(optionCon);
			if(!manifest.empty())
			{
				if(!cossb::core::cossb_init(manifest.c_str()))
					destroy();
			}
		}
			break;

		//run with default configuration file(manifest.xml)
		case 'r':
		{
			if(!cossb::core::cossb_init("manifest.xml"))
				destroy();
			else {
				cossb_log->log(log::loglevel::INFO, fmt::format("Now Starting {}{}",COSSB_NAME, COSSB_VERSION).c_str());
			}
		}
		break;

		}
	}

	if (opt<-1)
	{
		cout << poptBadOption(optionCon, POPT_BADOPTION_NOALIAS) << ":" << poptStrerror(opt) << endl;
		destroy();
	}

	//start the cossb service
	cossb::core::cossb_start();

	pause();
	poptFreeContext(optionCon);

	destroy();

	return 0;
}
