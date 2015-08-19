/**
 * @file		libadopter.hpp
 * @brief		internal standard library adopter(loader)
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 19
 * @details	COSSB library adopter
 */

#ifndef _COSSB_LIBADOPTER_HPP_
#define _COSSB_LIBADOPTER_HPP_

#include <dlfcn.h>
#include <string>
#include "util/format.h"

using namespace std;

namespace cossb {
namespace base {

template<class T>
class libadopter {
public:
	libadopter(const char* solib):_so(solib) {
		string libpath = fmt::format(".{}",_so);
		_handle = dlopen(libpath.c_str(), RTLD_NOW|RTLD_GLOBAL);
	}

	virtual ~libadopter() {
		if(_handle) {
			dlclose(_handle);
			_handle = nullptr;
		}
	}

private:
	void* _handle = nullptr;
	string _so;
};

} /* namespace base */
} /* namespace cossb */


#endif /* _COSSB_LIBADOPTER_HPP_ */
