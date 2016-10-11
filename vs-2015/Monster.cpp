// Monster.cpp

// Engine includes.
#include "EventCollision.h"
#include "EventKeyboard.h"
#include "EventStep.h"
#include "EventOut.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes.
#include "Monster.h"


Monster::Monster(Hero* the_hero)
{

	// Gets each instance of the Dragonfly managers.
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::Sprite *p_temp_sprite;

	// Gets the ship sprite.
	p_temp_sprite = resource_manager.getSprite("monster");

	// Checks if the requested sprite exists. If not, returns an error!
	if (!p_temp_sprite) log_manager.writeLog("Monster::Monster(Hero*): Warning! Sprite '%s' not found", "monster");

	// Otherwise... It sets the sprite, slowdown, and transparency of this object.
	else {

		setSprite(p_temp_sprite);

		// Slows down the sprite by 3. ( 30FPS / 3 = 10FPS )
		setSpriteSlowdown(3);

		// Makes the sprite transparent.
		setTransparency();
	}

	// Set the object type and starting location.
	setType("Monster");
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	df::Vector p(15, world_manager.getBoundary().getVertical() / 4);
	setPosition(p);

	registerInterest(df::STEP_EVENT);

	hero = the_hero;
	Character();
}

int Monster::eventHandler(const df::Event * p_e)
{
	df::LogManager &lm = df::LogManager::getInstance();
	lm.writeLog("Got to eventHandler");
	if (p_e->getType() == df::STEP_EVENT) {

		const df::EventStep *p_s = dynamic_cast <const df::EventStep *> (p_e);
		if ((p_s->getStepCount() % 2) == 1) {
			if (getJumpCount() == 0) {
				if (hero->getPosition().getX() > getPosition().getX()) {
					setVelocity(df::Vector(.4, 0));
				}
				else if (hero->getPosition().getX() < getPosition().getX()) {
					setVelocity(df::Vector(-.4, 0));
				}
			}
		}
		else {
			Character::eventHandler(p_e);
		}
		return 1;
	}
	else {
		if (Character::eventHandler(p_e) == 1) {
			return 1;
		}
	}
	return 0;
}