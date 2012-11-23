/** @Author     Shannon Harwick
  * @brief      The Score object contains current score, current score multiplier, and methods to retrieve/update the score and multiplier.
  */

#include <Score.h>
#include <iostream>

// using namespace scoreSpace;
using namespace std;


/** @brief  The constructor initializes the score to 0 and the multiplier to 1.
  *
  */
Score::Score() {
        score=0;
        multiplier = 1;
}


/** @brief  The score is updated by adding a quartic polynomial of the number of blocks eliminated.
  * @param  The integer nBlocks is the number of blocks deleted in the last move.
  * @param  The boolean value speedBonus is not currently in use.  It is intended to allow the score to be incremented if the player makes multiple consecutive moves within a specified timeframe.
  * @return Void
  *
  */
void Score::updateScore(int nBlocks, bool speedBonus) {

    int updateValue;
    updateValue = (nBlocks-1)*(nBlocks-1)*(nBlocks-1)*(nBlocks-1);

    if (speedBonus)
        updateValue += 1;

    updateValue *= multiplier;

    score += updateValue;

}

/** @brief  Obtain the current score.
  * @param  None
  * @return The integer value of the score.
  *
  */
int Score::getScore() {
   return score;
}


/** @brief  When a star is eliminated, this method is called to increment the multiplier.
  * @param  None
  * @return Void
  *
  */
void Score::incrementMultiplier(){
    multiplier++;
}


/** @brief  When a new game is started, the score and multiplier must be returned to their initial values (0 and 1).
  * @param  None
  * @return Void
  *
  */
void Score::resetScore() {
    multiplier = 1;
    score=0;
}


/** @brief  This method obtains the current multiplier. It is necessary to display the current multiplier on the board.
  * @param  None
  * @return The current integer value of the multiplier.
  *
  */
int Score::getMultiplier() {
    return multiplier;
}


