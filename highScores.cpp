#include "highScores.h"


HighScores::HighScores()
{
    highScoreInput.open("highscores.txt");
    highScoreOutput.open("highScores.txt");

    // Read in High Scores from file
    readInHighScores();

}

HighScores::~HighScores(){
    highScoreInput.close();
    highScoreOutput.close();
}

void HighScores::readInHighScores(){
    int index = 0;
    while(highScoreInput.good()){
        getline(highScoreInput, tempString);
        highScores[index] = tempString;
        index++;
    }
}

void HighScores::writeHighScores(){

}

string HighScores::getScore(int s){
    return highScores[s];
}

void HighScores::addHighScore(int score){

}
