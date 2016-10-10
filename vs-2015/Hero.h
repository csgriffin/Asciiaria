// Hero.h

#pragma once

// Game includes.
#include "Character.h"
#include "Reticle.h"

class Hero : public Character {

private:

	// Reticle information.
	Reticle *p_reticle;

public:

	// Constructor.
	Hero();

	// Prototype for the event handler.
	int eventHandler(const df::Event * p_e);
};

