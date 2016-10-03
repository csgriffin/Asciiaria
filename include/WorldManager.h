#pragma once
#include "Manager.h"
#include "ObjectList.h"
#include "Box.h"

namespace df {

	const int MAX_ALTITUDE = 4;

	class WorldManager:
		public Manager
	{

	private:
		Object *p_view_following;

		Box boundary;
		Box view;

		WorldManager();
		WorldManager(WorldManager const&);
		void operator=(WorldManager const&);

		ObjectList updates;
		ObjectList deletions;
	public:
		void draw();
		static WorldManager &getInstance();
		int startUp();
		void shutDown();
		int insertObject(Object *p_o);
		int removeObject(Object *p_o);
		ObjectList getAllObjects() const;
		ObjectList objectsOfType(std::string type) const;
		void update();
		int markForDelete(Object *p_o);
		ObjectList isCollision(Object *p_o, Vector where) const;
		int moveObject(Object *p_o, Vector where);

		void setBoundary(Box new_boundary);
		Box getBoundary() const;
		void setView(Box new_view);
		Box getView() const;

		void setViewPosition(Vector view_pos);
		int setViewFollowing(Object *p_new_view_following);
	};
}

