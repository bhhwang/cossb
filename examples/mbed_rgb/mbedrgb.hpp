/**
 * @file	mbed_rgb.hpp
 * @brief	ARM mbed RGB LED control component ����
 * @author	Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 	2015. 10. 2
 * @details	ARM mbed RGB LED control service component example, ARM�� mbed �ϵ��� ���� application board���� �����ϴ� RGB LED�� �����ϴ� ���� ������Ʈ ����
 */

#ifndef EXAMPLES_MBED_RGB_MBEDRGB_HPP_
#define EXAMPLES_MBED_RGB_MBEDRGB_HPP_

#include "../../include/interface.hpp"
#include <string>

using namespace std;

class mbed_rgb : public cossb::interface::icomponent {
public:
	mbed_rgb();
	virtual ~mbed_rgb();

	bool setup();
	bool run();
	bool stop();
	void request(cossb::message::messageframe* msg);

private:
	bool connect(const char* ipaddr, unsigned short port);
	bool endsWith(char* inString, int len, char* compString);
	bool startsWith(char* inString, char* compString);
	void process();

private:
	int socket_fd;
	string _host;
	unsigned short _port;
	cossb::base::task _client_task;


};

COMPONENT_EXPORT

#endif /* EXAMPLES_MBED_RGB_MBEDRGB_HPP_ */