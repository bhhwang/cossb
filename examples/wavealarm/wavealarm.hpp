/*
 * wavealarm.hpp
 *
 *  Created on: 2015. 10. 21.
 *      Author: hwang
 */

#ifndef EXAMPLES_WAVEALARM_WAVEALARM_HPP_
#define EXAMPLES_WAVEALARM_WAVEALARM_HPP_

#include <interface.hpp>

using namespace cossb;

class wavealarm : public interface::icomponent {
public:
	wavealarm();
	virtual ~wavealarm();

	//interfaces
	bool setup();
	bool run();
	bool stop();
	void request(cossb::message::message* msg);

private:
	void process1();
	void process2();

private:
	cossb::base::task _sound_task1;
	cossb::base::task _sound_task2;
};

COMPONENT_EXPORT

#endif /* EXAMPLES_WAVEALARM_WAVEALARM_HPP_ */
