/**@author Devin Rusnak
 * @copyright Blockstar 2012
 * @class HighScores highScores.h "highScores.h"
 * @brief This is a class used to read & write high scores from the game to a file for record.
 * @bug High Scores do not transfer to mainwindow_UI correctly.
 *
 * The high scores from the game are stored in a .txt file that is read and wrote to.
 * The top ten scores from each mode is read & wrote to in a specific order to maintain simplicity
 * in the file format.
 * The high scores from each game mode are held in seperate arrays of integers.
 * These scores are used by the score# labels in mainwindow_UI to display the scores to the user.
*/
#include "highScores.h"

/**
 * @brief HighScores::HighScores
 *
 */
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

/**
 * @brief HighScores::~HighScores
 */
HighScores::~HighScores(){
    delete theFile;
    delete inputStream;
}

/**
 * @brief HighScores::readInHighScores
 */
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

/**
 * @brief HighScores::writeHighScores
 */
void HighScores::writeHighScores(){

}

/**
 * @brief HighScores::getScore
 * @param s Index of the score wanted.
 * @return Returns score at the index requested.
 */
int HighScores::getScore(int s){
    if(highScoresArray[s] == NULL)
        return 0;

    else
        return highScoresArray[s];
}

/**
 * @brief HighScores::addHighScore
 * @param score Score that is sorted into the proper array.
 */
void HighScores::addHighScore(int score){

}
