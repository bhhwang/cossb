/*
 * session.hpp
 *
 *  Created on: Aug 26, 2015
 *      Author: odroid
 */

#ifndef SESSION_HPP_
#define SESSION_HPP_

#include "../../include/arch/singleton.hpp"
#include <boost/unordered_map.hpp>
#include "typedef.hpp"
#include <uuid/uuid.h>

using namespace boost;



class session {
public:
	session();
	virtual ~session();
};


#endif /* SESSION_HPP_ */
