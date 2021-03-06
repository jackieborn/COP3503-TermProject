#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <array>
#include <ctime>
#include <iomanip>

#include "tiles.h"
#include "termProj.h"
#include "stats.h"



using namespace std;

int main()
{
    srand(time(nullptr));//get current time as seed number for rand()

    string menuOpt; //which menu option user chooses
    Gameboard board; //create game board obj
    char key; //which direction user moves
    bool gameOver = false; //true if no more moves left for player to make

    int temp[4][4]; //stores game board for comparison - to find which rows/cols moved
    int movement[4] = {0};  //array to store which row/col saw movement after user plays a turn
                            //each index in array corresponds to a row/col
                            //make index =1, when that row/col had tiles that moved in it

    Tiles tileSet;//create new tileSet object
    bool firstTurn;//if player's 1st turn, must call initialPool since 9/12 tiles already on board
    int newTile; //new tile that will spawn onto board every turn

    Statistics stats;//create object
    string player; //holds player name

//--------------------------------------------------------------------------------------------------
    //asks player to enter name
    cout << "Please enter player name: " << endl;
    cin >> player;
    cout << endl;

    //checks to see if name is already taken in the stats file
    bool nameAccepted = stats.UpdatePlayerNameList(player);
    while(nameAccepted == false)
    {
        cout << "Name already taken. Please enter another: " << endl;
        cin >> player;
        cout << endl;
        nameAccepted = stats.UpdatePlayerNameList(player);
    }




    while(true)
        {
        //reset gameOver to false
        gameOver = false;

        cout << endl;
        cout << "Welcome to Threes!:" << endl;
        cout << "The OG number tile game!!!" << endl;
        cout << "MAIN MENU: Type your selection (exactly as shown)" << endl;
        cout << "Tutorial" << endl;
        cout << "Start" << endl;
        cout << "Scores" << endl;
        cout << "Quit" << endl;
        cin >> menuOpt;

        //prints out information about the game & how to play
        if(menuOpt == "Tutorial")//********************************************************************************
        {
            cout << "Welcome to the Threes! Tutorial." << endl;
            cout << "--------------------------------" << endl;
            cout << endl;
            cout << "Rules for playing Threes!" << endl;
            cout << endl;
            cout << "Threes! is a tile merging game, where" << endl;
            cout << "you are tasked with merging as many tiles" << endl;
            cout << "as you can before your board becomes full," << endl;
            cout << "and you are unable to make any more moves." << endl;
            cout << endl;
            cout << "During each move, you will choose to move either" << endl;
            cout << "up, down, left, or right. By doing so, each tile" << endl;
            cout << "on the board will attempt to move in that direction!" << endl;
            cout << "If a tile can move 'into' another tile of the same value," << endl;
            cout << "they will 'merge', forming a larger tile, which is worth more" << endl;
            cout << "points! Tiles that cannot merge or do not have a free space to" << endl;
            cout << "move in to will stay where they are (blank spaces are represented by underscores)." << endl;
            cout << endl;
            cout << "--------------------------------" << endl;
            cout << endl;
            cout << "Merging tiles" << endl;
            cout << endl;
            cout << "When two tiles of the same value merge together, they form a higher" << endl;
            cout << "tile, equal to the sum of the two tiles that just merged. For example," << endl;
            cout << "two tiles of value '3' merge to form one tile of value '6'. Similarly," << endl;
            cout << "two tiles of value '12' merge to form a tile of value '24'. The" << endl;
            cout << "exception to this are '1's and '2's. Tiles of the value '1' MUST merge with" << endl;
            cout << "a tile of value '2' to form a single tile of value '3'." << endl;
            cout << endl;
            cout << "--------------------------------" << endl;
            cout << endl;
            cout << "New tiles" << endl;
            cout << endl;
            cout << "Each time you make a move, a new tile will appear on the board." << endl;
            cout << "The tile will appear on the side you moved away from. For example," << endl;
            cout << "moving left will cause a tile to appear from the right and moving down" << endl;
            cout << "will cause a tile to appear from the top. The tile will spawn in a row" << endl;
            cout << "or column that moved during your previous move." << endl;
            cout << endl;
            cout << "--------------------------------" << endl;
            cout << endl;
            cout << "Game over and scores" << endl;
            cout << endl;
            cout << "The game will end if you fill up your board with 16 tiles, and you" << endl;
            cout << "are left with no more valid moves. At that point, a score will be" << endl;
            cout << "calculated based on the tiles currently on your board. A scoring table" << endl;
            cout << "can be found below:" << endl;
            cout << endl;
            cout << "Tiles          Score" << endl;
            cout << endl;
            cout << "1              0" << endl;
            cout << "2              0" << endl;
            cout << "3              3" << endl;
            cout << "6              9" << endl;
            cout << "12             27" << endl;
            cout << "24             81" << endl;
            cout << "48             243" << endl;
            cout << "96             729" << endl;
            cout << "192            2187" << endl;
            cout << "384            6561" << endl;
            cout << "768            19683" << endl;
            cout << "1536           59049" << endl;
            cout << "3072           177147" << endl;
            cout << "6144           531441" << endl;
            cout << endl;
            cout << "Did you get all that?" << endl;
            cout << endl;
            cout << "Happy Threes!" << endl;
            cout << endl;
        }

        else if(menuOpt == "Start")//******************************************************************************
        {
            board.createBoard();
            firstTurn = true;

            while(gameOver == false)
            {
                board.printBoard();

                //reset movement to zeros
                for(int i=0; i<4; i++)
                {
                    movement[i] = 0;
                }

                //stores current board into temp 2d array
                for(int i=0; i<4; i++)
                {
                    for(int j=0; j<4; j++)
                    {
                        temp[i][j] = board.getTileValue(i, j);
                    }
                }

                cout << "Use w/a/s/d to choose which direction you want to shift tiles" << endl;
                cout << "then hit Enter." << endl;

                //get new tile to spawn onto board
                newTile = tileSet.getTile(board);
                cout << "NEXT TILE: " << newTile << endl;

                cin >> key;
                board.updateBoard(key);

                //if user moved up or down
                //check which columns saw movement to decide which col new tile spawns in
                if((key == 'w') || (key == 's'))
                {
                    //compares each spot in board after user makes move, to board before movement
                    for(int j=0; j<4; j++)
                    {
                        for(int i=0; i<4; i++)
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
                    for(int i=0; i<4; i++)
                    {
                        for(int j=0; j<4; j++)
                        {
                            if(temp[i][j] != board.getTileValue(i, j))
                            {
                                movement[i] = 1;
                            }
                        }
                    }
                }

                //checks to see if the user made a valid movement
                //check to see if any tile movement actually happened
                bool validMove = false; //when board before & after player move is the same
                for(int i=0; i<4; i++)
                {
                    for(int j=0; j<4; j++)
                    {
                        //so long as one tile value is different after the move, the player move is valid
                        if(board.getTileValue(i, j) != temp[i][j])
                        {
                            validMove = true;
                        }
                    }
                }

                if(validMove)
                {
                    //generate random number to pick a index from movement array
                    //which will be the row/col the new tile generates in
                    int spawnTo = rand()%4;
                    //while the array index is 0 (row/col that didn't see movement), choose another random number
                    while(movement[spawnTo] == 0)
                    {
                        spawnTo = rand()%4;
                    }

                    //if player's first turn, must call initialPool (since 9 of 12 tiles already on board)
                    if(firstTurn)
                    {
                        tileSet.initialPool();
                        firstTurn = false;
                    }

//~~

                    //place new tile on board
                    if(key == 'w')
                    {
                        //if player moved up, tile spawns in bottom row
                        board.setTileValue(3, spawnTo, newTile);
                    }
                    else if(key == 'a')
                    {
                        //if player moved left, tile spawns in rightmost column
                        board.setTileValue(spawnTo, 3, newTile);
                    }
                    else if(key == 's')
                    {
                        //if player moved down, tile spawns in top row
                        board.setTileValue(0, spawnTo, newTile);
                    }
                    else if(key == 'd')
                    {
                        //if player moved right, tile spawns in leftmost column
                        board.setTileValue(spawnTo, 0, newTile);
                    }
                }

                else if (!validMove)
                {
                    cout << "BOOOO! Invalid move." << endl << endl;
                }

                //check if the player has any moves left to make
                //if no more viable moves, then the game is over
                gameOver = board.gameOver();

            }//start game - while loop end

            //print board that is Game Over
            board.printBoard();

            cout << "GAME OVER!" << endl << endl;

            //updates player's highest tile achieved in the game
            stats.UpdatePlayerHighestTile(player, board.highestTile());

            //updates player's highest game score
            stats.UpdatePlayerScore(player, board.returnScore());

            //updates player's total lifetime score
            stats.UpdateScoreList(board.returnScore());

            board.~Gameboard();

        }

        else if(menuOpt == "Scores")//*****************************************************************************
        {
            if(stats.NumberOfPlayerGames(player) == 0)
            {
                cout << endl << "You haven't played yet!" << endl << endl;
            }
            else
            {
                cout << endl << "Mean score: " << stats.Mean(player) << endl;
                cout << "Number of games played: " << stats.NumberOfPlayerGames(player) << endl;
                cout << "See text file for player history." << endl << endl;
            }


        }

        else if(menuOpt == "Quit")//*******************************************************************************
        {
            cout << endl << "Quitting";
            return 1;
        }

    }

    return 0;
}

//*****************************************************************************************************************
//~ ~ ~ ~ Below are functions for Game objects ~ ~ ~ ~ ~ ~
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

//setter to place new tiles onto board
void Gameboard::setTileValue(int i, int j, int value)
{
    gameboard[i][j] = value;
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
    int high = 0;
    int temp = 0;

    for(int i; i<4; i++)
    {
        for(int j; j<4; j++)
        {
            temp = gameboard[i][j];
            if(temp > high)
            {
                high = temp;
            }
        }
    }
    return high;

}

bool Gameboard::gameOver()
{
    //Checks to see if the game is over
    //Game is over if the player cannot make anymore moves, if the board is full

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(gameboard[i][j] == 0)
            {
                return false;
            }
        }
    }

    if(canMerge(gameboard[0][0], gameboard[0][1]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[0][1], gameboard[0][2]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[0][2], gameboard[0][3]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[1][0], gameboard[1][1]) == true)
    {
       return false;
    }
    else if(canMerge(gameboard[1][1], gameboard[1][2]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[1][2], gameboard[1][3]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[2][0], gameboard[2][1]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[2][1], gameboard[2][2]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[2][2], gameboard[2][3]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[3][0], gameboard[3][1]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[3][1], gameboard[3][2]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[3][2], gameboard[3][3]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[0][0], gameboard[1][0]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[1][0], gameboard[2][0]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[2][0], gameboard[3][0]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[0][1], gameboard[1][1]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[1][1], gameboard[2][1]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[2][1], gameboard[3][1]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[0][2], gameboard[1][2]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[1][2], gameboard[2][2]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[2][2], gameboard[3][2]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[0][3], gameboard[1][3]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[1][3], gameboard[2][3]) == true)
    {
        return false;
    }
    else if(canMerge(gameboard[2][3], gameboard[3][3]) == true)
    {
        return false;
    }
    else
    {
        return true;
    }
    //Parse through the gameboard sideways
    //Check to see if the tile to the right of the current can merge with the current tile
    //Also checks to see if tile to the right is empty (is equal to 0)
    //If it can or a space is empty, more moves can be made and game is not over
//    for(int i = 0; i < 4; i++)
//    {
//        for(int j = 0; j < 3; j++)
//        {
//            int curr = gameboard[i][j];
//            int next = gameboard[i][j+1];
//
//            notOver = canMerge(curr, next);
//
//            if(notOver==true || next == 0)
//            {
//                return notOver;
//            }
//        }
//    }
//
//    //Parse through the gameboard going down
//    //Check to see if the tile below the current can merge with the current tile
//    //Also checks to see if the tile below is empty
//    //If it can merge or a space is empty, more moves can be made and game is not over
//    for(int j = 0; j < 4; j++)
//    {
//        for(int i = 0; i < 3; i++)
//        {
//            int curr = gameboard[i][j];
//            int below = gameboard[i+1][j];
//
//            notOver = canMerge(curr, below);
//
//            if(notOver || below == 0)
//            {
//                return notOver;
//            }
//        }
//    }
//    return notOver;
}

//void seedNumGen()
//{
//    return srand(time(nullptr));
//
//}

int Gameboard::returnScore ()
{
    int sum;
    int currentTile;

    for (int i = 0; i < 4; i ++)
    {
        for (int j = 0; j < 4; j++)
        {
            currentTile = gameboard[i][j];

            if (currentTile == 1 || currentTile == 2)
            {
                continue;
            }
            currentTile /= 3;
            currentTile = log2(currentTile);
            currentTile++;
            sum += pow(3,currentTile);
        }
    }
    return sum;
}

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





//destructor (delete game board object)
Gameboard::~Gameboard()
{
    delete gameboard;
 }



