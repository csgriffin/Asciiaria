// System includes.
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>

// Engine includes.
#include "LogManager.h"
#include "GameManager.h"
#include "TestObject.h"
#include "ResourceManager.h"

// Game includes.
#include "game.h"
#include "Tile.h"
#include "Hero.h"

// Using the std namespace.
using namespace std;

// Function prototypes.
int loadLevel();

// Constants.
static const int MAP_WIDTH = 80;
static const int MAP_HEIGHT = 24;

// Game constructor? (Is this necessary?)
game::game() {

}

// Game destructor? (Is this necessary?)
game::~game() {

}

int main(int argc, char * argv[])
{
	df::GameManager &game_manager = df::GameManager::getInstance();
	game_manager.startUp();
	df::LogManager &log_manager = df::LogManager::getInstance();
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();

	// Make test tile.
	//Tile testTile = Tile(DIRT);
	//testTile.setPosition(df::Vector(8, 8));

	// Load the game's level.
	loadLevel();

	Hero ourNobleProtagonist = Hero::Hero();
	ourNobleProtagonist.setPosition(df::Vector(5, 5));
	resource_manager.loadSprite("sprites/saucer-spr.txt", "saucer");
	ourNobleProtagonist.setSprite(resource_manager.getSprite("saucer"));

	game_manager.run();
	return 0;
}

// Function that should read the CSV mapfile.
// Returns 0 on success and -1 on failure.
// This function borrows heavily from this source:
// http://www.cplusplus.com/forum/unices/112048/
int loadLevel() {

	// Get the log manager.
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Array to store the map file's information.
	int map_array[MAP_HEIGHT][MAP_WIDTH];

	// Get the file.
	ifstream file("map.csv");

	// Error check the file opening.
	if (!file) {
		log_manager.writeLog("\nError opening the map file.");
		return -1;
	}

	for (int column_counter = 0; column_counter < MAP_WIDTH; column_counter++) {

		// String for the line.
		string line;

		// Get the line.
		getline(file, line);
		istringstream sline(line);

		for (int row_counter = 0; row_counter < MAP_HEIGHT; row_counter++) {

			// String for the value.
			string value;

			// Get the line, stopping at the delimeter.
			getline(sline, value, ',');

			// Store the value after converting it.
			map_array[row_counter][column_counter] = atoi(value.c_str());

			// Test code. As of 10/5/16 this code functions.
			// log_manager.writeLog("Printing the value of (%d, %d), which is %d.", row_counter, column_counter, map_array[row_counter][column_counter]);
		}
	}

	// Now the array will produce the map.
	for (int column_counter = 0; column_counter < MAP_WIDTH; column_counter++) {

		for (int row_counter = 0; row_counter < MAP_HEIGHT; row_counter++) {

			// Variable for current tile.
			Tile *p_current_tile;

			switch (map_array[row_counter][column_counter]) {

				// If it's zero, it's air.
			case 0:
				p_current_tile = new Tile(AIR);
				p_current_tile->setPosition(df::Vector(row_counter, column_counter));
				log_manager.writeLog("This is air at (%f, %f).", p_current_tile->getPosition().getX(), p_current_tile->getPosition().getY());
				break;

				// If it's 1, it's dirt. Place the dirt!
			case 1:
				p_current_tile = new Tile(DIRT);
				p_current_tile->setPosition(df::Vector(row_counter, column_counter));
				log_manager.writeLog("This is dirt at (%f, %f).", p_current_tile->getPosition().getX(), p_current_tile->getPosition().getY());

				break;
			}
		}

	}

	return 0;
}
