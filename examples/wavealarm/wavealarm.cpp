/*
 * wavealarm.cpp
 *
 *  Created on: 2015. 10. 21.
 *      Author: hwang
 */

#include "wavealarm.hpp"
#include "../../include/componentpack.hpp"
#include <SFML/Audio.hpp>	//depends on SFML library

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
	//string file = get_profile()->get(profile::section::property, "wavfile").asString("dingdong.wav");
	/*cossb_log->log(cossb::log::loglevel::INFO, "setup wave");
	sf::Music music;
	if(music.openFromFile("./wav/dingdong.wav")) {
		music.play();
	}
	else
		cossb_log->log(cossb::log::loglevel::ERROR, "cannot open file");*/

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("wav/dingdong.wav"))
		return false;

	// Display sound informations
	//std::cout << "dingdong.wav:" << std::endl;
	//std::cout << " " << buffer.getDuration().asSeconds() << " seconds"       << std::endl;
	//std::cout << " " << buffer.getSampleRate()           << " samples / sec" << std::endl;
	//std::cout << " " << buffer.getChannelCount()         << " channels"      << std::endl;

	// Create a sound instance and play it
	/*sf::Sound sound(buffer);
	sound.play();

	// Loop while the sound is playing
	while (sound.getStatus() == sf::Sound::Playing)
	{
		// Leave some CPU time for other processes
		sf::sleep(sf::milliseconds(100));

		// Display the playing position
		std::cout << "\rPlaying... " << std::fixed << std::setprecision(2) << sound.getPlayingOffset().asSeconds() << " sec   ";
		std::cout << std::flush;
	}
	std::cout << std::endl << std::endl;*/

	return true;
}

bool wavealarm::run()
{

	return true;
}

bool wavealarm::stop()
{
	return true;
}

void wavealarm::request(cossb::message::message* msg) const
{

}
