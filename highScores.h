#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <QString>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class HighScores
{

public:
    HighScores();
    ~HighScores();

    ifstream highScoreInput;
    ofstream highScoreOutput;
    string tempString;

    // Variables
    string highScores[10];

    // Methods
    void readInHighScores();
    void writeHighScores();
    string getScore(int);
    void addHighScore(int);
};

#endif // HIGHSCORES_H
