#ifndef TILES_H_INCLUDED
#define TILES_H_INCLUDED

#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <random>
#include <ctime>

#include "termProj.h"

using namespace std;

class Tiles
{
public:

	//Data members for the class.
	//The vector 'pool' holds tiles for the game
	//The integer 'maxTile' holds the highest tile on the board
	std::vector<int> pool;
	int maxTile;

	//This function initializes a small pool of tiles
	//This specific pool of tiles is only used once, when a game is started
	void initialPool();

	//This function checks to see if a pool of tiles is empty
	bool isEmpty();

	//This function refreshes the pool of tiles
	void refreshTiles(Gameboard board);

	//This function returns one tile
	int getTile(Gameboard board);

	//This function sets the max tile value.
	void setMaxTile(int max);

	//Prints the max tile value (mostly used for debugging)
	void printMaxTile();

	//Prints the pool of tiles (mostly used for debugging)
	void printPool();
};

#endif // TILES_H_INCLUDED
