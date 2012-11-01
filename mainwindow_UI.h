#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QSignalMapper>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGridLayout>
#include <QGroupBox>
#include <QLCDNumber>
#include <QGraphicsRectItem>
#include <QProgressBar>
#include <QMouseEvent>
#include <myRectItem.h>
#include <QTimer>
#include <Colors.h>
#include <Score.h>
#include <ScoreFrame.h>


//Dan Updates:

#include "Block.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum ScreenOrientation {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };

    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    // Note that this will only have an effect on Fremantle.
    void setOrientation(ScreenOrientation orientation);
    void showExpanded();

private:
    // Variables
    QGridLayout *grid, *mainMenuGrid, *settingMenuGrid, *modeSelectionGrid;
    QGraphicsScene *theScene;
    QGraphicsView *blockView;
    QGraphicsRectItem *tempBlock;
    QProgressBar *bombBar, *timeBar;
    QPushButton *menuButton, *newGameButton, *settingsButton, *helpButton;
    QPushButton *shuffleButton;
    QGroupBox *mainMenu, *settingsMenu, *helpMenu, *gameModeMenu;
    QLabel *titleLabel;
    myRectItem* rectArray[8][9];
    int screenSizeX, screenSizeY;
    int boardSizeX, boardSizeY;
    int blockSize;
    int xPos, yPos;
    int currentTime;
    QTimer *timer;
    int x;
    void setUpClock();
    void gameOver();
    void reset();
    Colors *colorPtr;
    Score *scorePtr;
    ScoreFrame *sframe;
    int multiplier;
	
	//Dan Block Variables
    Block *gameBoard[8][9];

    // Methods
    Ui::MainWindow *ui;
    void setupBlocks();
    void setupInterface();
    void setupWindows();
	
	//Dan Block Functions
    void processMatch(Block*);
	vector<Block*> sortVector(vector<Block*>);
	void determineColor(vector<Block*>);
	vector<Block*> checkSpecials(vector<Block*>);
    vector<Block*> bombCollector(vector<Block*>, int, int);
	
protected:
    void mousePressEvent(QMouseEvent *event);

private slots:
   void menuPressed();
   void timeSlot();
   void shufflePressed();
   void newGamePressed();
   void settingsPressed();
   void helpPressed();

signals:
   void blockPressed(int, int);
};

#endif // MAINWINDOW_H
