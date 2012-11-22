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

}

void ScoreFrame::update(int n) {
    QString num = QLocale(QLocale::English).toString((double) n, 'f', 0);
    text->setText(num);
}

void ScoreFrame::resetScoreBoard() {
    text->setText("0");
}

