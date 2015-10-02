/*
 * libhttpserver.cpp
 *
 *  Created on: 2015. 9. 29.
 *      Author: hwang
 */

#include "libhttpserver.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int libhttpserver::request_handle (void *cls, struct MHD_Connection *connection,
                      const char *url, const char *method,
                      const char *version, const char *upload_data,
                      size_t *upload_data_size, void **con_cls)
{
	std::ifstream file("./html/index.html", ifstream::in);
	std::stringstream buffer;
	if(file) {
		buffer << file.rdbuf();
		file.close();
	}
	else {
		buffer << "<html><body>Cannot find html file</body></html>";
	}

	struct MHD_Response* response = MHD_create_response_from_buffer(buffer.str().size(), (void*)(buffer.str().c_str()), MHD_RESPMEM_MUST_FREE);

	int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
	MHD_destroy_response(response);

	return ret;
}


libhttpserver::libhttpserver(int port):_port(port) {


}

libhttpserver::~libhttpserver() {
	MHD_stop_daemon(daemon);
}

void libhttpserver::run()
{
	daemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, _port, NULL, NULL, &libhttpserver::request_handle, this, MHD_OPTION_END);
	if(!daemon)
		return;
}


