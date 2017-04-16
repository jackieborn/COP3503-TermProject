#ifndef TERMPROJ_H_INCLUDED
#define TERMPROJ_H_INCLUDED

#include <iostream>
#include <array>

using namespace std;

class Gameboard
{
private:

    int gameboard[4][4];
    /*int **gameboard;
    const int ROWS = 4;
    const int COLS = 4;*/

public:

    Gameboard(); //constructor

    int getTileValue(int i, int j); //to get the tile value at a certain spot on gameboard
    int setTileValue(int i, int j, int value); //to spawn new tile after each turn

    void createBoard(); //makes new empty board, gens 9 rand tiles to place randomly on board
    void updateBoard(char key); //updates after player movement
    void printBoard(); //displays board
    void deleteBoard(); //deletes board after game over/quit
    int highestTile(); //parses board & returns highest tile number
    bool gameOver();//when all spaces on board full, check if Game Over

    //~Gameboard(); //destructor
};

bool canMerge(int num1, int num2); //checks if two tiles can merge



#endif // TERMPROJ_H_INCLUDED
