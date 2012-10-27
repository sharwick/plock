#include <ScoreFrame.h>
#include <QFrame>
#include <QPaintEvent>
#include <QLabel>
#include <QtGui>

using namespace std;


ScoreFrame::ScoreFrame() {
    text = new QLabel("0",0,0);
    text->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    text->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    text->setLineWidth(4);
    text->setStyleSheet("QLabel {background-color : blue; color : white; font: 9pt \"Courier New\";}");
}

void ScoreFrame::update(int n) {
    text->setText(QString::number(n));
}

void ScoreFrame::resetScoreBoard() {
    text->setText("0");
}

