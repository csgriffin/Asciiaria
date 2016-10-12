// System includes.
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>

// Engine includes.
#include "LogManager.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Box.h"

// Game includes.
#include "Tile.h"
#include "Hero.h"
#include "Monster.h"

// Using the std namespace.
using namespace std;

// Function prototypes.
int loadLevel();
void loadResources();
void populateWorld();

// Constants.
static const int MAP_WIDTH = 300;
static const int MAP_HEIGHT = 50;

int main(int argc, char * argv[])
{
	// Get the log manager in case anything needs to be grabbed.
	df::LogManager &log_manager = df::LogManager::getInstance();

	// Start up game manager.
	df::GameManager &game_manager = df::GameManager::getInstance();
	if (game_manager.startUp()) {
		log_manager.writeLog("Error starting game manager!");
		game_manager.shutDown();
		return 0;
	}

	// Get the world manager.
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	// Set the log manager to flush after each write.
	log_manager.setFlush(true);

	// Show the dragonfly splash screen.
	// df::splash();

	// Set the boundary of the world.
	df::Box theBox = df::Box::Box(df::Vector(), 300, 50);
	world_manager.setBoundary(theBox);

	// Load the game resources.
	loadResources();

	// Load the game's level.
	loadLevel();

	// Populate the world with our hero and the monster.
	populateWorld();

	// Actually run the game.
	game_manager.run();

	// Game closes.
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

	for (int row_counter = 0; row_counter < MAP_HEIGHT; row_counter++) {

		// String for the line.
		string line;

		// Get the line.
		getline(file, line);
		istringstream sline(line);

		for (int column_counter = 0; column_counter < MAP_WIDTH; column_counter++) {

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
				p_current_tile->setPosition(df::Vector(column_counter, row_counter));

				// Test code that write the tile type and location. Works as of 10/10/2016.
				log_manager.writeLog("This is air at (%f, %f).", p_current_tile->getPosition().getX(), p_current_tile->getPosition().getY());

				break;

				// If it's 1, it's dirt. Place the dirt!
			case 1:
				p_current_tile = new Tile(DIRT);
				p_current_tile->setPosition(df::Vector(column_counter, row_counter));

				// Test code that write the tile type and location. Works as of 10/10/2016.
				log_manager.writeLog("This is dirt at (%f, %f).", p_current_tile->getPosition().getX(), p_current_tile->getPosition().getY());

				break;

			case 2:
				p_current_tile = new Tile(VERTICAL);
				p_current_tile->setPosition(df::Vector(column_counter, row_counter));

				break;

			case 3:
				p_current_tile = new Tile(HORIZONTAL);
				p_current_tile->setPosition(df::Vector(column_counter, row_counter));

				break;
			}
		}

	}

	return 0;
}

// Load the resources the game needs.
void loadResources() {

	// Get the resource manager.
	df::ResourceManager &resource_manager = df::ResourceManager::getInstance();

	// Load the sprite for dirt.
	resource_manager.loadSprite("sprites/dot-spr.txt", "dirt");

	// Load the sprite for the hero.
	resource_manager.loadSprite("sprites/hero-spr.txt", "hero");

	// Load the sprite for the villain.
	resource_manager.loadSprite("sprites/monster-spr.txt", "monster");

	// Load the border sprites.
	resource_manager.loadSprite("sprites/hor-border-spr.txt", "hor_border");
	resource_manager.loadSprite("sprites/vert-border-spr.txt", "vert_border");

}

// Create the Hero and Monster.
void populateWorld() {

	// Make the hero. Also, save a pointer to it.
	Hero* ourNobleProtagonist = new Hero;
	df::WorldManager &w_m = df::WorldManager::getInstance();
	w_m.setViewFollowing(ourNobleProtagonist);

	// Make the monster. Also, save a pointer to it... For the heck of it.
	Monster* ourEvilVillain = new Monster(ourNobleProtagonist);
}