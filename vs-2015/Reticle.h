// Reticle.h
// Code stripped directly from Saucer Shoot.
// TODO: Make this code more unique?

#pragma once

// Engine includes.
#include "Object.h"

// Defines the character used for the reticle.
#define RETICLE_CHAR '+'

class Reticle : public df::Object {

public:

	// Constructor.
	Reticle();

	// Prototype to draw reticle to screen.
	void draw();

	// Prototype for the event handler.
	int eventHandler(const df::Event *p_e);
};
