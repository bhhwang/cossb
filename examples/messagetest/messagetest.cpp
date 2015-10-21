/*
 * messageserialization.cpp
 *
 *  Created on: 2015. 10. 7.
 *      Author: hwang
 */

#include "messagetest.hpp"

#include "../../include/componentpack.hpp"

COMPONENT_INSTANCE(messagetest)
COMPONENT_CREATE(messagetest)
COMPONENT_DESTROY

messagetest::messagetest()
:icomponent(COMPONENT(messagetest)){


}

messagetest::~messagetest() {

}

bool messagetest::setup()
{
	//cossb_broker->regist(this, get_profile()->get(profile::section::info, "publish").asString("undefined"));
	return true;
}

bool messagetest::run()
{
	cossb::message::message msg(this);

	msg["pi"] = 3.141;
	msg["happy"] = true;
	msg["name"] = "Niels";
	msg["nothing"] = nullptr;
	msg["answer"]["everything"] = 42;
	msg["list"] = { 1, 0, 2 };
	msg["object"] = { {"currency", "USD"}, {"value", 42.89} };

	cossb_broker->publish(msg);


	return true;
}

bool messagetest::stop()
{
	return true;
}

void messagetest::request(cossb::message::message* msg) const
{

}
