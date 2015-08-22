/*
 * cbmdns.cpp
 *
 *  Created on: 2015. 8. 20.
 *      Author: hwang-linux
 */

#include "cbmdns.hpp"
#include <iostream>
#include <pthread.h>

using namespace std;

namespace cossb {
namespace base {

cbmdns::cbmdns() {
	start_mdns();
}

cbmdns::~cbmdns() {
	stop_mdns();
}

void cbmdns::start_mdns()
{
	_udp_sock = new net::udp(net::netType::SERVER);
	net::endpoint_v4 address();
}

void cbmdns::stop_mdns()
{
	if(_udp_sock)
		delete _udp_sock;
}


} /* namespace base */

extern "C" interface::iobject* create() {
	return new base::cbmdns;
}

extern "C" void destroy(interface::iobject* instance) {
	delete instance;
}

} /* namespace cossb */
