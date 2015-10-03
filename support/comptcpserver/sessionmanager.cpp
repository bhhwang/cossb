/*
 * sessionmanager.cpp
 *
 *  Created on: 2015. 10. 3.
 *      Author: hwang
 */

#include "sessionmanager.hpp"

session_manager::session_manager() {


}

session_manager::~session_manager() {
	_container.clear();
}

void session_manager::close_session(const session_uuid uuid)
{
	auto itr = _container.find(uuid);
	if(itr!=_container.end())
	{
		if(itr->second->socket().is_open())
			itr->second->socket().close();

		delete itr->second;
		_container.erase(itr);
	}
}

void session_manager::insert(session_uuid& uuid, session* session)
{
	_container.insert(pair<session_uuid, session*>(uuid, session));
}

session* session_manager::get_session(session_uuid uuid)
{
	auto ses = _container.find(uuid);
	if(ses!=_container.end())
		return ses->second;
	else
		return nullptr;
}

int session_manager::size()
{
	return _container.size();
}

void session_manager::generate_session_id(session_uuid& id)
{
	uuid_t	guid;
	uuid_generate(guid);	//16byte

	char ch_guid[64];
	memset(ch_guid, 0x00, sizeof(ch_guid));
	uuid_unparse(guid, ch_guid);
	id = string(ch_guid);
}
