#pragma once
#include "Object.h"
class Character :
	public df::Object
{
private:
	float gravity;
	int jump_count;
	int jump_slowdown;
public:
	Character();
	void setGravity(float new_gravity);
	float getGravity() const;
	int eventHandler(const df::Event *p_e);
	void jump();
	int getJumpCount() const;
};

