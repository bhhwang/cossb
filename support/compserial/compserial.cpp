/*
 * compserial.cpp
 *
 *  Created on: 2015. 8. 25.
 *      Author: hwang-linux
 */

#include "compserial.hpp"
#include "../../include/component_util.hpp"

COMPONENT_INSTANCE(compserial)
COMPONENT_CREATE(compserial)
COMPONENT_DESTROY

compserial::compserial()
:icomponent(COMPONENT(compserial)){


}

compserial::~compserial() {
	if(_serial)
		delete _serial;
}


bool compserial::setup()
{
	string port = get_profile()->get(profile::section::property, "port").asString("/dev/ttyS0");
	int baudrate = get_profile()->get(profile::section::property, "baudrate").asInt(19200);

	cossb_log->log(log::loglevel::INFO, fmt::format("Port/Baudrate : {}/{}",port,baudrate).c_str());

	if(!_serial)
		_serial = new libserial();

	if(!_serial->open(port.c_str(), baudrate))
	{
		delete _serial;
		_serial = nullptr;
		cossb_log->log(log::loglevel::ERROR, fmt::format("Cannot open the serial port {}", port).c_str());
		return false;
	}

	return true;
}

bool compserial::run()
{
	cout << "run" << endl;
	return true;
}

bool compserial::stop()
{
	if(_serial) {
		_serial->close();
		delete _serial;
		_serial = nullptr;
	}
	return true;
}

void compserial::request(cossb::interface::imessage* msg)
{
	cout << "request" << endl;
}

void compserial::read_task_proc()
{

}
