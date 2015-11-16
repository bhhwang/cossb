/*
 * mbedrgb.cpp
 *
 *  Created on: 2015. 10. 2.
 *      Author: hwang
 */

#include "mbedrgb.hpp"
#include <componentpack.hpp>
#include <ext/json.hpp>
using json = nlohmann::json;

using namespace std;

USE_COMPONENT_INTERFACE(mbedrgb)

template <typename T, size_t N>
T* _begin(T(&arr)[N]) { return &arr[0]; }
template <typename T, size_t N>
T* _end(T(&arr)[N]) { return &arr[0]+N; }

mbedrgb::mbedrgb()
:icomponent(COMPONENT(mbedrgb)){
	// TODO Auto-generated constructor stub

}

mbedrgb::~mbedrgb() {
	if(_desc)
		delete _desc;
}

bool mbedrgb::setup()
{
	return true;
}
bool mbedrgb::run()
{
	if(!_client_task)
		_client_task = create_task(mbedrgb::process);

	return true;
}
bool mbedrgb::stop()
{
	destroy_task(_client_task);

	return true;
}
void mbedrgb::request(cossb::message::message* msg)
{
	//device
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

	//control
	try {
		if(!::strcmp(msg->get_topic(), "service/cc3200gpio:switch"))
		{
			if(msg->data.find("switch")!=msg->data.end())
			{
				bool sw = msg->data["switch"].get<bool>();
				if(sw) {
					string packet = "{\"r\":1, \"g\":0, \"b\":0}";
					if(_client)
						::send(*_client->get_sock(), packet.c_str(), packet.size(), 0);
				}
				else {
					string packet = "{\"r\":0, \"g\":1, \"b\":0}";
					if(_client)
						::send(*_client->get_sock(), packet.c_str(), packet.size(), 0);
				}
			}
		}
	}
	catch(std::exception& e) {
		cossb_log->log(cossb::log::loglevel::ERROR, e.what());
	}

}

void mbedrgb::process()
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
								msg.set_topic("service/cc3200gpio:switch");
								msg["switch"] = sw;
								cossb_broker->publish(msg);
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
/*
bool mbedrgb::endsWith(char* inString, int len, char* compString) {
  int compLength = strlen(compString);

  //compare the last "compLength" values of the inString
  for (int i = 0; i < compLength; i++) {
    char a = inString[(len - 1) - i];
    char b = compString[(compLength - 1) - i];
    if (a != b) {
      return false;
    }
  }
  return true;
}

bool mbedrgb::startsWith(char* inString, char* compString) {
  int compLength = strlen(compString);

  //compare the last "compLength" values of the inString
  for (int i = 0; i < compLength; i++) {
    char a = inString[i];
    char b = compString[i];
    if (a != b) {
      return false;
    }
  }
  return true;
}
*/
