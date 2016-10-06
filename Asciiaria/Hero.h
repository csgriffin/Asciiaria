#pragma once
#include "Character.h"
class Hero :
	public Character
{
private:
public:
	Hero();
	int eventHandler(const df::Event * p_e);
};

