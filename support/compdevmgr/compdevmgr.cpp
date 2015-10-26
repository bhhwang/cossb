/*
 * compdevmgr.cpp
 *
 *  Created on: 2015. 10. 27.
 *      Author: hwang
 */

#include "compdevmgr.hpp"
#include <exception.hpp>

USE_COMPONENT_INTERFACE(compdevmgr)

compdevmgr::compdevmgr()
:interface::icomponent(COMPONENT(compdevmgr)) {
	// TODO Auto-generated constructor stub

}

compdevmgr::~compdevmgr() {
	if(_udp_multicast)
		delete _udp_multicast;
}

bool compdevmgr::setup()
{
	try {
	if(!_udp_multicast)
		_udp_multicast = new cossb::net::udpmulticast(net::netType::HOST, "225.0.0.37", 21928);

	} catch(net::exception& e) {
		cossb_log->log(log::loglevel::ERROR, e.what());
	}

	return true;
}

bool compdevmgr::run()
{
	_response_task = create_task(compdevmgr::response);
	return true;
}

bool compdevmgr::stop()
{
	destroy_task(_response_task);
	return true;
}

void compdevmgr::request(cossb::message::message* msg) const
{

}

void compdevmgr::response()
{
	struct sockaddr_in	_client_sockaddr;
	unsigned int _client_sockaddr_size = sizeof(_client_sockaddr);

	char* _rcv_buffer = new char[2048];
	while(1) {
		memset(_rcv_buffer, 0, sizeof(char)*2048);
		int nBytes = recvfrom(_udp_multicast->sockfd, _rcv_buffer, 2048, 0 , (struct sockaddr*)&_client_sockaddr, (socklen_t*)&_client_sockaddr_size);
		if(nBytes>0) {
			cossb_log->log(log::loglevel::INFO, fmt::format("received {}bytes from {}", nBytes, inet_ntoa(_client_sockaddr.sin_addr)).c_str());
		}


		boost::this_thread::sleep(boost::posix_time::microsec(100));
	}
	delete []_rcv_buffer;
}
