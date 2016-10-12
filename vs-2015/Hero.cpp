// Engine includes.
#include "EventCollision.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventOut.h"
#include "EventStep.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Arrow.h"
#include "Monster.h"

// Game includes.
#include "Hero.h"

void Hero::fire(df::Vector target)
{
	if (fire_countdown > 0) {
		return;
	}
	fire_countdown = fire_slowdown;

	df::WorldManager &w_m = df::WorldManager::getInstance();

	Arrow *p = new Arrow(getPosition());
	if (target.getX() > getPosition().getX() - w_m.getView().getCorner().getX()) {
		p->setVelocity(df::Vector(1, ((float)(target.getY() - getPosition().getY() + w_m.getView().getCorner().getY())) / ((float)(target.getX() - getPosition().getX() + w_m.getView().getCorner().getX()))));
	}
	else {
		p->setVelocity(df::Vector(-1, -1 * ((float)(target.getY() - getPosition().getY() + w_m.getView().getCorner().getY())) / ((float)(target.getX() - getPosition().getX() + w_m.getView().getCorner().getX()))));
	}
}

void Hero::spawn() {
	if (spawn_timer > 0) {
		spawn_timer--;
		return;
	}
	spawn_timer = max_spawn_timer;

	Monster *theEnemy = new Monster(this);
	theEnemy->setPosition(df::Vector(getPosition().getX() + 80, 3));
}

Hero::Hero()
{
	Character();

	// Gets each instance of the Dragonfly managers.
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::Sprite *p_temp_sprite;

	// Gets the ship sprite.
	p_temp_sprite = resource_manager.getSprite("hero");

	// Checks if the requested sprite exists. If not, returns an error!
	if (!p_temp_sprite) log_manager.writeLog("Hero::Hero(): Warning! Sprite '%s' not found", "hero");

	// Otherwise... It sets the sprite, slowdown, and transparency of this object.
	else {

		setSprite(p_temp_sprite);

		// Slows down the sprite by 3. ( 30FPS / 3 = 10FPS )
		setSpriteSlowdown(3);

		// Makes the sprite transparent.
		setTransparency();
	}

	// Registers interest in keyboard, step, and mouse events.
	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);
	registerInterest(df::MOUSE_EVENT);

	max_spawn_timer = 100;
	spawn_timer = max_spawn_timer;

	fire_slowdown = 15;
	fire_countdown = fire_slowdown;

	// Set the object type and starting location.
	setType("Hero");
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	df::Vector p(7, world_manager.getBoundary().getVertical() / 4);
	setPosition(p);

	// Creates a reticle.
	p_reticle = new Reticle();
	p_reticle->draw();
}

int Hero::eventHandler(const df::Event * p_e) {
	if (p_e->getType() == df::MOUSE_EVENT) {
		const df::EventMouse *p_s = dynamic_cast <const df::EventMouse *> (p_e);
		if ((p_s->getMouseButton() == df::Mouse::RIGHT) && (p_s->getMouseAction() == df::CLICKED)) {
			fire(p_s->getMousePosition());
		}
		Character::eventHandler(p_e);
		return 1;
	}
	if (p_e->getType() == df::STEP_EVENT) {
		spawn();

		fire_countdown--;
		if (fire_countdown < 0) {
			fire_countdown = 0;
		}
		Character::eventHandler(p_e);
		return 1;
	}
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard *p_s = dynamic_cast <const df::EventKeyboard *> (p_e);
		if (p_s->getKeyboardAction() == df::KEY_DOWN) {
			if (p_s->getKey() == df::Keyboard::RIGHTARROW) {
				if (getJumpCount() == 0) {
					setVelocity(df::Vector(.5, 0));
					return 1;
				}
			}
			if (p_s->getKey() == df::Keyboard::LEFTARROW) {
				if (getJumpCount() == 0) {
					setVelocity(df::Vector(-.5, 0));
					return 1;
				}
			}
		}
		if (p_s->getKeyboardAction() == df::KEY_PRESSED) {
			if (p_s->getKey() == df::Keyboard::UPARROW) {
				jump();
				return 1;
			}
		}
		if (p_s->getKeyboardAction() == df::KEY_RELEASED) {
			if (p_s->getKey() == df::Keyboard::RIGHTARROW) {
				setVelocity(df::Vector(0, getVelocity().getY()));
				return 1;
			}
			if (p_s->getKey() == df::Keyboard::LEFTARROW) {
				setVelocity(df::Vector(0, getVelocity().getY()));
				return 1;
			}
		}
	}
	if (Character::eventHandler(p_e) == 1) {
		return 1;
	}
	return 0;
}

Hero::~Hero()
{
	df::ResourceManager &r_m = df::ResourceManager::getInstance();
	r_m.getSound("heroDeath")->play();
	r_m.getMusic("music")->stop();
	r_m.getMusic("endMusic")->play();

	Object::~Object();
}
