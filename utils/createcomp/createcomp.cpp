/*
 * createcomp.cpp
 *
 *  Created on: 2015. 9. 6.
 *      Author: hwang-linux
 */

#include "createcomp.hpp"
#include "../../include/logger.hpp"
#include <popt.h>
#include <boost/filesystem.hpp>
#include <string>
#include "../../include/base/configreader.hpp"


using namespace std;
using namespace boost;

namespace cossb {

/**
 * @brief	use utility interface macro
 */
USE_UTILITY_INTERFACE_EXECUTE(cossb::createcomp)


createcomp::createcomp() {
	// TODO Auto-generated constructor stub

}

createcomp::~createcomp() {
	// TODO Auto-generated destructor stub
}

bool createcomp::execute(int argc, char* argv[])
{
	const int arg_offset = 2;	//ignore the 2 args from the first
	int argcc = argc - arg_offset;
	char** argvv = &argv[arg_offset];

	if(argcc>1)
	{
		string path = cossb_config->get_path()->find("component")->second;
		path.append(argvv[1]);

		filesystem::path fullpath = filesystem::system_complete(path);
		boost::filesystem::create_directories(fullpath);
		cossb_log->log(log::loglevel::INFO, fmt::format("Create directory {}", fullpath).c_str());

		return true;
	}
	else
		return false;
}

} /* namespace cossb */

