/*
 * utlauncher.cpp
 *
 *  Created on: 2015. 9. 6.
 *      Author: hwang-linux
 */

#include "utilloader.hpp"
#include <dlfcn.h>
#include <popt.h>
#include <sys/stat.h>

namespace cossb {
namespace util {

utilloader::utilloader(const char* target_util) {


}

utilloader::~utilloader() {
	// TODO Auto-generated destructor stub
}

bool utilloader::launch(int argc, char* argv[])
{
	/*_ut_handle = dlopen(target_util, RTLD_LAZY|RTLD_GLOBAL);
	if(_ut_handle)
	{
		create_component pfcreate = (create_component)dlsym(_ut_handle, "create");
		if(!pfcreate) {
			dlclose(_ut_handle);
			_ut_handle = nullptr;
			return false;
		}




		destroy_component pfdestroy = (destroy_component)dlsym(_ut_handle, "destroy");
		if(pfdestroy)
			pfdestroy();

		if(_ut_handle)
		{
			dlclose(_ut_handle);
			_ut_handle = nullptr;
		}

	}*/

	return false;
}

} /* namespace util */
} /* namespace cossb */
