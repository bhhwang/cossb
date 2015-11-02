/**
 * @file	helloworld.hpp
 * @brief	hello world component ����
 * @author	Byunghun Hwang<bhhwang@nsynapse.com>
 * @date 	2015. 8. 7
 * @details	hello world ����, �⺻ ������Ʈ�� ���� Ȯ��
 */

#ifndef _COSSB_EXAMPLE_HELLOWORLD_HPP_
#define _COSSB_EXAMPLE_HELLOWORLD_HPP_

#include <interface.hpp>

class helloworld : public cossb::interface::icomponent {
public:
	helloworld();
	virtual ~helloworld();

	bool setup();
	bool run();
	bool stop();
	void request(cossb::message::message* msg);

private:

private:

};

COMPONENT_EXPORT

#endif /* _COSSB_EXAMPLE_HELLOWORLD_HPP_ */

