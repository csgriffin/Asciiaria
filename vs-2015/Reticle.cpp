// Reticle.cpp
// Code stripped directly from Saucer Shoot.
// TODO: Make the reticle more unique?

// Engine includes.
#include "GraphicsManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "EventMouse.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"
#include "ResourceManager.h"

// Game includes.
#include "Reticle.h"
#include "Tile.h"

Reticle::Reticle() {

	// Set type of object.
	setType("Reticle");

	// Set solidness to SPECTRAL.
	setSolidness(df::SPECTRAL);

	// Set to the highest layer.
	setAltitude(df::MAX_ALTITUDE);

	// Register interest in moure events.
	registerInterest(df::MOUSE_EVENT);

	// Get the world manager.
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	// Set starting location in the middle of window.
	df::Vector p(world_manager.getBoundary().getHorizontal() / 2,
		world_manager.getBoundary().getVertical() / 2);
	setPosition(p);
}

int Reticle::eventHandler(const df::Event *p_e) {

	// Check for any mouse events.
	if (p_e->getType() == df::MOUSE_EVENT) {
		const df::EventMouse *p_mouse_event =
			dynamic_cast <const df::EventMouse *> (p_e);

		// If the mouse has moved.
		if (p_mouse_event->getMouseAction() == df::MOVED) {

			// Change location to new mouse position.
			setPosition(p_mouse_event->getMousePosition());
			return 1;
		}

		// Get graphics and world manager.
		df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
		df::WorldManager &world_manager = df::WorldManager::getInstance();

		if ((p_mouse_event->getMouseAction() == df::CLICKED) && (p_mouse_event->getMouseButton() == df::Mouse::RIGHT)) {

			// Get all the objects and find the desired tile.
			df::ObjectList all_objects;
			all_objects = world_manager.getAllObjects();
			df::ObjectListIterator li(&all_objects);

			for (li.first(); li.isDone(); li.next()) {

				df::Object *p_current_object = li.currentObject();

				df::LogManager &log_manager = df::LogManager::getInstance();
				log_manager.writeLog("Mouse Position: (%d, %d) and Tile Position: (%d, %d)", p_mouse_event->getMousePosition().getX(), p_mouse_event->getMousePosition().getY(),
					p_current_object->getPosition().getX(), p_current_object->getPosition().getY());

				if (p_current_object->getType() == "tile") {

					// Test code to see what the position of the tile and mouse are.
					log_manager.writeLog("Mouse Position: (%d, %d) and Tile Position: (%d, %d)", p_mouse_event->getMousePosition().getX(), p_mouse_event->getMousePosition().getY(),
						p_current_object->getPosition().getX(), p_current_object->getPosition().getY());

					if (p_current_object->getPosition() == p_mouse_event->getMousePosition()) {

						Tile *p_casted_object =
							dynamic_cast <Tile *> (p_current_object);

						if (p_casted_object->getTileType() == AIR) {

							// Get resource manager.
							df::ResourceManager &resource_manager = df::ResourceManager::getInstance();

							//world_manager.markForDelete(this);
							p_casted_object->setTileType(DIRT);
							p_casted_object->setSprite(resource_manager.getSprite("dirt"));
							p_casted_object->setSolidness(df::HARD);
						}
					}
				}
			}

		}

		if ((p_mouse_event->getMouseAction() == df::CLICKED) && (p_mouse_event->getMouseButton() == df::Mouse::LEFT)) {

			// Get all the objects and find the desired tile.
			df::ObjectList all_objects;
			all_objects = world_manager.getAllObjects();
			df::ObjectListIterator li(&all_objects);

			for (li.first(); li.isDone(); li.next()) {

				df::Object *p_current_object = li.currentObject();

				df::LogManager &log_manager = df::LogManager::getInstance();
				log_manager.writeLog("Mouse Position: (%d, %d) and Tile Position: (%d, %d)", p_mouse_event->getMousePosition().getX(), p_mouse_event->getMousePosition().getY(),
					p_current_object->getPosition().getX(), p_current_object->getPosition().getY());

				if (p_current_object->getType() == "tile") {

					// Test code to see what the position of the tile and mouse are.
					log_manager.writeLog("Mouse Position: (%d, %d) and Tile Position: (%d, %d)", p_mouse_event->getMousePosition().getX(), p_mouse_event->getMousePosition().getY(),
						p_current_object->getPosition().getX(), p_current_object->getPosition().getY());

					if (p_current_object->getPosition() == p_mouse_event->getMousePosition()) {

						Tile *p_casted_object =
							dynamic_cast <Tile *> (p_current_object);

						if (p_casted_object->getTileType() == DIRT) {

							//world_manager.markForDelete(this);
							p_casted_object->setTileType(AIR);
							p_casted_object->setSprite(nullptr);
							p_casted_object->setSolidness(df::SPECTRAL);
						}
					}
				}
			}

		}

		return 1;
	}

	return 0;
}

// Draw reticle on window.
void Reticle::draw() {

	// Get the graphics manager.
	df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();

	// Draw the character in position.
	graphics_manager.drawCh(getPosition(), RETICLE_CHAR, df::RED);
}