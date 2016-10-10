#include "Tile.h"
#include "LogManager.h"
#include "GraphicsManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include <iostream>
#include "EventMouse.h"

Tile::Tile(Terrain init_tileType) {
	df::Object();

	// Set the initial type of the tile.
	tileType = init_tileType;

	// Get the resource manager.
	df::ResourceManager &rm = df::ResourceManager::getInstance();

	switch (tileType)
	{
	case DIRT:

		// Set solidness to HARD.
		setSolidness(df::HARD);

		// Get dirt's sprite.
		setSprite(rm.getSprite("dirt"));

		break;

	case AIR:
		// Nothing.
	default:

		// Set solidness to SPECTRAL.

		setSolidness(df::SPECTRAL);
		break;
	}

	// Register interest in the mouse events.
	registerInterest(df::MOUSE_EVENT);

}

Terrain Tile::getTileType() const {
	return tileType;
}

void Tile::setTileType(Terrain new_type) {
	tileType = new_type;
}

int Tile::eventHandler(const df::Event * p_e) {

	if (p_e->getType() == df::MOUSE_EVENT) {

		const df::EventMouse *p_mouse_event = dynamic_cast <const df::EventMouse *> (p_e);

		if ((p_mouse_event->getMouseAction() == df::CLICKED) && (p_mouse_event->getMouseButton() == df::LEFT)) {

			if (tileType == DIRT) {

				// Get world manager.
				df::WorldManager &world_manager = df::WorldManager::getInstance();
				df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();
				df::LogManager &log_manager = df::LogManager::getInstance();

				// Gets the charWidth and charHeight.
				float charWidth = (float)graphics_manager.getHorizontalPixels() / (float)graphics_manager.getHorizontal();
				float charHeight = (float)graphics_manager.getVerticalPixels() / (float)graphics_manager.getVertical();

				// Apply spacesToPixels.
				df::Vector mouse_tile(p_mouse_event->getMousePosition().getX() / charWidth, p_mouse_event->getMousePosition().getY() / charHeight);

				// Check if this is the selected tile.
				if (((int)getPosition().getX() == (int)mouse_tile.getX()) && ((int)getPosition().getY() == (int)mouse_tile.getY())) world_manager.markForDelete(this);

				// Print out what was used.
				log_manager.writeLog("Tile Position: %f, %f and Mouse Position: %f, %f", (int)getPosition().getX(), (int)getPosition().getY(),
					(int)mouse_tile.getX(), (int)mouse_tile.getY());

			}
			else {
				// nothing...
			}
		}

		return 1;
	}

	return 0;
}

/*void Tile::draw() {

	// Get the graphics manager.
	df::GraphicsManager &graphics_manager = df::GraphicsManager::getInstance();

	// Get log manager.
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Write log.
	//cout << "At the draw method with a " + tileType << endl;

	switch (tileType)
	{
	case DIRT:

		// Place dirt block.
		graphics_manager.drawCh(getPosition(), '=', df::WHITE);

		break;

	case AIR:
		// Nothing.
	default:
		break;
	}
}*/
