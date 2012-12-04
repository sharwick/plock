/** @Author     Shannon Harwick
  * @brief      The Score frame object controls the score board presented on the top of the screen.
  */



#include <ScoreFrame.h>
#include <QFrame>
#include <QPaintEvent>
#include <QLabel>
#include <QtGui>
#include <QCoreApplication>

using namespace std;

/** @author     Shannon Harwick
  * @brief      Initiate the score board.  As the palette changes, the colors will be overwritten.
  */
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

/** @author     Shannon Harwick
  * @brief      Updates the score board to display current score, formatted with commas.
  * @param      n The input n will be the integer value of the current score.
  */
void ScoreFrame::update(int n) {
    QString num = QLocale(QLocale::English).toString((double) n, 'f', 0);
    text->setText(num);
}


/** @author     Shannon Harwick
  * @brief      Resets the score to 0.  This method must be called before the start of a new game.
  * @return     Void
  */
void ScoreFrame::resetScoreBoard() {
    text->setText("0");
}

