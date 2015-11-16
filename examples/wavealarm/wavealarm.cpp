/*
 * wavealarm.cpp
 *
 *  Created on: 2015. 10. 21.
 *      Author: hwang
 */

#include "wavealarm.hpp"
#include <componentpack.hpp>
#include <ext/json.hpp>
#include <SFML/Audio.hpp>	//depends on SFML library

using json = nlohmann::json;

USE_COMPONENT_INTERFACE(wavealarm)


wavealarm::wavealarm()
:icomponent(COMPONENT(wavealarm)){
	// TODO Auto-generated constructor stub

}

wavealarm::~wavealarm() {
	// TODO Auto-generated destructor stub
}

bool wavealarm::setup()
{
	return true;
}

bool wavealarm::run()
{

	return true;
}

bool wavealarm::stop()
{
	destroy_task(_sound_task1);
	destroy_task(_sound_task2);
	return true;
}

void wavealarm::request(cossb::message::message* msg)
{
	try {
		if(!::strcmp(msg->get_topic(), "service/cc3200gpio:switch"))
		{
			if(msg->data.find("switch")!=msg->data.end())
			{
				bool sw = msg->data["switch"].get<bool>();
				if(sw) {
					if(_sound_task1)
						destroy_task(_sound_task1);

					if(!_sound_task1)
						_sound_task1 = create_task(wavealarm::process1);
				}
			}
		}
	}
	catch(std::exception& e) {
		cossb_log->log(cossb::log::loglevel::ERROR, e.what());
	}

	try {
		if(!::strcmp(msg->get_topic(), "service/cc3200button:button1"))
		{
			if(msg->data.find("button")!=msg->data.end())
			{
				bool sw = msg->data["button"].get<bool>();
				if(sw) {
					if(_sound_task2)
						destroy_task(_sound_task2);

					if(!_sound_task2)
						_sound_task2 = create_task(wavealarm::process2);
				}
			}
		}
	}
	catch(std::exception& e) {
		cossb_log->log(cossb::log::loglevel::ERROR, e.what());
	}
}

void wavealarm::process1()
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("wav/yelp.wav"))
		return;

	sf::Sound sound(buffer);
	sound.play();

	while(sound.getStatus() == sf::Sound::Playing)
	{
		// Leave some CPU time for other processes
		sf::sleep(sf::milliseconds(100));
	}
}

void wavealarm::process2()
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("wav/dingdong.wav"))
		return;

	sf::Sound sound(buffer);
	sound.play();

	while(sound.getStatus() == sf::Sound::Playing)
	{
		// Leave some CPU time for other processes
		sf::sleep(sf::milliseconds(100));
	}
}
