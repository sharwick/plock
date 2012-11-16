#include "highScores.h"


HighScores::HighScores()
{
    theFile = new QFile("highscores.txt");
    if(!theFile->open(QIODevice::Append)){
        cout << "File Not Found" << endl;
    }
    else{
        inputStream = new QTextStream(theFile);
    }
}

HighScores::~HighScores(){

}

void HighScores::readInHighScores(){

    int index = 0;
    bool fail = false;

    while(!inputStream->atEnd()){
        tempString = inputStream->readLine();
        highScoresArray[index] = tempString.toInt(&fail, 10);
        if(fail){
            cout << "Conversion Failed at index " << index << endl;
            return;
        }
    }
}

void HighScores::writeHighScores(){

}

int HighScores::getScore(int s){
    if(highScoresArray[s] == NULL)
        return 0;

    else
        return highScoresArray[s];
}

void HighScores::addHighScore(int score){

}
