#include <ScoreFrame.h>
#include <QFrame>
#include <QPaintEvent>
#include <QLabel>
#include <QtGui>

using namespace std;


ScoreFrame::ScoreFrame() {
    text = new QLabel("0",0,0);
    //text->setText("<FONT FACE=\"courier\" COLOR=\"#FF00FF\">TEST<\\FONT>");  // play with HTML within QT

    //QFont* font = new QFont("Courier New");
    //font->setItalic(true);
    //font->setPixelSize(40);
    //text->setFont(*font);

    text->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    text->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    text->setLineWidth(4);

    //text->setStyleSheet("QLabel {background-color : blue; color : white; font: 9pt \"Courier New\";}");
    text->setStyleSheet("QLabel {background-color : blue; color : white; font: 9pt \"Courier New\";}");

    //text->show();
    //text->setVisible(true);

    // setup frame as background to score text

}

void ScoreFrame::update(int n) {
    text->setText(QString::number(n));
}

void ScoreFrame::resetScoreBoard() {
    text->setText("0");
}


void ScoreFrame::paint() {

    // TO DO
}
