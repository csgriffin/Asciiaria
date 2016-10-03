#pragma once
#include <string>
#include "Sprite.h"
#include "Manager.h"
#include "Sound.h"
#include "Music.h"

namespace df {
	const int MAX_SPRITES = 1000;


	const std::string FRAMES_TOKEN = "frames";
	const std::string HEIGHT_TOKEN = "height";
	const std::string WIDTH_TOKEN = "width";
	const std::string COLOR_TOKEN = "color";
	const std::string END_FRAME_TOKEN = "end";
	const std::string END_SPRITE_TOKEN = "eof";
	
	const int MAX_SOUNDS = 128;
	const int MAX_MUSIC = 128;

	class ResourceManager :
		public Manager
	{
	private:
		Sound sound[MAX_SOUNDS];
		int sound_count;
		Music music[MAX_MUSIC];
		int music_count;

		ResourceManager();
		ResourceManager(ResourceManager const&);
		void operator=(ResourceManager const&);
		Sprite *p_sprite[MAX_SPRITES];
		int sprite_count;
	public:
		static ResourceManager &getInstance();
		int startUp();
		void shutDown();
		int loadSprite(std::string filename, std::string label);
		int unloadSprite(std::string label);
		Sprite *getSprite(std::string label) const;

		int loadSound(std::string filename, std::string label);
		int unloadSound(std::string label);
		Sound *getSound(std::string label);
		int loadMusic(std::string filename, std::string label);
		int unloadMusic(std::string label);
		Music *getMusic(std::string label);
	};
}

