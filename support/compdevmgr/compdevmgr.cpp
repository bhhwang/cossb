/*
 * compdevmgr.cpp
 *
 *  Created on: 2015. 10. 27.
 *      Author: hwang
 */

#include "compdevmgr.hpp"
#include <net/exception.hpp>
//#include <ext/json.hpp>
#include <manager.hpp>
#include <componentpack.hpp>

#define MAX_BUFFER_SIZE		2048

USE_COMPONENT_INTERFACE(compdevmgr)

compdevmgr::compdevmgr()
:interface::icomponent(COMPONENT(compdevmgr)) {
	_dev_container = new deviceinfo_container;
}

compdevmgr::~compdevmgr() {

	if(_udp_recv)
		delete _udp_recv;

	if(_dev_container) {
		_dev_container->clear();
		delete _dev_container;
	}
}

bool compdevmgr::setup()
{
	string group_address = get_profile()->get(cossb::profile::section::property, "address").asString("225.0.0.37");
	int group_port = get_profile()->get(cossb::profile::section::property, "port").asInt(21928);

	try
	{
		if(!_udp_recv)
		{
			_udp_recv = new cossb::net::multicast;
			_udp_recv->create(group_address.c_str(), group_port);
		}
	}
	catch(net::exception& e) {
		if(_udp_recv) {
			delete _udp_recv;
			_udp_recv = nullptr;
		}

		cossb_log->log(log::loglevel::ERROR, e.what(), log::color::COLOR);
	}

	return true;
}

bool compdevmgr::run()
{
	if(_udp_recv) {
		_rcv_buffer = new char[MAX_BUFFER_SIZE];
		_response_task = create_task(compdevmgr::response);
	}
	return true;
}

bool compdevmgr::stop()
{
	if(_udp_recv)
		destroy_task(_response_task);

	if(_rcv_buffer)
		delete []_rcv_buffer;

	return true;
}

void compdevmgr::request(cossb::message::message* msg)
{
	//nothing to do
}

void compdevmgr::response()
{
	struct sockaddr_in	client_addr;
	unsigned int _client_sockaddr_size = sizeof(client_addr);

	while(1) {
		memset(_rcv_buffer, 0, sizeof(char)*MAX_BUFFER_SIZE);
		int nBytes = recvfrom(*_udp_recv->get_sock(), _rcv_buffer, MAX_BUFFER_SIZE, 0 , (struct sockaddr*)&client_addr, (socklen_t*)&_client_sockaddr_size);
		if(nBytes>0) {
			try {
				profile::device_desc desc(_rcv_buffer, nBytes);

				if(_dev_container->find(desc)==_dev_container->end()) {
					cossb_log->log(log::loglevel::INFO, fmt::format("New device {} requests a permission to access service",desc.devicename).c_str(), log::color::COLOR);
					cossb_log->log(log::loglevel::INFO, fmt::format("Registered UUID {} ",desc.unique_id.str()).c_str());
					_dev_container->insert(deviceinfo_container::value_type(desc, client_addr));

					if(!desc.component.empty()) {
						if(cossb_component_manager->install(desc.component.c_str())) {
							cossb_component_manager->run(desc.component.c_str());

							//publish
							//cossb::message::message msg(this, cossb::message::msg_type::EVENT);
							//msg["command"] = "announce";
							//msg["address"] = inet_ntoa(client_addr.sin_addr);
							//msg["port"] = devinfo["port"];
							//cossb_broker->publish(msg);
						}
					}
				}

			/*if(devinfo.find("devicename")!= devinfo.end()) {
				string devname = devinfo["devicename"];
				if(_dev_container->find(devname)==_dev_container->end()) {
				cossb_log->log(log::loglevel::INFO, fmt::format("New device {} requests a permission to access service.", devinfo["devicename"], inet_ntoa(client_addr.sin_addr)).c_str());

				if(devinfo.find("componentname")!=devinfo.end()) {
					string component_name = devinfo["componentname"];
					if(!component_name.empty())
						if(cossb_component_manager->install(component_name.c_str())) {
							cossb_component_manager->run(component_name.c_str());

							_dev_container->insert(deviceinfo_container::value_type(devname, client_addr));

							//message publish
							cossb::message::message msg(this);
							msg["command"] = "reconnect";
							msg["address"] = inet_ntoa(client_addr.sin_addr);
							msg["port"] = devinfo["port"];
							cossb_broker->publish(msg);
						}
				}
				}
			}*/

			}
			catch(cossb::profile::exception& e) {
				cossb_log->log(log::loglevel::ERROR, e.what(), log::color::COLOR);
			}

		}


		boost::this_thread::sleep(boost::posix_time::microsec(100));
	}
}
