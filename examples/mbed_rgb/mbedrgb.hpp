/**
 * @file	mbed_rgb.hpp
 * @brief	ARM mbed RGB LED control component 예제
 * @author	Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 	2015. 10. 2
 * @details	ARM mbed RGB LED control service component example, ARM의 mbed 하드웨어를 통해 application board에서 제공하는 RGB LED를 제어하는 서비스 컴포넌트 예제
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
	void request(cossb::message::message* msg);

private:
	bool connect(const char* ipaddr, unsigned short port);

	void process();

	cossb::base::task _client_task;

private:

	string _host;
	unsigned short _port;

};

COMPONENT_EXPORT

#endif /* EXAMPLES_MBED_RGB_MBEDRGB_HPP_ */
