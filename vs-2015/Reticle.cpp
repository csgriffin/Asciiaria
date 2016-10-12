// Reticle.cpp
// Code stripped directly from Saucer Shoot.
// TODO: Make the reticle more unique?

// Engine includes.
#include "GraphicsManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "EventMouse.h"

// Game includes.
#include "Reticle.h"

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
	}

	return 0;
}

// Draw reticle on window.
void Reticle::draw() {

	// Get the graphics manager.
	df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
	df::WorldManager &w_m = df::WorldManager::getInstance();

	// Draw the character in position.
	df::Vector p = df::Vector(getPosition().getX() + w_m.getView().getCorner().getX(), getPosition().getY() + w_m.getView().getCorner().getY());
	graphics_manager.drawCh(p, RETICLE_CHAR, df::RED);
}