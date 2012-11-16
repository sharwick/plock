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
#include <QString>
#include <QDialogButtonBox>
#include <QMouseEvent>
#include <QTextBrowser>
#include <myRectItem.h>
#include <QTimer>
#include <Colors.h>
#include <Score.h>
#include <ScoreFrame.h>
#include <highScores.h>
#include <QGraphicsEllipseItem>

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
    QGridLayout *grid, *modeMenuLayout, *settingsLayout, *confirmLayout, *highScoreLayout;
    QVBoxLayout *mainMenuLayout, *helpMenuLayout, *pauseMenuLayout, *gameOverLayout, *startLayout;
    QGraphicsScene *theScene;
    QGraphicsView *blockView;
    QGraphicsRectItem *tempBlock;
//    QProgressBar *bombBar, *timeBar;
    QPushButton *menuButton,*shuffleButton, *rotateButton, *horizontalFlipButton,  *newGameButton, *settingsButton,
    *helpButton, *backToMenu, *backToMenu2, *backToMenu3, *backToMenu4, *standardModeButton, *highScoreButton,
    *pauseAccept, *pauseRejected, *pauseSettings, *endlessModeButton, *survivalModeButton, *gameOverToMenu, *gameOverRestart,
    *quitButton, *confirmAcceptButton, *confirmRejectButton;
    QGroupBox *mainMenu, *settingsMenu, *helpMenu, *gameModeMenu, *pauseMenu, *gameOverMenu, *confirmMenu, *highScoreMenu, *startScreen;
    QCheckBox *soundCheck, *screenLockCheck;
    QLabel *titleLabel, *gameModeTitle, *settingsTitle, *timeLabel, *bombLayer, *bombFill, *Timeclock, *Timefill, *finalLevelLabel;
    QTextBrowser *helpText, *highScoreText;
    QSlider *colorSlider;
    QLabel *tempScore, *tempLevel, *score1, *score2, *score3, *score4, *score5, *score6, *score7, *score8, *score9, *score10;
    myRectItem* rectArray[8][9];
    QTimer *timer;
    QTimer *btimer;
    Colors *colorPtr;
    Score *scorePtr;
    ScoreFrame *sframe;
    int level;
    int timerCounter;
    QGraphicsEllipseItem *myEllipse;
    HighScores *theHighScores;


    // Variables
    int screenSizeX, screenSizeY;
    int boardSizeX, boardSizeY;
    int blockSize;
    int xPos, yPos;
    int currentTime;
    int bcurrentTime;
    int stdModeFlag, endlessModeFlag, survivalModeFlag;
    int x, y;
    bool start;
    void setUpClock();
    void timeOver();
    void btimeOver();
    void btimeBegin();
    void timeBegin();
    void reset();   
    void updateBomb(int nBlocks);
    void updateProgress(int);
    int multiplier;
	
	//Dan Block Variables
    Block *gameBoard[8][9];

    // Methods
    Ui::MainWindow *ui;
    void setupBlocks();
    void setupGameScreen();
    void setupWindows();
    void startGame();
    void loadHighScores();
	
	//Dan Block Functions
    void processMatch(Block*);
	vector<Block*> sortVector(vector<Block*>);
	void determineColor(vector<Block*>);
	vector<Block*> checkSpecials(vector<Block*>);
    vector<Block*> bombCollector(vector<Block*>, int, int);

    void processProgress();
    void generateGraphicObject();

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
   void highScoresShow();
   void gameOverRestartSlot();
   void gameOverMenuSlot();
   void standardMode();
   void endlessMode();
   void survivalMode();
   void screenLock();
   void noSound();
   void changeColorScheme();
   void verticalFlip();
   void horizontalFlip();
   void rotate();
   void confirmQuit();
   void quitRejected();
   void quit();


};

#endif // MAINWINDOW_H
