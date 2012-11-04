#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QGraphicsRectItem>
#include <QProgressBar>
#include <QSlider>
#include <QDialogButtonBox>
#include <QMouseEvent>
#include <QTextBrowser>
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
    // Necessitas Stuff
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
    // Objects
    QGridLayout *grid, *settingsLayout;
    QVBoxLayout *mainMenuLayout, *modeMenuLayout, *helpMenuLayout, *pauseMenuLayout;
    QGraphicsScene *theScene;
    QGraphicsView *blockView;
    QGraphicsRectItem *tempBlock;
//    QProgressBar *bombBar, *timeBar;
    QPushButton *menuButton,*shuffleButton, *verticalFlipButton, *horizontalFlipButton,  *newGameButton, *settingsButton,
    *helpButton, *backToMenu, *backToMenu2, *backToMenu3, *standardModeButton,
    *pauseAccept, *pauseRejected, *pauseSettings;
    QGroupBox *mainMenu, *settingsMenu, *helpMenu, *gameModeMenu, *pauseMenu;
    QCheckBox *soundCheck, *screenLockCheck;
    QLabel *titleLabel, *gameModeTitle, *settingsTitle;
    QTextBrowser *helpText;
    QSlider *colorSlider;
    myRectItem* rectArray[8][9];
    QTimer *timer;
    QTimer *btimer;
    Colors *colorPtr;
    Score *scorePtr;
    ScoreFrame *sframe;

    // Variables
    int screenSizeX, screenSizeY;
    int boardSizeX, boardSizeY;
    int blockSize;
    int xPos, yPos;
    int currentTime;
    int bcurrentTime;
    int x, y;
    bool restart;
    void setUpClock();
    void timeOver();
    void btimeOver();
    void btimeBegin();
    void timeBegin();
    void reset();   
    void updateBomb(int nBlocks);
    int multiplier;
	
	//Dan Block Variables
    Block *gameBoard[8][9];

    // Methods
    Ui::MainWindow *ui;
    void setupBlocks();
    void setupGameScreen();
    void setupWindows();
	
	//Dan Block Functions
    void processMatch(Block*);
	vector<Block*> sortVector(vector<Block*>);
	void determineColor(vector<Block*>);
	vector<Block*> checkSpecials(vector<Block*>);
    vector<Block*> bombCollector(vector<Block*>, int, int);

    //vector<GraphObject> scoringObjects; //NYI
	
protected:
    void mousePressEvent(QMouseEvent *event);

private slots:
   void menuPressed();
   void timeSlot();
   void bombtimeSlot();
   void shufflePressed();
   void newGamePressed();
   void settingsPressed();
   void helpPressed();
   void backToMain();
   void backToPause();
   void pausedPressed();
   void pauseSettingsPressed();
   void pauseBack();
   void standardMode();
   void screenLock();
   void noSound();
   void changeColorScheme();
   void verticalFlip();
   void horizontalFlip();

};

#endif // MAINWINDOW_H
