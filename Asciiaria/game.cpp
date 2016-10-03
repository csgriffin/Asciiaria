#include "game.h"
#include "LogManager.h"
#include "GameManager.h"
#include "TestObject.h"
#include "ResourceManager.h"


game::game()
{
}


game::~game()
{
}

int main(int argc, char * argv[])
{
	df::GameManager &game_manager = df::GameManager::getInstance();
	game_manager.startUp();
	df::LogManager &log_manager = df::LogManager::getInstance();
	log_manager.writeLog("Testing functionality");
	log_manager.writeLog("Testing '%s'", "Again");
	log_manager.writeLog("Testing '%s' '%s'", "Once", "More");

	df::ResourceManager &rm = df::ResourceManager::getInstance();
	rm.loadSprite("sprites/saucer-spr.txt", "saucer");
	rm.loadMusic("sounds/start-music.wav", "music");
	rm.loadSound("sounds/fire.wav", "fire");
	rm.getMusic("music")->play(true);

	game_manager.run();
	rm.unloadMusic("music");
	rm.unloadSound("fire");
	rm.unloadSprite("saucer");
	return 0;
}
