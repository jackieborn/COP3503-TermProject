#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <regex>
using namespace std;

class Statistics{
 private:
     string playerName;
     string score;
     string highestTile;


public:
    Statistics();
    bool fileExists(const string fileName);
    double Mean(string playerName);
    int NumberOfPlayerGames(string playerName);
    double StandardDeviation();
    void UpdatePlayerHighestTile(string playerName, int tileScore);
    void UpdatePlayerScore(string playerName, int score);
    double Percentile(int score, double standardDev, double mean);
    double CheckStats(int playerName);
    double UpdateStats(int playerName);
    int gamesPlayed(int playerName);

};
Statistics::Statistics(){

}

void Statistics::UpdatePlayerScore(string playerName, int score){

 string fileName = playerName + ".txt";
 char buffer[256];
 ofstream outfile;
 outfile.open(fileName, ios::app | ios_base::out | ios_base::in);
 if(outfile.is_open()){
    outfile << score << endl;
 }
 else{
    outfile << score << endl;

}
outfile.close();

}

int Statistics::NumberOfPlayerGames(string playerName){
    ifstream infile(playerName + ".txt");
    double numberOfGames = 0;
    string temp;
    while(infile >> temp){
        numberOfGames++;
     }
     return numberOfGames;
}

void Statistics::UpdatePlayerHighestTile(string playerName, int tileScore){
    int currentTileScore;
    stringstream ss;
    ss << tileScore;
    string tileScoreToStr = ss.str();
    string fileName = playerName + "_" + "TileScore" + ".txt";
    //File to read from
    ifstream infile(fileName);
    if(infile.is_open()){
        infile >> currentTileScore;
        infile.close();
        if(currentTileScore < tileScore){
            ofstream outfile;
            outfile.open(fileName, ios::trunc);
            outfile << tileScore << endl;
            outfile.close();
        }

    }
    else{
        ofstream outfile;
        outfile.open(fileName);
        outfile << tileScore << endl;
        outfile.close();
    }

    int tempScore;

}



bool fileExists(const string fileName)
{
    ifstream infile(fileName);
    return infile.good();
}

double Statistics::Mean(string playerName){
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
    while(infile >> temp){
        //takes each score in string, coverts score to int, and stores int
        cout << "Score: " << temp << endl;
        sum += atoi(temp.c_str());
        mean = sum/numOfGames;
     }
     return mean;
}




