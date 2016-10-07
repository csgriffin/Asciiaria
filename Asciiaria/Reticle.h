// Compile only once!
#ifndef SS_RETICLE_H
#define SS_RETICLE_H

// Engine includes.
#include "Object.h"

// Defines the character used for the reticle.
#define RETICLE_CHAR '+'

class Reticle : public df::Object {

public:
	Reticle();

	// Prototype to draw reticle to screen.
	void draw();

	// Prototype for the event handler.
	int eventHandler(const df::Event *p_e);
};

#endif