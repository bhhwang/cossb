/*
 * wavealarm.hpp
 *
 *  Created on: 2015. 10. 21.
 *      Author: hwang
 */

#ifndef EXAMPLES_WAVEALARM_WAVEALARM_HPP_
#define EXAMPLES_WAVEALARM_WAVEALARM_HPP_

#include "../../include/interface/icomponent.hpp"

using namespace cossb;

class wavealarm : public interface::icomponent {
public:
	wavealarm();
	virtual ~wavealarm();

	//interfaces
	bool setup();
	bool run();
	bool stop();
	void request(cossb::message::message* msg) const;

private:

};

COMPONENT_EXPORT

#endif /* EXAMPLES_WAVEALARM_WAVEALARM_HPP_ */
