/** @author     Shannon Harwick/BOMBSTAR
  * @purpose    Create a frame to display the score object
  */

#ifndef SCOREFRAME_H
#define SCOREFRAME_H

#include <QFrame>
#include <QLabel>
#include <QPaintEvent>

using namespace std;

class ScoreFrame {

public:
    QLabel *text;
    ScoreFrame();
    void update(int);
    void resetScoreBoard();
};

#endif // SCOREFRAME_H
