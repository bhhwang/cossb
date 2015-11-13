/*
 * cc3200gpio.hpp
 *
 *  Created on: 2015. 11. 11.
 *      Author: hwang
 */

#ifndef EXAMPLES_CC3200_GPIO_CC3200GPIO_HPP_
#define EXAMPLES_CC3200_GPIO_CC3200GPIO_HPP_

#include <interface.hpp>
#include <net/tcp.hpp>

class cc3200gpio : public cossb::interface::icomponent {
public:
	cc3200gpio();
	virtual ~cc3200gpio();

	bool setup();
	bool run();
	bool stop();
	void request(cossb::message::message* msg);

private:
	void process();

private:
	fd_set _status;
	cossb::base::task _client_task;
	cossb::net::tcp* _client = nullptr;
	cossb::profile::device_desc* _desc = nullptr;

};

COMPONENT_EXPORT

#endif /* EXAMPLES_CC3200_GPIO_CC3200GPIO_HPP_ */
