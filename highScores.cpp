/**@author Devin Rusnak
 * @copyright Blockstar 2012
 * @class HighScores highScores.h "highScores.h"
 * @brief This is a class used to read & write high scores from the game to a file for record.
 * @bug High Scores are not read from the file correctly.
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
        survivalLevels[index] = 0;
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
        delete theFile;
    }
}

/**
 * @brief HighScores::readInHighScores
 * @bug The file gets opened but nothing is read from it.
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
            survivalLevels[i] = 0;
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
            delete tempChar;
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
int HighScores::addHighScore(QString type, int score, int level){
    int tempScore = 0, tempScore2 = 0, index = 0,
            tempLevel = 0, tempLevel2 = 0, rtn = 0;

    if(type == "standard"){
        while(index < 5){
            if(score >= standardInts[index]){
                tempScore = standardInts[index];
                standardInts[index] = score;
                rtn = 1;
                index++;
                break;  // Leave while loop
            }
            index++;
        }
        // Move other scores down
        while(index < 5){
            if(tempScore >= standardInts[index]){
                tempScore2 = standardInts[index];
                standardInts[index] = tempScore;
                tempScore = tempScore2;
            }
            index++;
        }
    }
    else if(type == "survival"){
       QString tempString("");
        while(index < 5){
            if(score >= survivalInts[index]){
                tempScore = survivalInts[index];
                tempLevel = survivalLevels[index];
                survivalInts[index] = score;
                survivalLevels[index] = level;
                rtn = 1;
                index++;
                break;
            }
            index++;
        }
        while(index < 5){
            if(tempScore >= survivalInts[index]){
                tempScore2 = survivalInts[index];
                tempLevel2 = survivalLevels[index];
                survivalInts[index] = tempScore;
                survivalLevels[index] = tempLevel;
                tempScore = tempScore2;
                tempLevel = tempLevel2;
            }
            index++;
        }
    }
    else if(type == "endless"){
        while(index < 5){
            if(score >= endlessInts[index]){
                tempScore = endlessInts[index];
                endlessInts[index] = score;
                rtn = 1;
                index++;
                break;
            }
            index++;
        }
        while(index < 5){
            if(tempScore >= endlessInts[index]){
                tempScore2 = endlessInts[index];
                endlessInts[index] = tempScore;
                tempScore = tempScore2;
            }
            index++;
        }
    }
    return rtn;
}

/**
 * @brief HighScores::loadHighScores
 *
 * Sets the text of the QLabels that displays the scores from
 * the int arrays of the scores.
 */
void HighScores::loadHighScores(){
    QString tempString("");
    for(int index = 0; index < 5; index++){
        tempString = QString::number(index+1);
        tempString.append(".  ");
        tempString.append(QString::number(standardInts[index]));
        standardScores[index]->setText(tempString);

        tempString = QString::number(index+1);
        tempString.append(". <Lvl: ");
        tempString.append(QString::number(survivalLevels[index]));
        tempString.append("> ");
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
