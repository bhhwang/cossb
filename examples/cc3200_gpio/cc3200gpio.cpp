/*
 * cc3200gpio.cpp
 *
 *  Created on: 2015. 11. 11.
 *      Author: hwang
 */

#include "cc3200gpio.hpp"
#include <componentpack.hpp>
#include <ext/json.hpp>
using json = nlohmann::json;

USE_COMPONENT_INTERFACE(cc3200gpio)

cc3200gpio::cc3200gpio()
:icomponent(COMPONENT(cc3200gpio)) {
	// TODO Auto-generated constructor stub

}

cc3200gpio::~cc3200gpio() {
	if(_desc)
		delete _desc;
}

bool cc3200gpio::setup()
{
	return true;
}

bool cc3200gpio::run()
{

	if(!_client_task)
		_client_task = create_task(cc3200gpio::process);

	return true;
}

bool cc3200gpio::stop()
{
	destroy_task(_client_task);
	return true;
}

void cc3200gpio::request(cossb::message::message* msg)
{
	try {
		if(!::strcmp(msg->get_topic(), "service/compdevmgr:announce")) {
			if(_desc) {
				delete _desc;
				_desc = nullptr;
			}

			if(msg->data.find("profile")!=msg->data.end()) {
				string profile = msg->data["profile"];
				_desc = new cossb::profile::device_desc(profile.c_str(), profile.size());
			}

			string address = "";
			if(msg->data.find("ipaddress")!=msg->data.end()) {
				address = msg->data["ipaddress"].get<string>();
			}

			if(_desc) {
				_client = new cossb::net::tcp(cossb::net::netType::CLIENT, address.c_str(), _desc->port);
				_client->async_connect();
				cossb_log->log(cossb::log::loglevel::INFO, fmt::format("Connected to {}:{}",address, _desc->port).c_str());
			}
		}
		} catch(std::exception& e) {
			cossb_log->log(cossb::log::loglevel::ERROR, e.what());
	}
}

void cc3200gpio::process()
{
	const int buffer_len = 2048;
	while(1) {
		try {
			if(_client) {
				char* buffer = new char[buffer_len];
				memset(buffer, 0, sizeof(char)*buffer_len);
				int len = ::recv(*_client->get_sock(), buffer, buffer_len, 0);
				if(len>0) {
					cossb_log->log(cossb::log::loglevel::INFO, fmt::format("{}",buffer).c_str());

					try {
						json data = json::parse(buffer);

						if(data.find("command")!=data.end() && data.find("switch")!=data.end()){
							if(!::strcmp(data["command"].get<string>().c_str(), "io")) {
								bool sw = data["switch"].get<bool>();

								//create message to publish
								cossb::message::message msg(this, cossb::message::msg_type::EVENT);
								msg.set_topic("service/cc3200gpio/switch");
								msg["switch"] = sw;
								cossb_broker->publish(msg);
								cossb_log->log(cossb::log::loglevel::INFO, "published");
							}
						}

					} catch(std::exception& e) {
						cossb_log->log(cossb::log::loglevel::ERROR, e.what());
					}
				}

				delete []buffer;
			}
		} catch(thread_interrupted&) {
			break;
		}

		boost::this_thread::sleep(boost::posix_time::milliseconds(100));
	}
}
