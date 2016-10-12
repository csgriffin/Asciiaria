#include "Arrow.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"



Arrow::Arrow(df::Vector hero_pos)
{
	df::ResourceManager &r_m = df::ResourceManager::getInstance();
	r_m.getSound("fire")->play();
	df::Vector p(hero_pos.getX(), hero_pos.getY());
	setPosition(p);
	setSprite(r_m.getSprite("arrow"));
	setSolidness(df::SOFT);
	setType("Arrow");
	setVelocity(df::Vector(1, 0));
	setAltitude(4);
}

void Arrow::out()
{
	df::WorldManager &world_manager = df::WorldManager::getInstance();
	world_manager.markForDelete(this);
}

void Arrow::hit(const df::EventCollision * p_collision_event)
{
	if ((p_collision_event->getObject1()->getType() == "Monster") || (p_collision_event->getObject2()->getType() == "Monster")) {
		df::WorldManager &world_manager = df::WorldManager::getInstance();
		world_manager.markForDelete(p_collision_event->getObject1());
		world_manager.markForDelete(p_collision_event->getObject2());
		return;
	}
	if ((p_collision_event->getObject1()->getType() != "Hero") && (p_collision_event->getObject2()->getType() != "Hero")) {
		df::WorldManager &world_manager = df::WorldManager::getInstance();
		world_manager.markForDelete(this);
	}
}

int Arrow::eventHandler(const df::Event * p_e)
{
	/*if (p_e->getType() == df::STEP_EVENT) {
		df::WorldManager &world_manager = df::WorldManager::getInstance();
		df::ObjectList *ol = &world_manager.objectsInBox(getBox());

		df::ObjectListIterator oli = df::ObjectListIterator::ObjectListIterator(ol);
		oli.first();
		while (!oli.isDone()) {
			if (oli.currentObject()->getType() == "Monster") {
				world_manager.markForDelete(oli.currentObject());
				world_manager.markForDelete(this);
			}
			oli.next();
		}
		return 1;
	}*/
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision *p_collision_event = dynamic_cast <const df::EventCollision *> (p_e);
		hit(p_collision_event);
		return 1;
	}
	return 0;
}
