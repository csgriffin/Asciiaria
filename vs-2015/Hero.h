// Hero.h

#pragma once

// Game includes.
#include "Character.h"
#include "Reticle.h"

class Hero : public Character {

private:

	// Reticle information.
	Reticle *p_reticle;
	int fire_slowdown;
	int fire_countdown;
	void fire(df::Vector target);

	int spawn_timer;
	int max_spawn_timer;

	void spawn();

public:

	// Constructor.
	Hero();

	// Prototype for the event handler.
	int eventHandler(const df::Event * p_e);

	~Hero();
};

