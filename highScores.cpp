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
    fileFlag = 0;
    try{
        theFile.open("highscores.txt");
    }
    catch(exception e){
        fileFlag = -1;
    }
}

/**
 * @brief HighScores::~HighScores
 */
HighScores::~HighScores(){

}

/**
 * @brief HighScores::readInHighScores
 */
void HighScores::readInHighScores(){
    if(fileFlag == -1){

        for(int i=0; i < 5; i++){
            standardHighScores[i] = "0";
            survivalHighScores[i] = "0";;
            endlessHighScores[i] = "0";;
        }
    }

    if(fileFlag == 0){

        int index = 0;
        if(theFile.is_open()){
            while(!theFile.eof()){

                getline(theFile, tempString);

                if(index < 5)
                    standardHighScores[index] = tempString;
                else if(index < 10 && index >= 5)
                    survivalHighScores[index-5] = tempString;
                else if(index >= 10)
                    endlessHighScores[index-10] = tempString;

                index++;
            }
        }
        else{
            index = 0;
            while(index < 15){
                if(index < 5)
                    standardHighScores[index] = "0";
                else if(index < 10 && index >= 5)
                    survivalHighScores[index-5] = "0";
                else if(index >= 10)
                    endlessHighScores[index-10] = "0";

                index++;
            }
        }
    }
    theFile.close();
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
char* HighScores::getScore(char* type, int index){
    char *tempChar;

    if(type == "standard"){
        tempChar = (char*)standardHighScores[index].c_str();
        return tempChar;
    }
    else if(type == "survival"){
        tempChar = (char*)survivalHighScores[index].c_str();
        return tempChar;
    }
    else{
        tempChar = (char*)endlessHighScores[index].c_str();
        return tempChar;
    }
}

/**
 * @brief HighScores::addHighScore
 * @param score Score that is sorted into the proper array.
 */
void HighScores::addHighScore(int score){

}
