/*
 * mbedrgb.cpp
 *
 *  Created on: 2015. 10. 2.
 *      Author: hwang
 */

#include "mbedrgb.hpp"
#include "../../include/componentpack.hpp"
#include <tuple>

using namespace std;

COMPONENT_INSTANCE(mbed_rgb)
COMPONENT_CREATE(mbed_rgb)
COMPONENT_DESTROY

mbed_rgb::mbed_rgb()
:icomponent(COMPONENT(mbed_rgb)){
	// TODO Auto-generated constructor stub

}

mbed_rgb::~mbed_rgb() {
	// TODO Auto-generated destructor stub
}

bool mbed_rgb::setup()
{
	cossb_broker->regist(this, "service/mbed_rgb");
	 _host = "127.0.0.1";
	 _port = 9090;
	return true;
}
bool mbed_rgb::run()
{
	/*if(!_client_task)
		_client_task = create_task(mbed_rgb::process);*/

	return true;
}
bool mbed_rgb::stop()
{
	//destroy_task(_client_task);

	return true;
}
void mbed_rgb::request(cossb::message::message* msg)
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

void mbed_rgb::process()
{

	/*boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(_host.c_str()), _port);
	boost::system::error_code connect_error;
	boost::asio::ip::tcp::socket socket(_io_service);
	socket.connect(endpoint, connect_error);*/

	/*while(1)
	{
		if(connect_error)
			break;

		boost::system::error_code ignored_error;
		//socket.write_some(boost::asio::buffer(request_message, 81), ignored_error);
	}*/
}

