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

class libhttpserver
{
public:
	libhttpserver(int port=80);
	virtual ~libhttpserver();

	/**
	 * @brief	start http server
	 */
	void run();

private:
	static int request_handle (void* cls, struct MHD_Connection* connection,
	                      const char* url, const char* method,
	                      const char* version, const char* upload_data,
	                      size_t* upload_data_size, void** con_cls);

private:
	int _port;

	struct MHD_Daemon* daemon = nullptr;
};

#endif /* SUPPORT_COMPHTTPSERVER_LIBHTTPSERVER_HPP_ */
