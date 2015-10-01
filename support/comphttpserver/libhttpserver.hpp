/**
 * @file		libhttpserver.hpp
 * @brief		HTTP Server library
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 9. 29
 * @details	Light-weight HTTP server library using microhttpd-dev
 */

#ifndef SUPPORT_COMPHTTPSERVER_LIBHTTPSERVER_HPP_
#define SUPPORT_COMPHTTPSERVER_LIBHTTPSERVER_HPP_

#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <microhttpd.h>

#define DEFAULT_PORT	8888

class libhttpserver
{
public:
	libhttpserver();
	virtual ~libhttpserver();

	void listen(unsigned int port);

	void run();

private:
};

#endif /* SUPPORT_COMPHTTPSERVER_LIBHTTPSERVER_HPP_ */
