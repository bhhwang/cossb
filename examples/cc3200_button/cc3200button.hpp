/**
 * @file	cc3200button.hpp
 * @brief	cc3200 TI launchpad button example
 * @author	Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 	2015. 10. 2
 * @details	TI cc3200 launchpad button service example
 */

#ifndef EXAMPLES_CC3200BUTTON_CC3200BUTTON_HPP_
#define EXAMPLES_CC3200BUTTON_CC3200BUTTON_HPP_

#include "../../include/interface.hpp"
#include <string>

using namespace std;

class cc3200button : public cossb::interface::icomponent {
public:
	cc3200button();
	virtual ~cc3200button();

	bool setup();
	bool run();
	bool stop();
	void request(cossb::message::message* msg) const;

private:
	bool connect(const char* ipaddr, unsigned short port);

	void process();
	bool endsWith(char* inString, int len, char* compString);
	bool startsWith(char* inString, char* compString);
	cossb::base::task _client_task;

private:
	int socket_fd = -1;
	fd_set _status;
	string _host;
	unsigned short _port;

};

COMPONENT_EXPORT

#endif /* EXAMPLES_CC3200_BUTTON_CC3200BUTTON_HPP_ */
