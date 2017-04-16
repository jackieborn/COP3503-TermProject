#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <random>
#include <ctime>

#include "tiles.h"
#include "termProj.h"

//Used for testing
/*int main()
{
	//The line below should be implemented ONCE at the top of our main function
	srand(time(0));

	Tiles tileSet;
	tileSet.initialPool();
	tileSet.setMaxTile(768);

	return 0;
}*/

//called once at the start of a new game to complete that pool set of 12
void Tiles::initialPool()
{
    pool.clear();
    pool.push_back(1);
    pool.push_back(2);
    pool.push_back(3);
    random_shuffle(begin(pool), end(pool));
}

//Check if the pool of tiles is empty. If it is empty, return true; if not, return false.
bool Tiles::isEmpty()
{
    bool empty = false;
    if (pool.empty())
    {
        empty = true;
    }
    return empty;
}

void Tiles::refreshTiles(Gameboard board)
{
    //Clears pool, and fills pool with 4 1's, 4 2's, and 4 3's
    pool.clear();
    pool.push_back(1);
    pool.push_back(1);
    pool.push_back(1);
    pool.push_back(1);
    pool.push_back(2);
    pool.push_back(2);
    pool.push_back(2);
    pool.push_back(2);
    pool.push_back(3);
    pool.push_back(3);
    pool.push_back(3);
    pool.push_back(3);

    //If the max tile is above 24 (i.e., it's 48 or above), there's a chance to spawn a bonus tile
    int maxTile = board.highestTile();
    if (maxTile > 24)
    {
        int j;
        int state;
        int coinFlip;
        j = maxTile;
        j /= 3;
        j = log2(j);
        j = j-4;

        state = rand()%(j+1);
        coinFlip = rand()%2;

        //Fifty-fifty chance to include a bonus tile
        if (coinFlip == 1)
        {
            state ++;
            state = pow(2,state);
            state *= 3;
            pool.push_back(state);
        }
    }

    //Shuffles the pool of tiles
    random_shuffle(begin(pool), end(pool));
}

//Get a tile
int Tiles::getTile(Gameboard board)
{
    //If the pool is empty, the pool is refreshed before a tile is returned
    bool empty = isEmpty();
    if(empty)
    {
        refreshTiles(board);
    }

    //Grabs tile from index zero, erases value at that index, returns tile
    int tile = pool[0];
    pool.erase(pool.begin());
    return tile;
}

//Set maxTile equal to the current max value of the tile
void Tiles::setMaxTile (int max)
{
    maxTile = max;
}

//Print out the value of the max tile
void Tiles::printMaxTile()
{
    cout << maxTile << endl;
}

void Tiles::printPool()
{
    for (int i = 0; i < pool.size(); i++)
    {
        cout << pool[i] << " ";
    }
    cout << endl;
}
