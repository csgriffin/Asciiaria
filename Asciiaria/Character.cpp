#include "Character.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "LogManager.h"
#include "EventKeyboard.h"
#include "EventOut.h"

Character::Character()
{
	setSolidness(df::HARD);
	gravity = .1;
	jump_count = 0;
	jump_slowdown = 50;
	df::Object();
}

void Character::setGravity(float new_gravity)
{
	gravity = new_gravity;
}

float Character::getGravity() const
{
	return gravity;
}

int Character::eventHandler(const df::Event * p_e)
{
	df::LogManager &lm = df::LogManager::getInstance();
	lm.writeLog("Got to eventHandler");
	if (p_e->getType() == df::STEP_EVENT) {
		//const df::EventStep *p_s = dynamic_cast <const df::EventStep *> (p_e);
		setVelocity(df::Vector(getVelocity().getX(), getVelocity().getY() + getGravity()));
		if (jump_count > 0) {
			jump_count--;
		}
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		if (getVelocity().getX() != (float)0) {
			setVelocity(df::Vector(0, getVelocity().getY()));
			return 1;
		}
		if (getVelocity().getY() != (float)0) {
			setVelocity(df::Vector(getVelocity().getX(), 0));
			return 1;
		}
	}
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard *p_s = dynamic_cast <const df::EventKeyboard *> (p_e);
		if (p_s->getKeyboardAction() == df::KEY_DOWN) {
			if (p_s->getKey() == df::Keyboard::RIGHTARROW) {
				setPosition(df::Vector(getPosition().getX() + 1, getPosition().getY()));
				return 1;
			}
			if (p_s->getKey() == df::Keyboard::LEFTARROW) {
				setPosition(df::Vector(getPosition().getX() - 1, getPosition().getY()));
				return 1;
			}
		}
		if (p_s->getKeyboardAction() == df::KEY_PRESSED) {
			if (p_s->getKey() == df::Keyboard::UPARROW) {
				jump();
				return 1;
			}
		}
		if (p_s->getKeyboardAction() == df::KEY_RELEASED) {
			//setVelocity(df::Vector(0, getVelocity().getY()));
		}
	}
	if (p_e->getType() == df::OUT_EVENT) {
		if (getVelocity().getX() != (float)0) {
			setVelocity(df::Vector(0, getVelocity().getY()));
			return 1;
		}
		if (getVelocity().getY() != (float)0) {
			setVelocity(df::Vector(getVelocity().getX(), 0));
			return 1;
		}
	}
	return 0;
}

void Character::jump() {
	if (jump_count > 0) {
		jump_count--;
		return;
	}
	else {
		jump_count = jump_slowdown;
		setVelocity(df::Vector(getVelocity().getX(), getVelocity().getY() - (float)2));
	}
}