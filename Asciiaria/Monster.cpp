#include "Monster.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "LogManager.h"
#include "EventKeyboard.h"
#include "EventOut.h"


Monster::Monster(Hero the_hero)
{
	hero = &the_hero;
	Character();
}

int Monster::eventHandler(const df::Event * p_e)
{
	df::LogManager &lm = df::LogManager::getInstance();
	lm.writeLog("Got to eventHandler");
	if (p_e->getType() == df::STEP_EVENT) {
		Character::eventHandler(p_e);
		if (hero->getPosition().getX() > getPosition().getX()) {
			setVelocity(df::Vector(.05, getVelocity().getY()));
		}
		if (hero->getPosition().getX() < getPosition().getX()) {
			setVelocity(df::Vector(-.05, getVelocity().getY()));
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