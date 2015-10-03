/**
 * @file		sessionmanager.hpp
 * @brief		TCP Server session manager
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 10. 3
 * @details	TCP session manager
 */

#ifndef SUPPORT_COMPTCPSERVER_SESSIONMANAGER_HPP_
#define SUPPORT_COMPTCPSERVER_SESSIONMANAGER_HPP_

#include "../../include/arch/singleton.hpp"
#include <boost/unordered_map.hpp>
#include <uuid/uuid.h>
#include "typedef.hpp"

using namespace cossb;

typedef boost::unordered_map<session_uuid, session*> session_container;

class session_manager : public arch::singleton<session_manager> {
public:
	session_manager();
	virtual ~session_manager();

	/**
	 * @brief	close session
	 */
	void close_session(const session_uuid uuid);

	/**
	 * @brief	insert new session in session container
	 */
	void insert(session_uuid& uuid, session* session);

	/**
	 * @brief	getting session from uuid
	 */
	session* get_session(session_uuid uuid);

	/**
	 * @brief	generate session id
	 */
	void generate_session_id(session_uuid& id);

	/**
	 * @brief	getting container size
	 */
	int size();

private:
	session_container _container;

};

#endif /* SUPPORT_COMPTCPSERVER_SESSIONMANAGER_HPP_ */
