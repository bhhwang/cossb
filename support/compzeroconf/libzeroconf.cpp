/*
 * libzeroconf.cpp
 *
 *  Created on: 2015. 9. 12.
 *      Author: hwang
 */

#include "libzeroconf.hpp"
#include <iostream>

using namespace std;


libzeroconf::libzeroconf() {
	// TODO Auto-generated constructor stub

}

libzeroconf::~libzeroconf() {
	// TODO Auto-generated destructor stub
}

void libzeroconf::browse()
{
	//allocate main loop object
	if(!(_poll = avahi_simple_poll_new())) {
		cout << "Fail to create simpol poll object" << endl;
		return;
	}

	//allocate a new client
}
