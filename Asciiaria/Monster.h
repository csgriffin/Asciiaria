#pragma once
#include "Character.h"
#include "Hero.h"

class Monster :
	public Character
{
private:
	Monster();
	Hero *hero;
public:
	Monster(Hero* the_hero);
	int Monster::eventHandler(const df::Event * p_e);
};

