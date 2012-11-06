#include <ScoreFrame.h>
#include <QFrame>
#include <QPaintEvent>
#include <QLabel>
#include <QtGui>
#include <QCoreApplication>

using namespace std;


ScoreFrame::ScoreFrame() {
    text = new QLabel("0",0,0);

    QPalette sfPal;
    sfPal.setColor(QPalette::Button, QColor(0,0,0,255) );
    sfPal.setColor(QPalette::ButtonText,  QColor(250,250,250,255));
    text->setPalette(sfPal);
    text->setAlignment(Qt::AlignCenter);
    text->setFrameStyle(QFrame::Panel);
    QFont sfFont;
    sfFont.setBold(true);
    text->setFont(sfFont);

    /*
    text->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    text->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    text->setLineWidth(4);
    text->setStyleSheet("QLabel {background-color : blue; color : white; font: 9pt \"Courier New\";}");
    */
}

void ScoreFrame::update(int n) {
    text->setText(QString::number(n));
}

void ScoreFrame::resetScoreBoard() {
    text->setText("0");
}

