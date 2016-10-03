#pragma once
#include "Vector.h"
#include <string>
#include "Event.h"
#include "Sprite.h"
#include "Box.h"

namespace df {
	enum Solidness {
		HARD,
		SOFT,
		SPECTRAL,
	};

	class Object
	{
	private:
		Box box;

		Sprite *p_sprite;
		bool sprite_center;
		int sprite_index;
		int sprite_slowdown;
		int sprite_slowdown_count;

		int id;
		std::string type;
		Vector position;
		Vector direction;
		float speed;
		int altitude;
		Solidness solidness;

	public:
		int setAltitude(int new_altitude);
		int getAltitude() const;
		virtual void draw();
		Object();
		virtual ~Object();
		void setId(int new_id);
		int getId() const;
		void setType(std::string new_type);
		std::string getType() const;
		void setPosition(Vector new_pos);
		Vector getPosition() const;
		virtual int eventHandler(const Event *p_e);
		void setSpeed(float speed);
		float getSpeed() const;
		void setDirection(Vector new_direction);
		Vector getDirection() const;
		void setVelocity(Vector new_velocity);
		Vector getVelocity() const;
		Vector predictPosition();
		bool isSolid() const;
		int setSolidness(Solidness new_solid);
		Solidness getSolidness() const;

		void setSprite(Sprite *p_new_sprite, bool set_box = true);
		Sprite *getSprite() const;
		void setCentered(bool centered = true);
		bool isCentered() const;
		void setSpriteIndex(int new_sprite_index);
		int getSpriteIndex() const;
		void setSpriteSlowdown(int new_sprite_slowdown);
		int getSpriteSlowdown() const;
		void setSpriteSlowdownCount(int new_sprite_slowdown_count);
		int getSpriteSlowdownCount() const;

		void setBox(Box new_box);
		Box getBox() const;
	};
}

