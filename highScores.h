#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <iostream>
#include <fstream>
#include <string>
#include <exception>

using namespace std;

class HighScores
{

public:
    // Constructors
    HighScores();
    ~HighScores();

    // Objects
    ifstream theFile;
    string standardHighScores[5];
    string survivalHighScores[5];
    string endlessHighScores[5];

    // Variables
    int fileFlag;
    string tempString;

    // Methods
    void readInHighScores();
    void writeHighScores();
    char* getScore(char*, int);
    void addHighScore(int);
};

#endif // HIGHSCORES_H
