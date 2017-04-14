#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <random>
#include <ctime>
#include "tiles.h"

//Used for testing 
int main()
{
	//The line below should be implemented ONCE at the top of our main function 
	srand(time(0));
	
	Tiles tileSet;
	tileSet.initialPool();
	tileSet.setMaxTile(768);
	
	for (int i = 0; i < 52; i++)
	{
		cout << tileSet.getTile() << " ";
	}
		
	return 0;
}	
	
	 
	