

#include "cc3200button.hpp"
#include "../../include/componentpack.hpp"
#include <tuple>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <fcntl.h>

using namespace std;
using namespace boost;

template <typename T, size_t N>
T* _begin(T(&arr)[N]) { return &arr[0]; }
template <typename T, size_t N>
T* _end(T(&arr)[N]) { return &arr[0]+N; }


USE_COMPONENT_INTERFACE(cc3200_button)

cc3200_button::cc3200_button()
:icomponent(COMPONENT(cc3200_button)),_port(8000){
	// TODO Auto-generated constructor stub

}

cc3200_button::~cc3200_button() {
	// TODO Auto-generated destructor stub
}

bool cc3200_button::setup()
{
	//cossb_broker->regist(this, "service/cc3200button");
	_host = get_profile()->get(cossb::profile::section::property, "host").asString("127.0.0.1");
	_port = get_profile()->get(cossb::profile::section::property, "port").asUInt(8000);

	cossb_log->log(cossb::log::loglevel::INFO, fmt::format("Connecting.. {}:{}",_host, _port).c_str());


	return true;
}
bool cc3200_button::run()
{
	/*if(!_client_task)
		_client_task = create_task(cc3200_button::process);*/

	return true;
}
bool cc3200_button::stop()
{
	//destroy_task(_client_task);
	//close(socket_fd);

	return true;
}
void cc3200_button::request(cossb::message::messageframe* msg)
{
	cossb_log->log(cossb::log::loglevel::INFO, "Received message");

	std::tuple<string, vector<char>> unpacked_data;
	if(cossb::message::unpack(&unpacked_data, *msg))
	{
		vector<char> data = std::get<1>(unpacked_data);
		if(std::get<0>(unpacked_data)=="rgb")
		{
			cossb_log->log(cossb::log::loglevel::INFO, fmt::format("received size : {}", data.size()).c_str());
		}
		else
			cossb_log->log(cossb::log::loglevel::ERROR, "Error");


	}
	else
		cossb_log->log(cossb::log::loglevel::ERROR, "Cannot unpacked message");

}

void cc3200_button::process()
{
	struct sockaddr_in servaddr;
	socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(socket_fd<0)
		return;

	//non-blocking mode
	if(fcntl(socket_fd, F_SETFL, O_NONBLOCK | fcntl(socket_fd, F_GETFL))==-1)
		cossb_log->log(cossb::log::loglevel::ERROR, "Cannot change non-blocking mode..");

	bzero(&servaddr,sizeof(servaddr));

	int timeout = 1;
	int intvl = 1;
	int probes = 3;
	int on = 1;

	::setsockopt(socket_fd, SOL_SOCKET, SO_KEEPALIVE, (void*) &on, sizeof(int));
	::setsockopt(socket_fd, SOL_TCP, TCP_KEEPIDLE, (void*) &timeout, sizeof(int));
	::setsockopt(socket_fd, SOL_TCP, TCP_KEEPINTVL, (void*) &intvl, sizeof(int));
	::setsockopt(socket_fd, SOL_TCP, TCP_KEEPCNT, (void*) &probes, sizeof(int));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(_host.c_str());
	servaddr.sin_port=htons(_port);

	const int buffer_len = 1024;

	while(1)
	{
		::connect(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr));	//non-blocking mode connection, always return -1

		while(1)
		{
			if(socket_fd)
			{
				char* buffer = new char[buffer_len];
				memset(buffer, 0, sizeof(char)*buffer_len);

				int len = ::recv(socket_fd, buffer, buffer_len, 0);
				if(len>0) {
					cossb_log->log(cossb::log::loglevel::INFO, fmt::format("{} Bytes received",len).c_str());
					if(len==12 && startsWith(buffer, "/START") && endsWith(buffer, len, "/END")) {
						cossb_log->log(cossb::log::loglevel::INFO, fmt::format("data : {},{}",(int)buffer[5],(int)buffer[6]).c_str());
						char packet[3] = {0,};
						if(buffer[6]==0x03)
							packet[2] = buffer[7];
						if(buffer[6]==0x0b)
							packet[0] = buffer[7];

						vector<unsigned char> data(_begin(packet), _end(packet));
						int target = cossb_broker->publish(this, "service/mbed_rgb", "rgb", data);
					}
				}
				else if(len==0)
				{
					delete []buffer;
					break;
				}

				boost::this_thread::sleep(boost::posix_time::milliseconds(10));
				delete []buffer;
			}
		}

		boost::this_thread::sleep(boost::posix_time::milliseconds(500));

	}

	close(socket_fd);

}

bool cc3200_button::endsWith(char* inString, int len, char* compString) {
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

bool cc3200_button::startsWith(char* inString, char* compString) {
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
