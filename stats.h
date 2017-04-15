#ifndef STATS_H_INCLUDED
#define STATS_H_INCLUDED

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <regex>

include "termProj.h"

using namespace std;

class Statistics{
 private:
     string playerName;
     string score;
     string highestTile;


public:
    //constructor
    Statistics();

    //checks if file exists. Returns false if file doesnt exist.
    bool fileExists(const string fileName);

    //sums player's scores and divides by player's total games to get player's average. Doesn't round.
    double Mean(string playerName);

    //counts the number of games a player has played. Used in Mean function
    int NumberOfPlayerGames(string playerName);

    //doesn't work yet
    double StandardDeviation();

    //update's player's largest tile to a text file named playerName_tileScore.txt
    void UpdatePlayerHighestTile(string playerName, int tileScore);

    //Add's a player's score to the list of player's scores stored in playerName.txt
    void UpdatePlayerScore(string playerName, int score);

    //not functional yet
    double Percentile(int score, double standardDev, double mean);

    //not functional yet
    double CheckStats(int playerName);

     //not functional yet
    double UpdateStats(int playerName);

    //not functional yet
    int gamesPlayed(int playerName);

};
Statistics::Statistics(){

}


void Statistics::UpdatePlayerScore(string playerName, int score)
{

 //fileName is the name of the file that will be opened
 string fileName = playerName + ".txt";

 //creates buffer to prevent overflow
 char buffer[256];

 //opens ofstream for writing
 ofstream outfile;

 //opens file in ios::app and ios_base mode which will append new lines to the bottom and create a new file if
 //the specified file to be opened wasn't created yet
 outfile.open(fileName, ios::app | ios_base::out | ios_base::in);

 //open file
 if(outfile.is_open())
 {
    //read file by word
    outfile << score << endl;
 }
 else
 {
    outfile << score << endl;

}
//close file.
outfile.close();

}

int Statistics::NumberOfPlayerGames(string playerName)
{
    //opens file in read mode
    ifstream infile(playerName + ".txt");

    //variable that keeps count of how many scores there are in log, ie how many games played
    double numberOfGames = 0;

    //temp string reads in string scores from text file
    string temp;

    //reads from text file one word at a time, ie reads one score at a time
    while(infile >> temp)
    {
        numberOfGames++;
     }

     return numberOfGames;
}

//if player reaches a new highest tile, the new highest tile is stored
void Statistics::UpdatePlayerHighestTile(string playerName, int tileScore){
    //holds the tile from the most recent game
    int currentTileScore;

    //opens string stream
    stringstream ss;

    //inputs tileScore into string stream
    ss << tileScore;

    //storoes tileScore as string
    string tileScoreToStr = ss.str();

    //concatenates file name
    string fileName = playerName + "_" + "TileScore" + ".txt";

    //open file in read mode
    ifstream infile(fileName);

    //if opening was succesful
    if(infile.is_open())
    {
        //read score into currentTileScore
        infile >> currentTileScore;

        //closes file
        infile.close();

        //if new tile score is greater than old tile score
        if(currentTileScore < tileScore)
        {
            //open write stream
            ofstream outfile;

            //opens file in truncate mode, which deletes all past contents in the opened file
            outfile.open(fileName, ios::trunc);

            //stores new score
            outfile << tileScore << endl;

            //closes file
            outfile.close();
        }

    }
    else
    {
        //file was not created. create a new file to store new player's tile information
        //open stream in write mode
        ofstream outfile;

        //open file
        outfile.open(fileName);

        //write to file
        outfile << tileScore << endl;

        //close file
        outfile.close();
    }

    int tempScore;

}



bool fileExists(const string fileName)
{
    //open file in read mode
    ifstream infile(fileName);

    //return true if file exists
    return infile.good();
}

double Statistics::Mean(string playerName)
{
    //opens file
    ifstream infile(playerName + ".txt");

    //stores sum of scores
    double sum = 0;
    double mean;

    //stores readline from file
    string temp;

    //calls NumberofPlayerGames functions to see how many games played by player
    int numOfGames = NumberOfPlayerGames(playerName);

    //reads in each
    while(infile >> temp)
    {
        //takes each score in string, coverts score to int using atoi function, and stores int
        cout << "Score: " << temp << endl;

        sum += atoi(temp.c_str());

        //divide sum by total games
        mean = sum/numOfGames;
     }

     return mean;
}


#endif // STATS_H_INCLUDED
