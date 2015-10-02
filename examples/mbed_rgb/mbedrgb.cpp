/*
 * mbedrgb.cpp
 *
 *  Created on: 2015. 10. 2.
 *      Author: hwang
 */

#include "mbedrgb.hpp"
#include "../../include/componentpack.hpp"

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
	return true;
}
bool mbed_rgb::run()
{
	return true;
}
bool mbed_rgb::stop()
{
	return true;
}
void mbed_rgb::request(cossb::message::message* msg)
{

	/*std::tuple<string, vector<unsigned char>> unpacked_data;
	if(message::unpack(&unpacked_data, *msg)==error::errorcode::PLUN_NO_ERROR) {
		if(std::get<0>(unpacked_data)=="raw") {
			vector<unsigned char> data = std::get<1>(unpacked_data);

			for(auto& c:data)
				_queue.push_back(c);

			process();

		}
		else {
			get_logger()->error("Undefined Message was received.");
		}
	}*/
}
