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

	// Load the game's level.
	loadLevel();

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
	int map_array[MAP_WIDTH][MAP_HEIGHT];

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
	for (int row_counter = 0; row_counter < MAP_HEIGHT; row_counter++) {

		for (int column_counter = 0; column_counter < MAP_WIDTH; column_counter++) {

			switch (map_array[row_counter][column_counter]) {

				// If it's zero, it's air. Do nothing!
			case 0:
				break;

				// If it's 1, it's dirt. Place the dirt!
			case 1:
				// TODO: Place dirt.
				break;
			}
		}

	}

	return 0;
}
