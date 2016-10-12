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
	df::Vector p(40, 5);
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
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_s = dynamic_cast <const df::EventCollision *> (p_e);
		if ((p_s->getObject1() == hero) || (p_s->getObject2() == hero)) {
			df::WorldManager &w_m = df::WorldManager::getInstance();
			w_m.markForDelete(hero);
			return 1;
		}
	}
	else {
		if (Character::eventHandler(p_e) == 1) {
			return 1;
		}
	}
	return 0;
}

Monster::~Monster()
{
	df::ResourceManager &r_m = df::ResourceManager::getInstance();
	r_m.getSound("monsterDeath")->play();
	Object::~Object();
}
