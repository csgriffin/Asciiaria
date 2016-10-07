#include "Hero.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "LogManager.h"
#include "EventKeyboard.h"
#include "EventOut.h"
#include "EventMouse.h"

Hero::Hero()
{
	Character();

	// Creates a reticle.
	p_reticle = new Reticle();
	p_reticle->draw();
}

int Hero::eventHandler(const df::Event * p_e) {

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
