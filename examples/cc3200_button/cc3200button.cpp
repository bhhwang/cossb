

#include "cc3200button.hpp"
#include "../../include/componentpack.hpp"
#include <tuple>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <fcntl.h>
#include <logger.hpp>
#include <ext/json.hpp>

using json = nlohmann::json;

using namespace std;
using namespace boost;

template <typename T, size_t N>
T* _begin(T(&arr)[N]) { return &arr[0]; }
template <typename T, size_t N>
T* _end(T(&arr)[N]) { return &arr[0]+N; }


USE_COMPONENT_INTERFACE(cc3200button)

cc3200button::cc3200button()
:icomponent(COMPONENT(cc3200button)){



}

cc3200button::~cc3200button() {
	// TODO Auto-generated destructor stub
}

bool cc3200button::setup()
{

	return true;
}

bool cc3200button::run()
{
	if(!_client_task)
		_client_task = create_task(cc3200button::process);

	return true;
}
bool cc3200button::stop()
{
	destroy_task(_client_task);

	return true;
}
void cc3200button::request(cossb::message::message* msg)
{

	try {
	if(msg->data.size()>0) {
		string command = msg->data["command"];

		//reconnect
		if(command.compare("reconnect")==0) {
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

void cc3200button::process()
{
	const int buffer_len = 2048;
	while(1) {
		try {
			if(_client) {
				char* buffer = new char[buffer_len];
				memset(buffer, 0, sizeof(char)*buffer_len);
				int len = ::recv(_client->sockfd, buffer, buffer_len, 0);
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
	}
}

bool cc3200button::endsWith(char* inString, int len, char* compString) {
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

bool cc3200button::startsWith(char* inString, char* compString) {
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
