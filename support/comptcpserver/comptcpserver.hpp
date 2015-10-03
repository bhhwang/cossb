/**
 * @file		comptcpserver.hpp
 * @brief		TCP Server component
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 8. 25
 * @details		TCP server component (multiple client accessible)
 */


#ifndef SUPPORT_COMPONENT_COMPTCPSERVER_HPP_
#define SUPPORT_COMPONENT_COMPTCPSERVER_HPP_

#include "../../include/interface.hpp"
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

using namespace cossb;
using namespace boost;

class session;
class comptcpserver : public interface::icomponent {
public:
	comptcpserver();
	virtual ~comptcpserver();

	bool setup();
	bool run();
	bool stop();
	void request(message::message* msg);

private:
	void accept();
	void listen();
	void handle_accept(session* session, const boost::system::error_code& error);

private:
	boost::asio::io_service _io_service;
	boost::asio::ip::tcp::acceptor _acceptor;
	base::task _server_task;
	string _host;
	string _topic;
	unsigned int _port = 9090;
};

COMPONENT_EXPORT

#endif /* SUPPORT_COMPONENT_COMPTCPSERVER_HPP_ */
