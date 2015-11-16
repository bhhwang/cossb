/**
 * @file	mbed_rgb.hpp
 * @brief	ARM mbed RGB LED control component ����
 * @author	Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 	2015. 10. 2
 * @details	ARM mbed RGB LED control service component example, ARM�� mbed �ϵ��� ���� application board���� �����ϴ� RGB LED�� �����ϴ� ���� ������Ʈ ����
 */

#ifndef EXAMPLES_MBED_RGB_MBEDRGB_HPP_
#define EXAMPLES_MBED_RGB_MBEDRGB_HPP_

#include <interface.hpp>
#include <net/tcp.hpp>

using namespace std;

class mbedrgb : public cossb::interface::icomponent {
public:
	mbedrgb();
	virtual ~mbedrgb();

	bool setup();
	bool run();
	bool stop();
	void request(cossb::message::message* msg);

private:
	//bool connect(const char* ipaddr, unsigned short port);
	//bool endsWith(char* inString, int len, char* compString);
	//bool startsWith(char* inString, char* compString);
	void process();

private:
	cossb::base::task _client_task;
	cossb::net::tcp* _client = nullptr;
	cossb::profile::device_desc* _desc = nullptr;


};

COMPONENT_EXPORT

#endif /* EXAMPLES_MBED_RGB_MBEDRGB_HPP_ */
