/*
 * compdevmgr.cpp
 *
 *  Created on: 2015. 10. 27.
 *      Author: hwang
 */

#include "compdevmgr.hpp"
#include <exception.hpp>
#include <ext/json.hpp>
#include <manager.hpp>

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
	string group_address = get_profile()->get(cossb::profile::section::property, "address").asString("225.0.0.37");
	int group_port = get_profile()->get(cossb::profile::section::property, "port").asInt(21928);

	try {
	if(!_udp_multicast) {
		_udp_multicast = new cossb::net::udpmulticast(net::netType::HOST, group_address.c_str(), group_port);
		cossb_log->log(log::loglevel::INFO, fmt::format("Ready to allow remote device via {}:{}",group_address, group_port).c_str());
	}

	} catch(net::exception& e) {
		if(_udp_multicast)
			delete _udp_multicast;

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
	//nothing to do
}

void compdevmgr::response()
{
	using json = nlohmann::json;
	struct sockaddr_in	client_addr;
	unsigned int _client_sockaddr_size = sizeof(client_addr);

	char* rcv_buffer = new char[2048];
	while(1) {
		memset(rcv_buffer, 0, sizeof(char)*2048);
		int nBytes = recvfrom(_udp_multicast->sockfd, rcv_buffer, 2048, 0 , (struct sockaddr*)&client_addr, (socklen_t*)&_client_sockaddr_size);
		if(nBytes>0) {
			try {
			json devinfo = json::parse(rcv_buffer);
			if(devinfo.find("devicename")!= devinfo.end())
				cossb_log->log(log::loglevel::INFO, fmt::format("Device {} requests a permission to access service.", devinfo["devicename"], inet_ntoa(client_addr.sin_addr)).c_str());

			if(devinfo.find("componentname")!=devinfo.end()) {
				string component_name = devinfo["componentname"];
				if(!component_name.empty())
					cossb_component_manager->install(component_name.c_str());
			}


			/*for(json::iterator it = devinfo.begin(); it!=devinfo.end();++it) {
				cout << it.key() << ":" << it.value() << endl;
			}*/
			} catch(std::exception& e) {
				cossb_log->log(log::loglevel::ERROR, e.what());
			}

			/*cossb_log->log(log::loglevel::INFO, fmt::format("received {}bytes from {}:{}", nBytes, inet_ntoa(client_addr.sin_addr), client_addr.sin_port).c_str());
			if(sendto(_udp_multicast->sockfd, rcv_buffer, nBytes, 0, (struct sockaddr *)&client_addr, sizeof(client_addr))!=nBytes)
				cossb_log->log(log::loglevel::ERROR, "Cannot send");
			else
				cossb_log->log(log::loglevel::INFO, fmt::format("send to {}:{}", inet_ntoa(client_addr.sin_addr), client_addr.sin_port).c_str());*/
		}


		boost::this_thread::sleep(boost::posix_time::microsec(100));
	}
	delete []rcv_buffer;
}
