#include "Tile.h"
#include "LogManager.h"
#include "GraphicsManager.h"
#include "WorldManager.h"
#include <iostream>

Tile::Tile(Terrain init_tileType) {
	df::Object();

	tileType = init_tileType;

	switch (tileType)
	{
	case DIRT:

		// Set solidness to HARD.
		setSolidness(df::HARD);

		break;

	case AIR:
		// Nothing.
	default:
		// Set solidness to SPECTRAL.
		setSolidness(df::SPECTRAL);
		break;
	}

}

Terrain Tile::getTileType() const {
	return tileType;
}

void Tile::setTileType(Terrain new_type) {
	tileType = new_type;
}

void Tile::draw() {

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
}
