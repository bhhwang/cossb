/*
 * cbmdns.cpp
 *
 *  Created on: 2015. 8. 20.
 *      Author: hwang-linux
 */

#include "cbmdns.hpp"

namespace cossb {
namespace base {

cbmdns::cbmdns() {
	// TODO Auto-generated constructor stub

}

cbmdns::~cbmdns() {
	// TODO Auto-generated destructor stub
}
} /* namespace base */


extern "C" interface::ilog* create() {
	return new base::cblog;
}

extern "C" void destroy(interface::ilog* instance) {
	delete instance;
}

} /* namespace cossb */
