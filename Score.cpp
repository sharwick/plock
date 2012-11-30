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
  *         An upper bound of 100,000,000 is set on the score.
  * @param  nBlocks The integer nBlocks is the number of blocks deleted in the last move.
  * @param  speedBonus The boolean value speedBonus is not currently in use.  It is intended to allow the score to be incremented if the player makes multiple consecutive moves within a specified timeframe.
  * @return Void
  *
  */
void Score::updateScore(int nBlocks, bool speedBonus) {

    int updateValue;
    updateValue = (nBlocks-1)*(nBlocks-1)*(nBlocks-1)*(nBlocks-1);

    if (speedBonus)
        updateValue += 1;

    updateValue *= multiplier;

    // Set upper limit on score so that there are no issues of overflow/game freezing.
    int upperBound=100000000;

    if (updateValue<upperBound && score<=upperBound)
        score += updateValue;

    if (score>upperBound || updateValue > upperBound)
        score=upperBound;

}

/** @brief  Obtain the current score.
  * @return The integer value of the score.
  *
  */
int Score::getScore() {
   return score;
}


/** @brief  When a star is eliminated, this method is called to increment the multiplier.
  *         An upper bound of 50 is set on the multiplier.
  * @return Void
  *
  */
void Score::incrementMultiplier(){
    if (multiplier<50)
        multiplier++;
}


/** @brief  When a new game is started, the score and multiplier must be returned to their initial values (0 and 1).
  * @return Void
  *
  */
void Score::resetScore() {
    multiplier = 1;
    score=0;
}


/** @brief  This method obtains the current multiplier. It is necessary to display the current multiplier on the board.
  * @return The current integer value of the multiplier.
  *
  */
int Score::getMultiplier() {
    return multiplier;
}


