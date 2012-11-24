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
 * The default and only constructor. All that happens is that readInHighScores is called which
 * opens the file that the past scores are saved to.
 */
HighScores::HighScores()
{
    readInHighScores();
}

/**
 * @brief HighScores::~HighScores
 *
 * The destructor which doesn't really need to unallocate anything.
 */
HighScores::~HighScores(){

}

/**
 * @brief HighScores::readInHighScores
 *
 * This method opens the file highscores.txt and reads in its contents. It is formated as a
 * fifteen line text file where each line is a numerical score. The score is read in as both an
 * int and a string. The first five lines are the standard game mode scores. The next five lines
 * are the survival mode high scores, and the last five are the endless mode high scores. If the
 * file doesn't have enough lines to fill out the high scores then the rest of the scores are set
 * to zero.
 */
void HighScores::readInHighScores(){

    theFile.open("highscores.txt", ios::in | ios::out);

    // File failed to open
    if(!theFile.is_open()){
        for(int i=0; i < 5; i++){
            standardHighScores[i] = "Fail";
            standardInts[i] = -1;
            survivalHighScores[i] = "Fail";
            survivalInts[i] = -1;
            endlessHighScores[i] = "Fail";
            endlessInts[i] = -1;
        }
    }

    else{   // File is open, read in scores
        int index = 0;
        tempString = string();

        while(!theFile.eof()){

            getline(theFile, tempString);   // read in a line

            if(index < 5){
                standardHighScores[index] = tempString;

            }
            else if(index < 10 && index >= 5){
                survivalHighScores[index-5] = tempString;
            }
            else if(index >= 10){
                endlessHighScores[index-10] = tempString;
            }

            index++;
        }

        while(index < 15){
            if(index < 5){
                standardHighScores[index] = "0";
                standardInts[index] = 0;
            }
            else if(index < 10 && index >= 5){
                survivalHighScores[index-5] = "0";
                survivalInts[index-5] = 0;
            }
            else if(index >= 10){
                endlessHighScores[index-10] = "0";
                endlessInts[index-10] = 0;
            }
            index++;
        }
    }
    theFile.close();    // Close File
}

/**
 * @brief HighScores::writeHighScores
 *
 * Takes the string arrays of high scores and writes them in the correct
 * order to the file <highscores.txt>. The order of scores is: the five Standard
 * Mode scores, The five Survival Mode scores, and the five Endless Mode scores.
 */
void HighScores::writeHighScores(){

}

/**
 * @brief HighScores::getScore
 * @param s Index of the score wanted.
 * @return Returns score at the index requested.
 *
 * Given the string and the int sent to the method, it will return the score
 * at the index of the game mode specified.
 */
char* HighScores::getScore(char* type, int index){
    char *tempChar;

    if(strcmp(type, "standard") == 0){
        tempChar = (char*)standardHighScores[index].c_str();
        return tempChar;
    }
    else if(strcmp(type, "survival") == 0){
        tempChar = (char*)survivalHighScores[index].c_str();
        return tempChar;
    }
    else if(strcmp(type, "endless") == 0){
        tempChar = (char*)endlessHighScores[index].c_str();
        return tempChar;
    }
    else
        return 0;
}

/**
 * @brief HighScores::addHighScore
 * @param score Score that is sorted into the proper array.
 *
 * Given the string and the int sent to the method, it will add the score
 * into the index spot of the game mode specified.
 */
void HighScores::addHighScore(char* type, int score){
    int tempScore = 0, index = 0;
    std::stringstream strStream;

    if(strcmp(type, "standard") == 0){
        while(index < 5){
            if(score >= standardInts[index]){
                tempScore = standardInts[index];
                standardInts[index] = score;
                strStream << standardInts[index];
                standardHighScores[index] = strStream.str();
                strStream.flush();
                index++;
                return;
            }
            index++;
        }
        while(index < 4){
            standardInts[index+1] = standardInts[index];
            strStream << standardInts[index+1];
            standardHighScores[index+1] = strStream.str();
            strStream.flush();
            standardInts[index] = tempScore;
            strStream << standardInts[index];
            standardHighScores[index] = strStream.str();
            strStream.flush();
            index++;
        }
    }
    else if(strcmp(type, "survival") == 0){
        while(index < 5){
            if(score >= survivalInts[index]){
                tempScore = survivalInts[index];
                survivalInts[index] = score;
                strStream << survivalInts[index];
                survivalHighScores[index] = strStream.str();
                strStream.flush();
                index++;
                return;
            }
            index++;
        }
        while(index < 4){
            survivalInts[index+1] = survivalInts[index];
            strStream << survivalInts[index+1];
            survivalHighScores[index+1] = strStream.str();
            strStream.flush();
            survivalInts[index] = tempScore;
            strStream << survivalInts[index];
            survivalHighScores[index] = strStream.str();
            strStream.flush();
            index++;
        }
    }
    else if(strcmp(type, "endless") == 0){
        while(index < 5){
            if(score >= endlessInts[index]){
                tempScore = endlessInts[index];
                endlessInts[index] = score;
                strStream << endlessInts[index];
                endlessHighScores[index] = strStream.str();
                strStream.flush();
                index++;
                return;
            }
            index++;
        }
        while(index < 4){
            endlessInts[index+1] = endlessInts[index];
            strStream << endlessInts[index+1];
            endlessHighScores[index+1] = strStream.str();
            strStream.flush();
            endlessInts[index] = tempScore;
            strStream << endlessInts[index];
            endlessHighScores[index] = strStream.str();
            strStream.flush();
            index++;
        }
    }
}
