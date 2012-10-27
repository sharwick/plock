//NOTE: NO LONGER CURRENT; use mainwindow_UI

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QMainWindow>
#include <QSignalMapper>
#include "Block.h" //This will need to be changed for your test to compile
#include "Score.h" //SHupdate
#include "ScoreFrame.h" //SHupdate
#include "Colors.h" // SHupdate

// SHupdate
#include <QPushButton>
#include <QMap>
#include <QString>
#include <QLabel>
#include <QGraphicsView>
#include <QGridLayout>
#include <QGroupBox>
#include <QLCDNumber>
#include <QProgressBar>



namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    Score *scorePtr;  // SHupdate
    int ROWS, COLUMNS; // SHupdate
    Colors *colorPtr;

    enum ScreenOrientation {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };

    Block *myBlock;

    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    // Note that this will only have an effect on Fremantle.
    void setOrientation(ScreenOrientation orientation);

    void showExpanded();


    //SHupdate
    QLCDNumber *scoreLCD;
    QGridLayout *grid;

private slots:
    void button0Clicked();
    void button1Clicked();
    void button2Clicked();
    void button3Clicked();
    void button4Clicked();
    void button5Clicked();
    void button6Clicked();
    void button7Clicked();
    void button8Clicked();
    void quitButtonClicked();
    void resetButtonClicked();
    void shuffleButtonClicked();

    void timeSlot();


private:
    void processMatch(Block*);
    vector<Block*> sortVector(vector<Block*>);
    Block *gameBoard[3][3];
    void determineColor(vector<Block*>);
    //QSignalMapper *blockSignalMapper;
    Ui::MainWindow *ui;
    vector<Block*> bombCollector(vector<Block*>, int, int);
    vector<Block*> checkSpecials(vector<Block*>);

    ScoreFrame *sframe;
    void shuffle();
    void reset();

    void setUpClock();
    void gameOver();
    int currentTime;
    QTimer *timer;
    int x;


};

#endif // MAINWINDOW_H
