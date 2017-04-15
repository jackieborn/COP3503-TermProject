#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <array>
#include <ctime>
#include <iomanip>

#include "termProj.h"
#include "tiles.h"


using namespace std;

int main()
{
    srand(time(nullptr));//get current time as seed number for rand()

    string menuOpt; //which menu option user chooses
    Gameboard board; //create game board obj
    char key; //which direction user moves

    int temp[4][4]; //stores game board for comparison - to find which rows/cols moved
    int movement[4] = {0};  //array to store which row/col saw movement after user plays a turn
                            //each index in array corresponds to a row/col
                            //make index =1, when that row/col had tiles that moved in it



    while(true)
        {
        cout << "Welcome to Threes:" << endl;
        cout << "The OG number tile game!!!" << endl;
        cout << "MAIN MENU: Type your selection (exactly as shown)" << endl;
        cout << "Tutorial" << endl;
        cout << "Start" << endl;
        cout << "Scores" << endl;
        cout << "Quit" << endl;
        cin >> menuOpt;

        if(menuOpt == "Tutorial")//---------------------------------------------------------------
        {
            cout << "go to tutorial" <<endl;
        }

        else if(menuOpt == "Start")//---------------------------------------------------------------
        {
            board.createBoard();

            while(true)
            {
                board.printBoard();

                //reset movement to zeros
                for(int i=0; i<4; i++)
                {
                    movement[i] = 0;
                }

                //stores current board into temp 2d array
                for(int i=0; i<3; i++)
                {
                    for(int j=0; j<3; j++)
                    {
                        temp[i][j] = board.getTileValue(i, j);
                    }
                }

                cout << "Use w/a/s/d to choose which direction you want to shift tiles" << endl;
                cout << "then hit Enter." << endl;
                cin >> key;
                board.updateBoard(key);

                //if user moved up or down
                //check which columns saw movement to decide which col new tile spawns in
                if((key == 'w') || (key == 's'))
                {
                    //compares each spot in board after user makes move, to board before movement
                    for(int j=0; j<3; j++)
                    {
                        for(int i=0; i<3; i++)
                        {
                            if(temp[i][j] != board.getTileValue(i, j))
                            {
                                movement[j] = 1;
                            }
                        }
                    }
                }

                //if user moved left or right
                //check which rows saw movement to decide which row new tile spawns in
                if((key == 'a') || (key == 'd'))
                {
                    //compares each spot in board after user makes move to board, to board before movement
                    for(int i=0; i<3; i++)
                    {
                        for(int j=0; j<3; j++)
                        {
                            if(temp[i][j] != board.getTileValue(i, j))
                            {
                                movement[i] = 1;
                            }
                        }
                    }
                }

            //generate random number to pick a index from movement array
            //which will be the row/col the new tile generates in
            while(true)
            int spawnTo = rand()%4;
            if(movement[spawnTo] == 0)
            {
                spawnTo = rand()%4;
            }



            }
        }

        else if(menuOpt == "Scores")//---------------------------------------------------------------
        {
            cout << "see scores" <<endl;

        }

        else if(menuOpt == "Quit")
        {
            cout << "Quitting";
            return 1;
        }

    }

    return 0;
}

//*****************************************************************************************************************
//*****************************************************************************************************************

//constructor
Gameboard::Gameboard()
{
    for (int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            gameboard[i][j] = 0;
        }
    }
}

//getter to return value of certain tile on gameboard
int Gameboard::getTileValue(int i, int j)
{
    return gameboard[i][j];
}

void Gameboard::createBoard()
{
    bool tilesChosen = false; //true when 9 tiles generated with at least one 1, 2, and 3
    int startTiles[9] = {0}; //hold 9 starter tiles

    while(!tilesChosen)
    {

        //fill startTiles array with 9 random numbers
        //randNumGen();????????????????????????????????????????????????????????
        for(int i=0; i<9; i++)
        {

            startTiles[i] = rand() % (3) + 1;

        }

        // to keep track if there's at least one 1, 2, 3 tile each
        bool enOne = false;
        bool enTwo = false;
        bool enThree = false;

        //check startTiles array to make sure there's at least one 1, 2, 3 tile each
        for(int i=0; i<9; i++)
        {

            if(startTiles[i] == 1)
            {
                enOne = true;
            }
            else if(startTiles[i] == 2)
            {
                enTwo = true;
            }
            else if(startTiles[i] == 3)
            {
                enThree = true;
            }
        }
        //if there's at least one tile each of 1,2,3
        if((enOne == true) && (enTwo == true) && (enThree == true))
        {
            tilesChosen = true; //found 9 starter tiles to populate board
        }
    }
    int i=0;
    while(i<9)
    {
        int row = rand() % 4;
        int col = rand() % 4;

        //check if space in board is empty
        if(gameboard[row][col] == 0)
        {
            //if empty, puts tile on board
            gameboard[row][col] = startTiles[i];
            i++;
        }
    }


}

void Gameboard::updateBoard(char key)
{
    //For an up key press, synonymous with A, the contents of the array get pushed to the top, to the index i-1
    if(key == 'w')
    {
        for(int i = 1; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                //If the index above the current index is empty, push the current index to the top
                if(gameboard[i-1][j] == 0)
                {
                    gameboard[i-1][j] = gameboard[i][j];
                    gameboard[i][j] = 0;
                }
                //If not empty, call can merge
                //If you can merge the two tiles, then merge them and move the tile upward
                //Then make the current index empty by making it 0
                else
                {
                    int num1 = gameboard[i][j];
                    int num2 = gameboard[i-1][j];

                    bool merges = canMerge(num1, num2);

                    //Check to see if the adjacent tile can merge
                    if(merges)
                    {
                        int mergedNum = num1 + num2;

                        gameboard[i-1][j] = mergedNum;
                        gameboard[i][j] = 0;
                    }

                    //If it doesn't merge, do nothing
                    else
                    {
                        //Nothing, continue with the loop
                    }
                }
            }
        }
    }

    //For a left press, synonymous with W, the contents of the array get pushed to the left, to the index j-1
    if(key == 'a')
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 1; j < 4; j++)
            {
                //If the index to the left is empty, then move the value in the current index to the left and empty the current index
                if(gameboard[i][j-1] == 0)
                {
                    gameboard[i][j-1] = gameboard[i][j];
                    gameboard[i][j] = 0;
                }
                //If its not empty, store the contents of the current index and and the index to the left for comparison
                else
                {
                    int num1 = gameboard[i][j];
                    int num2 = gameboard[i][j-1];

                    bool merges = canMerge(num1, num2);

                    //Check to see if the adjacent tile can merge
                    if(merges)
                    {
                        int mergedNum = num1 + num2;

                        gameboard[i][j-1] = mergedNum;
                        gameboard[i][j] = 0;
                    }

                    //If it doesn't merge, do nothing
                    else
                    {
                        //Nothing, continue with the loop
                    }
                }
            }
        }
    }

    //S is equivalent to a down key press, so all the contents of the game board should move down one space if possible
    if(key == 's')
    {
        for(int i = 2; i >= 0; i--)
        {
            for(int j = 0; j < 4; j++)
            {
                //If the index below the current index is empty move the contents of the current index down
                if(gameboard[i+1][j] == 0)
                {
                    gameboard[i+1][j] = gameboard[i][j];
                    gameboard[i][j] = 0;
                }
                //If its not empty, then check to see if they can merge
                else
                {
                    //Stores the contents of the current tile and the tile below
                    int num1 = gameboard[i][j];
                    int num2 = gameboard[i+1][j];

                    bool merges = canMerge(num1, num2);

                    //Check to see if the adjacent tile can merge
                    if(merges)
                    {
                        int mergedNum = num1 + num2;

                        gameboard[i+1][j] = mergedNum;
                        gameboard[i][j] = 0;
                    }

                    //If it doesn't merge, do nothing
                    else
                    {
                        //Nothing, continue with the loop
                    }
                }
            }
        }
    }

    //The letter D is equivalent to a right key press
    //The contents of the game board get pushed to the right indices, equivalent to j+1
    if(key == 'd')
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 2; j >= 0; j--)
            {
                //If the index to the right of the current index is empty,
                //push the current index's value to the right and empty the current index
                if(gameboard[i][j+1] == 0)
                {
                    gameboard[i][j+1] = gameboard[i][j];
                    gameboard[i][j] = 0;
                }
                //If the index to the right is not empty, see if they can merge with the
                else
                {
                    //Make two integer values to hold the current tile value and the adjacent tile value
                    int num1 = gameboard[i][j];
                    int num2 = gameboard[i][j+1];

                    bool merges = canMerge(num1, num2);

                    //Check to see if the adjacent tile can merge
                    if(merges)
                    {
                        int mergedNum = num1 + num2;

                        gameboard[i][j+1] = mergedNum;
                        gameboard[i][j] = 0;
                    }

                    //If it doesn't merge, do nothing
                    else
                    {
                        //Nothing, continue with the loop
                    }
                }
            }
        }
    }

    //get new tile after movement

}

void Gameboard::printBoard()
{
    for(int i=0; i<4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            cout << setw(5) << gameboard[i][j] << " ";
        }
        cout << endl;
    }
}

void Gameboard::deleteBoard()
{

}

int Gameboard::highestTile()
{

}

//void seedNumGen()
//{
//    return srand(time(nullptr));
//
//}

bool canMerge(int num1, int num2)
{
    //1 and 2 can merge with each other, so if they are 1 and 2 then they are able to merge
    if((num1 == 1 && num2 == 2) || (num1 == 2 && num2 == 1))
    {
        return true;
    }

    //If the tiles are the same number then they can merge
    else if((num1>2) && (num2>2) && num1 == num2)
    {
        return true;
    }

    //If not either of these cases, return false
    else
    {
        return false;
    }
}





//destructor (delete array so no memory leak)
/*Gameboard::~Gameboard()
{
    for (int i = 0; i < ROWS; ++i){
        delete [] gameboard[i];
    }

    delete []gameboard;
 } */


