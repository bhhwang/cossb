/*
 * cbmdns.cpp
 *
 *  Created on: 2015. 8. 20.
 *      Author: hwang-linux
 */

#include "cbmdns.hpp"
#include "../../include/library_util.hpp"
#include <iostream>

using namespace std;

namespace cossb {
namespace base {

cbmdns::cbmdns() {
	cout << "create mdns service" << endl;

}

cbmdns::~cbmdns() {
	cout << "destroy mdns service" << endl;
}


} /* namespace base */

extern "C" interface::iobject* create() {
	return new base::cbmdns;
}

extern "C" void destroy(interface::iobject* instance) {
	delete instance;
}

} /* namespace cossb */
