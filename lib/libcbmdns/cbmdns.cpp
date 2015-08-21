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

void cbmdns::start()
{

}

void cbmdns::stop()
{

}

} /* namespace base */

extern "C" interface::isimpleservice* create() {
	return new base::cbmdns;
}

extern "C" void destroy(interface::isimpleservice* instance) {
	delete instance;
}

} /* namespace cossb */
