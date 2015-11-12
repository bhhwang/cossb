/*
 * cc3200gpio.cpp
 *
 *  Created on: 2015. 11. 11.
 *      Author: hwang
 */

#include "cc3200gpio.hpp"
#include <componentpack.hpp>

USE_COMPONENT_INTERFACE(cc3200gpio)

cc3200gpio::cc3200gpio()
:icomponent(COMPONENT(cc3200gpio)) {
	// TODO Auto-generated constructor stub

}

cc3200gpio::~cc3200gpio() {
	// TODO Auto-generated destructor stub
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
		if(msg->data.size()>0) {
			string command = msg->data["command"];

			//reconnect
			if(command.compare("auth")==0) {
				if(_client)
					delete _client;

				string host = msg->data["address"];
				int port = msg->data["port"];

				_client = new cossb::net::tcp(cossb::net::netType::CLIENT, host.c_str(), port);
				_client->async_connect();
				cossb_log->log(cossb::log::loglevel::INFO, fmt::format("Connected to {}:{}",host, port).c_str());
			}
		}
		else
			cossb_log->log(cossb::log::loglevel::ERROR, "Empty Message Data");
		} catch(std::exception& e) {
			cossb_log->log(cossb::log::loglevel::ERROR, e.what());
	}
}

void cc3200gpio::process()
{
	/*const int buffer_len = 2048;
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

						if(data.find("button1")!=data.end())
							if(data["button1"]==true) {
								cossb::message::message msg(this);
								msg["command"] = "test";
								cossb_log->log(cossb::log::loglevel::INFO, msg.get_topic());
								cossb_broker->publish(msg);
							}
						if(data.find("button2")!=data.end())
							if(data["button2"]==true) {
								cossb::message::message msg(this);
								cossb_broker->publish(msg);
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
	}*/
}
