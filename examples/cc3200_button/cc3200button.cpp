

#include "cc3200button.hpp"
#include <componentpack.hpp>
/*#include <tuple>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <fcntl.h>
#include <logger.hpp>*/
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
	if(_desc)
		delete _desc;
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

void cc3200button::process()
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

						if(data.find("command")!=data.end() && data.find("button1")!=data.end() && data.find("button2")!=data.end()) {
							if(!::strcmp(data["command"].get<string>().c_str(), "buttonread")) {
								bool btn1 = data["button1"].get<bool>();
								bool btn2 = data["button2"].get<bool>();

								if(_button1!=btn1) {
									cossb::message::message msg(this, cossb::message::msg_type::EVENT);
									msg.set_topic("service/cc3200button/button1");
									msg["button"] = btn1;
									cossb_broker->publish(msg);
									_button1 = btn1;
									cossb_log->log(cossb::log::loglevel::INFO, "published");
								}

								if(_button2!=btn2) {
									cossb::message::message msg(this, cossb::message::msg_type::EVENT);
									msg.set_topic("service/cc3200button/button2");
									msg["button"] = btn2;
									cossb_broker->publish(msg);
									_button2 = btn2;
								}

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

