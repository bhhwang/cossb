

#include "cc3200button.hpp"
#include "../../include/componentpack.hpp"
#include <tuple>

using namespace std;

COMPONENT_INSTANCE(cc3200_button)
COMPONENT_CREATE(cc3200_button)
COMPONENT_DESTROY

cc3200_button::cc3200_button()
:icomponent(COMPONENT(cc3200_button)){
	// TODO Auto-generated constructor stub

}

cc3200_button::~cc3200_button() {
	// TODO Auto-generated destructor stub
}

bool cc3200_button::setup()
{
	cossb_broker->regist(this, "service/cc3200button");
	 _host = "127.0.0.1";
	 _port = 9090;
	return true;
}
bool cc3200_button::run()
{
	/*if(!_client_task)
		_client_task = create_task(mbed_rgb::process);*/

	return true;
}
bool cc3200_button::stop()
{
	//destroy_task(_client_task);

	return true;
}
void cc3200_button::request(cossb::message::message* msg)
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


}
