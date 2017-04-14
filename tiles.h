#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <random>
#include <ctime>

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
	void initialPool()
	{
		pool.clear();
		pool.push_back(1);
		pool.push_back(2);
		pool.push_back(3);
		random_shuffle(begin(pool), end(pool));
	}
	
	//This function checks to see if a pool of tiles is empty
	bool isEmpty()
	{
		bool empty = false;
		if (pool.empty())
		{
			empty = true;
		}
		return empty;
	}
	
	//This function refreshes the pool of tiles 
	void refreshTiles()
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
			
	//This function returns one tile		
	int getTile()
	{
		//If the pool is empty, the pool is refreshed before a tile is returned 
		bool empty = isEmpty();
		if(empty)
		{
			refreshTiles();
		}
		
		//Grabs tile from index zero, erases value at that index, returns tile
		int tile = pool[0];
		pool.erase(pool.begin());
		return tile;
	}
	
	//This function sets the max tile value.
	void setMaxTile (int max)
	{
		maxTile = max;
	}	
	
	//Prints the max tile value (mostly used for debugging)
	void printMaxTile()
	{
		cout << maxTile << endl;
	}
	
	//Prints the pool of tiles (mostly used for debugging)
	void printPool()
	{
		for (int i = 0; i < pool.size(); i++)
		{
			cout << pool[i] << " ";
		}
		cout << endl;
	}				
};