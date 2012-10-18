#ifndef SCOREFRAME_H
#define SCOREFRAME_H

#include <QFrame>
#include <QLabel>
#include <QPaintEvent>

using namespace std;

class ScoreFrame {

private:


public:
    //QPaintEvent paintEvent;
    QLabel *text;
    ScoreFrame();
    void update(int);
    void resetScoreBoard();
    void paint();
    //void setParent(QWidget*);

};

#endif // SCOREFRAME_H
