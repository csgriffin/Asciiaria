#pragma once
#include <string>
#include <SFML/Audio.hpp>

namespace df {
	class Sound
	{
	private:
		sf::Sound sound;
		sf::SoundBuffer sound_buffer;
		std::string label;

	public:
		Sound();
		~Sound();

		int loadSound(std::string filename);
		void setLabel(std::string new_label);
		std::string getLabel() const;
		void play(bool loop = false);
		void stop();
		void pause();
		sf::Sound getSound() const;
	};
}

