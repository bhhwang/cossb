/*
 * messagetest.hpp
 *
 *  Created on: 2015. 10. 7.
 *      Author: hwang
 */

#ifndef EXAMPLES_MESSAGETEST_MESSAGETEST_HPP_
#define EXAMPLES_MESSAGETEST_MESSAGETEST_HPP_

#include "../../include/interface/icomponent.hpp"

using namespace cossb;

class messagetest : public interface::icomponent {
public:
	messagetest();
	virtual ~messagetest();

	//interfaces
	bool setup();
	bool run();
	bool stop();
	void request(cossb::message::message* msg);

};

COMPONENT_EXPORT

#endif /* EXAMPLES_MESSAGETEST_MESSAGETEST_HPP_ */
