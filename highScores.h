#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <iostream>

using namespace std;

class HighScores
{

public:
    HighScores();
    ~HighScores();

    QFile *theFile;
    QTextStream *inputStream;
    QString tempString;

    // Variables
    int highScoresArray[10];

    // Methods
    void readInHighScores();
    void writeHighScores();
    int getScore(int);
    void addHighScore(int);
};

#endif // HIGHSCORES_H
