#pragma once
#include "Character.h"
#include "Reticle.h"
class Hero :
	public Character
{
private:

	// Reticle information.
	Reticle *p_reticle;

public:
	Hero();
	int eventHandler(const df::Event * p_e);
};

