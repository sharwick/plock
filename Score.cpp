/*
 * @Author      Shannon Harwick
 * @Copyright   Shannon Harwick / Plock Team
 * @Purpose     Score object contains current score and methods to retrieve/update
 *
 */

#include <Score.h>
#include <iostream>

// using namespace scoreSpace;
using namespace std;

Score::Score() {
        score=0;
        multiplier = 1;
}

void Score::updateScore(int nBlocks, bool speedBonus) {

    int updateValue;
    updateValue = (nBlocks-1)*(nBlocks-1);

    if (speedBonus)
        updateValue += 1;

    updateValue *= multiplier;

    score += updateValue;

}

int Score::getScore() {
   return score;
}

void Score::incrementMultiplier(){
    multiplier++;
}

void Score::resetScore() {
    multiplier = 1;
    score=0;
}


