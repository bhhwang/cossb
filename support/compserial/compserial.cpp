/*
 * compserial.cpp
 *
 *  Created on: 2015. 8. 25.
 *      Author: hwang-linux
 */

#include "compserial.hpp"
#include "../../include/componentpack.hpp"

COMPONENT_INSTANCE(compserial)
COMPONENT_CREATE(compserial)
COMPONENT_DESTROY

compserial::compserial()
:interface::icomponent(COMPONENT(compserial)){


}

compserial::~compserial() {
	if(_serial)
		delete _serial;
}


bool compserial::setup()
{
	string port = get_profile()->get(profile::section::property, "port").asString("/dev/ttyS0");
	int baudrate = get_profile()->get(profile::section::property, "baudrate").asInt(19200);
	string topic = get_profile()->get(profile::section::info, "publish").asString("com/serial");

	//cossb_log->log(log::loglevel::INFO, fmt::format("Port/Baudrate : {}-{}",port,baudrate).c_str());

	if(!_serial)
		_serial = new libserial();

	if(!_serial->open(port.c_str(), baudrate))
	{
		delete _serial;
		_serial = nullptr;
		//cossb_log->log(log::loglevel::ERROR, fmt::format("Cannot open the serial port {}", port).c_str());
		return false;
	}

	return true;
}

bool compserial::run()
{
	if(!_read_task)
		_read_task = create_task(compserial::read_task_proc);

	return true;
}

bool compserial::stop()
{
	destroy_task(_read_task);

	if(_serial) {
		_serial->close();
		delete _serial;
		_serial = nullptr;
	}
	return true;
}

void compserial::request(cossb::message::message* msg)
{
	cout << "request" << endl;
}

void compserial::read_task_proc()
{
	while(1)
	{
		if(_serial)
		{
			const unsigned int buffer_len = 2048;
			unsigned char* buffer = new unsigned char[buffer_len];
			int read = _serial->read(buffer, sizeof(unsigned char)*buffer_len);

			if(read>0) {
				vector<unsigned char> data;
				data.assign(buffer, buffer+read*sizeof(unsigned char));

				//publish here
			}

			delete []buffer;
		}

		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
}

void compserial::print_hex(unsigned char* data, int len)
{
	string res="";
	char const hex[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
	for(int i=0;i<len; ++i)
	{
		const char c = data[i];
		res.append(&hex[(c&0xf0)>>4], 1);
		res.append(&hex[c&0x0f],1);
		res.append(" ");
	}

	//cossb_log->log(log::loglevel::INFO, fmt::format("Received Data : {}", res).c_str());

}


