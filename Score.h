/*
 * @Author      Shannon Harwick
 * @Copyright   Shannon Harwick / Plock Team
 * @Purpose     Score object contains current score and methods to retrieve/update
 *
 */

#ifndef SCORE_H
#define SCORE_H

//using namespace scoreSpace;

using namespace std;

class Score {

private:
    int score;
    int multiplier;

public:
    Score();
    int getScore();
    void updateScore(int, bool);
    void resetScore();
    void incrementMultiplier();
    int getMultiplier();
};

#endif // SCORE_H
