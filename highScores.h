#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <QFile>
#include <QTextStream>
#include <QLabel>

using namespace std;

class HighScores
{

public:
    // Constructors
    HighScores();
    ~HighScores();

    // Objects
    QFile *theFile;
    QLabel *standardScores[5], *survivalScores[5], *endlessScores[5];

    // Variables
    int standardInts[5];
    int survivalInts[5];
    int survivalLevels[5];
    int endlessInts[5];


    // Methods
    void readInHighScores();
    void writeHighScores();
    void loadHighScores();
    int addHighScore(QString, int, int);
    QLabel* getLabel(QString, int);

};

#endif // HIGHSCORES_H
