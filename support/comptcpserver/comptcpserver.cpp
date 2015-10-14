/*
 * comptcpserver.cpp
 *
 *  Created on: Aug 26, 2015
 *      Author: odroid
 */

#include "comptcpserver.hpp"
#include "../../include/componentpack.hpp"
#include "sessionmanager.hpp"

COMPONENT_INSTANCE(comptcpserver)
COMPONENT_CREATE(comptcpserver)
COMPONENT_DESTROY

comptcpserver::comptcpserver()
:interface::icomponent(COMPONENT(comptcpserver)),_acceptor(boost::asio::ip::tcp::acceptor(_io_service))
{
	session_manager::instance();
}

comptcpserver::~comptcpserver()
{
	session_manager::destroy();
}

bool comptcpserver::setup()
{
	_port = 9090;
	return true;
}

bool comptcpserver::run()
{
	if(_acceptor.is_open())
		_acceptor.close();

	try {
		asio::ip::address ipaddr = asio::ip::address_v4::from_string(_host);
		_acceptor.open(asio::ip::tcp::endpoint(ipaddr, _port).protocol());
		_acceptor.bind(asio::ip::tcp::endpoint(ipaddr, _port));
	} catch (boost::system::error_code& e) {
		cossb_log->log(log::loglevel::ERROR, fmt::format("Server Error : {}", e.message()).c_str());
	}

	if(!_server_task)
		_server_task = base::create_task(tcpserver::listen);

	return true;
}

bool comptcpserver::stop()
{
	_io_service.stop();

	if(_acceptor.is_open())
		_acceptor.close();

	destroy_task(_server_task);
	_server_task = nullptr;

	return true;
}

void comptcpserver::request(cossb::message::messageframe* msg)
{

}

void comptcpserver::accept()
{
	_acceptor.listen();

	session_uuid id;
	session_manager::instance()->generate_session_id(id);
	session_manager::instance()->insert(id, new session(id, _acceptor.get_io_service(), this));

	_acceptor.async_accept(session_manager::get()->get_session(id)->socket(),
								boost::bind(&tcpserver::handle_accept, this,
								session_manager::get()->get_session(id), boost::asio::placeholders::error));
}

void comptcpserver::listen()
{
	accept();
	_io_service.run();
}

void comptcpserver::handle_accept(tcp_session* session, const boost::system::error_code& error)
{

}

