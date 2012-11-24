#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>

#include <QFile>
#include <QTextStream>

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

    QFile otherFile;
    QTextStream stream;

    // Variables
    int fileFlag;
    int standardInts[5];
    int survivalInts[5];
    int endlessInts[5];
    string tempString;

    // Methods
    void readInHighScores();
    void writeHighScores();
    char* getScore(char*, int);
    void addHighScore(char*, int);
};

#endif // HIGHSCORES_H
