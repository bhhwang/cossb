/**
 * @file		soloader.hpp
 * @brief		shared library loader
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 12
 * @details	dependent shared library loader(multiple independent)
 */


#ifndef _COSSB_SOLOADER_HPP_
#define _COSSB_SOLOADER_HPP_

#include <dlfcn.h>
#include <string>
#include "util/format.h"
#include <iostream>

using namespace std;

namespace cossb {
namespace base {

template<class T>
class soloader {
public:
	soloader(const char* so_file):_so(so_file) {
		string sopath = fmt::format("./{}",_so);

		cout << "load " << sopath << endl;
		_handle = dlopen(sopath.c_str(), RTLD_NOW|RTLD_GLOBAL);
	}

	virtual ~soloader() {
		cout << "unload" << endl;
		if(_handle){
			dlclose(_handle);
			_handle = nullptr;
		}
	}

	T* load() {

		if(_handle)
		{
			typedef T* create_t();
			create_t* pfcreate = (create_t*)dlsym(_handle, "create");

			if(pfcreate)
				return pfcreate();
		}

		return nullptr;
	}

private:
	void* _handle = nullptr;
	string _so;
};

} /* namespace base */
} /* namespace cossb */

#endif /* _COSSB_SOLOADER_HPP_ */
