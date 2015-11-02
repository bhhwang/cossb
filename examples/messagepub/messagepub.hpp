/**
 * @file	messagepub.hpp
 * @brief	message publish 발행 예제
 * @author	Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 	2015. 9. 5
 * @details 특정 서비스 컴포넌트에게 메세지를 발행(publish)하는 예제
 */

#ifndef _COSSB_EXAMPLES_MESSAGEPUB_HPP_
#define _COSSB_EXAMPLES_MESSAGEPUB_HPP_

#include "../../include/interface.hpp"

class messagepub : public cossb::interface::icomponent {
public:
	messagepub();
	virtual ~messagepub();

	bool setup();
	bool run();
	bool stop();
	void request(cossb::message::message* msg);

private:
	void pub();

private:
	cossb::base::task _pub_task;
};

COMPONENT_EXPORT

#endif /* _COSSB_EXAMPLES_MESSAGEPUB_HPP_ */
