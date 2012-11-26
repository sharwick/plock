/**@author Devin Rusnak
 * @copyright Blockstar 2012
 * @class HighScores highScores.h "highScores.h"
 * @brief This is a class used to read & write high scores from the game to a file for record.
 * @bug High Scores are not read or written to file correctly.
 *
 * The high scores from the game are stored in a .txt file that is read and wrote to.
 * The top five scores from each mode is read & wrote to in a specific order to maintain simplicity
 * in the file format.
 * The high scores from each game mode are held in seperate arrays of integers.
 * These scores are used by the score# labels in mainwindow_UI to display the scores to the user.
*/

#include "highScores.h"

/**
 * @brief HighScores::HighScores
 *
 * The default and only constructor. It initalizes the QLabels the scores are displayed with.
 */
HighScores::HighScores()
{
    // Create Labels
    for(int index = 0; index < 5; index++){
        standardScores[index] = new QLabel("");
        survivalScores[index] = new QLabel("");
        endlessScores[index] = new QLabel("");
    }
    readInHighScores();
}

/**
 * @brief HighScores::~HighScores
 *
 * The Destructor
 */
HighScores::~HighScores(){
    for(int index = 0; index < 5; index++){
        delete standardScores[index];
        delete survivalScores[index];
        delete endlessScores[index];
    }
}

/**
 * @brief HighScores::readInHighScores
 *
 * Opens the file highscores.txt and reads in its contents. It is formated as a
 * fifteen line text file where each line is a numerical score. The first five lines are the
 * standard game mode scores. The next five lines are the survival mode high scores, and the
 * last five are the endless mode high scores. If the file doesn't have enough lines to fill
 * out the high scores then the rest of the scores are set to zero.
 */
void HighScores::readInHighScores(){

    theFile = new QFile("highscores.txt");

    // File failed to open
    if(!theFile->open(QIODevice::ReadWrite)){
        for(int i=0; i < 5; i++){
            standardScores[i]->setText("Fail");
            standardInts[i] = -1;
            survivalScores[i]->setText("Fail");
            survivalInts[i] = -1;
            endlessScores[i]->setText("Fail");
            endlessInts[i] = -1;
        }
    }
    else{   // File is open, read in scores
        char* tempChar = new char();
        int index = 0;

        while(theFile->canReadLine()){
            theFile->readLine(tempChar, 100);

            if(index < 5)
                standardInts[index] = atoi(tempChar);

            else if(index < 10 && index >= 5)
                survivalInts[index-5] = atoi(tempChar);

            else if(index >= 10)
                endlessInts[index-10] = atoi(tempChar);

            index++;
        }

        while(index < 15){
            if(index < 5){
                standardInts[index] = 0;
            }
            else if(index < 10 && index >= 5){
                survivalInts[index-5] = 0;
            }
            else if(index >= 10){
                endlessInts[index-10] = 0;
            }
            index++;
        }
    }
    loadHighScores();
    theFile->close();    // Close File
}

/**
 * @brief HighScores::writeHighScores
 *
 * Takes the string arrays of high scores and writes them in the correct
 * order to the file <highscores.txt>. The order of scores is: the five Standard
 * Mode scores, The five Survival Mode scores, and the five Endless Mode scores.
 */
void HighScores::writeHighScores(){
    theFile->open(QIODevice::ReadWrite);

    for(int index = 0; index < 15; index++){
        if(index < 5){
            theFile->write((char*)standardScores[index]);
            theFile->write("\n");
        }
        else if(index < 10 && index >= 5){
            theFile->write((char*)survivalScores[index-5]);
            theFile->write("\n");
        }
        else{
            theFile->write((char*)endlessScores[index-10]);
            theFile->write("\n");
        }
    }

    theFile->close();
}

/**
 * @brief HighScores::addHighScore
 * @param score The score that is sorted into the proper array.
 *
 * Given the string and the int sent to the method, it will sort
 * the score into the arrays of the top scores of the mode specified.
 */
void HighScores::addHighScore(QString type, int score){
    int tempScore = 0, index = 0;

    if(type == "standard"){
        while(index < 5){
            if(score >= standardInts[index]){
                tempScore = standardInts[index];
                standardInts[index] = score;
                standardScores[index]->setText(QString::number(score));
                index++;
                return;
            }
            index++;
        }
        while(index < 4){
            standardInts[index+1] = standardInts[index];
            standardScores[index+1]->setText(QString::number(standardInts[index+1]));
            standardInts[index] = tempScore;
            standardScores[index]->setText(QString::number(standardInts[index]));
            index++;
        }
    }
    else if(type == "survival"){
        while(index < 5){
            if(score >= survivalInts[index]){
                tempScore = survivalInts[index];
                survivalInts[index] = score;
                survivalScores[index]->setText(QString::number(score));
                index++;
                return;
            }
            index++;
        }
        while(index < 4){
            survivalInts[index+1] = survivalInts[index];
            survivalScores[index+1]->setText(QString::number(survivalInts[index+1]));
            survivalInts[index] = tempScore;
            survivalScores[index]->setText(QString::number(survivalInts[index]));
            index++;
        }
    }
    else if(type == "endless"){
        while(index < 5){
            if(score >= endlessInts[index]){
                tempScore = endlessInts[index];
                endlessInts[index] = score;
                endlessScores[index]->setText(QString::number(score));
                index++;
                return;
            }
            index++;
        }
        while(index < 4){
            endlessInts[index+1] = endlessInts[index];
            endlessScores[index+1]->setText(QString::number(endlessInts[index+1]));
            endlessInts[index] = tempScore;
            endlessScores[index]->setText(QString::number(endlessInts[index]));
            index++;
        }
    }
}

/**
 * @brief HighScores::loadHighScores
 *
 * Sets the text of the QLabels that displays the scores from
 * the int arrays of the scores.
 */
void HighScores::loadHighScores(){
    QString tempString;
    for(int index = 0; index < 5; index++){
        tempString = QString::number(index+1);
        tempString.append(".  ");
        tempString.append(QString::number(standardInts[index]));
        standardScores[index]->setText(tempString);

        tempString = QString::number(index+1);
        tempString.append(".  ");
        tempString.append(QString::number(survivalInts[index]));
        survivalScores[index]->setText(tempString);

        tempString = QString::number(index+1);
        tempString.append(".  ");
        tempString.append(QString::number(endlessInts[index]));
        endlessScores[index]->setText(tempString);
    }
}

/**
 * @brief HighScores::getLabel
 * @param type Game Mode
 * @param index Score Index
 * @return Label for the score of the Game Mode given at the index given.
 *
 * Returns a pointer to the QLabel that displays the score of the game mode
 * given at the index given.
 */
QLabel* HighScores::getLabel(QString type, int index){
    QLabel *ptr;
    if(type == "standard"){
        ptr = standardScores[index];
        return ptr;
    }
    else if(type == "survival"){
        ptr = survivalScores[index];
        return ptr;
    }
    else{
        ptr = endlessScores[index];
        return ptr;
    }
}
