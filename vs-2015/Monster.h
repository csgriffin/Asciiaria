// Monster.h

#pragma once

#include "Character.h"
#include "Hero.h"

class Monster : public Character {

private:

	// Constructor.
	Monster();

	// Uhh... Unsure what this is?
	Hero *hero;

public:

	// Public constructor.
	Monster(Hero* the_hero);

	// Prototype for the event handler.
	int Monster::eventHandler(const df::Event * p_e);

	~Monster();
};

