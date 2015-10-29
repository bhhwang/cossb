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
#include <componentpack.hpp>

#define MAX_BUFFER_SIZE		2048

USE_COMPONENT_INTERFACE(compdevmgr)

compdevmgr::compdevmgr()
:interface::icomponent(COMPONENT(compdevmgr)) {
	_dev_container = new deviceinfo_container;

}

compdevmgr::~compdevmgr() {
	if(_udp_multicast)
		delete _udp_multicast;

	if(_dev_container) {
		_dev_container->clear();
		delete _dev_container;
	}
}

bool compdevmgr::setup()
{
	string group_address = get_profile()->get(cossb::profile::section::property, "address").asString("225.0.0.37");
	int group_port = get_profile()->get(cossb::profile::section::property, "port").asInt(21928);

	try {
		if(!_udp_multicast) {
			_udp_multicast = new cossb::net::udpmulticast(net::netType::HOST, group_address.c_str(), group_port);
			cossb_log->log(log::loglevel::INFO, fmt::format("Multicast group address {}:{}",group_address, group_port).c_str());
		}

	}
	catch(net::exception& e) {
		if(_udp_multicast)
			delete _udp_multicast;

		cossb_log->log(log::loglevel::ERROR, e.what());
	}

	return true;
}

bool compdevmgr::run()
{
	_rcv_buffer = new char[MAX_BUFFER_SIZE];
	_response_task = create_task(compdevmgr::response);
	return true;
}

bool compdevmgr::stop()
{
	destroy_task(_response_task);

	if(_rcv_buffer)
		delete []_rcv_buffer;

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

	while(1) {
		memset(_rcv_buffer, 0, sizeof(char)*MAX_BUFFER_SIZE);
		int nBytes = recvfrom(_udp_multicast->sockfd, _rcv_buffer, MAX_BUFFER_SIZE, 0 , (struct sockaddr*)&client_addr, (socklen_t*)&_client_sockaddr_size);
		if(nBytes>0) {
			try {
			json devinfo = json::parse(_rcv_buffer);

			if(devinfo.find("devicename")!= devinfo.end()) {
				string devname = devinfo["devicename"];
				if(_dev_container->find(devname)==_dev_container->end()) {
				cossb_log->log(log::loglevel::INFO, fmt::format("New device {} requests a permission to access service.", devinfo["devicename"], inet_ntoa(client_addr.sin_addr)).c_str());

				if(devinfo.find("componentname")!=devinfo.end()) {
					string component_name = devinfo["componentname"];
					if(!component_name.empty())
						if(cossb_component_manager->install(component_name.c_str())) {
							_dev_container->insert(deviceinfo_container::value_type(devname, client_addr));

							//message publish
							cossb::message::message msg(this);
							msg["cmd"] = "auth";
							msg["address"] = inet_ntoa(client_addr.sin_addr);
							msg["port"] = client_addr.sin_port;
							cossb_broker->publish(msg);
							cossb_log->log(log::loglevel::INFO, "Publish");
						}
				}
				}
			}

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
}
