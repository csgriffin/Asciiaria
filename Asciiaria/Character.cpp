#include "Character.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "LogManager.h"
#include "EventKeyboard.h"

Character::Character()
{
	setSolidness(df::HARD);
	gravity = .1;
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
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		if ((getVelocity().getX() != (float) 0) || (getVelocity().getY() != (float) 0)) {
			lm.writeLog("SAUCER COLLISION");
			//const df::EventCollision *p_s = dynamic_cast <const df::EventCollision *> (p_e);
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
				setVelocity(df::Vector(getVelocity().getX(), getVelocity().getY() - (float)2));
				return 1;
			}
		}
		if (p_s->getKeyboardAction() == df::KEY_RELEASED) {
			//setVelocity(df::Vector(0, getVelocity().getY()));
		}
	}
	return 0;
}
