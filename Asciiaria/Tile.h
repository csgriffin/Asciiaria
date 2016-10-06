#pragma once

#include "Object.h"
#include <string>

// Using std namespace.
using namespace std;

enum Terrain {
	AIR = 0,
	DIRT = 1,
};

class Tile : public df::Object {

private:
	Tile();
	Terrain tileType;

public:
	Tile(Terrain init_tileType);

	Terrain getTileType() const;

	void setTileType(Terrain new_type);

	void draw();
};
