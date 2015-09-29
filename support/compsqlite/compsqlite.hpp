/**
 * @file		compsqlite.hpp
 * @brief		Sqlite component
 * @author		Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 		2015. 9. 29
 * @details	Sqlite database component
 */


#ifndef SUPPORT_COMPSQLITE_COMPSQLITE_HPP_
#define SUPPORT_COMPSQLITE_COMPSQLITE_HPP_

#include "../../include/interface.hpp"

using namespace cossb;

class compsqlite : public interface::icomponent {
public:
	compsqlite();
	virtual ~compsqlite();

	bool setup();
	bool run();
	bool stop();
	void request(cossb::message::message* msg);
};

COMPONENT_EXPORT

#endif /* SUPPORT_COMPSQLITE_COMPSQLITE_HPP_ */
