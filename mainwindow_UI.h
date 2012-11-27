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
#include <QFont>
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
    QVBoxLayout *mainMenuLayout, *helpMenuLayout, *pauseMenuLayout, *gameOverLayout, *startLayout, *levelClearLayout;
    QGraphicsScene *theScene;
    QGraphicsView *blockView;
    QGraphicsRectItem *tempBlock;
//    QProgressBar *bombBar, *timeBar;
    QPushButton *menuButton,*shuffleButton, *rotateButton, *horizontalFlipButton,  *newGameButton, *settingsButton,
    *helpButton, *backToMenu, *backToMenu2, *backToMenu3, *backToMenu4, *standardModeButton, *highScoreButton,
    *pauseAccept, *pauseRejected, *pauseSettings, *pauseHighScore, *endlessModeButton, *survivalModeButton, *gameOverToMenu, *gameOverRestart,
    *quitButton, *confirmAcceptButton, *confirmRejectButton, *gameOverHighScore, *levelNext;
    QGroupBox *mainMenu, *settingsMenu, *helpMenu, *gameModeMenu, *pauseMenu, *confirmMenu, *gameOverMenu, *highScoreMenu, *startScreen, *levelClear;
    QLabel *titleLabel, *gameModeTitle, *settingsTitle, *timeLabel, *bombLayer, *bombFill, *Timeclock, *Timefill, *finalLevelLabel, *finalScoreLabel,
    *bombLabel, *scoreLabel, *pauseLabel, *quitLabel, *colorSchemeLabel, *pressScreenLabel, *highScoresLabel, *levelClearLabel, *progressLabel,
    *standardLabel, *survivalLabel, *endlessLabel, *aboutLabel;
    QTextBrowser *helpText, *highScoreText;
    QSlider *colorSlider;
    QLabel *tempScore, *tempLevel, *newHighScore;
    myRectItem* rectArray[8][9];
    QTimer *timer, *btimer, *gtimer;
    QString aboutText;
    QFont tempFont;
    Colors *colorPtr;
    Score *scorePtr;
    ScoreFrame *sframe;
    QGraphicsEllipseItem *myEllipse;
    HighScores *theHighScores;
    vector<QLabel*> labelVector;
    vector<QPushButton*> buttonVector;

    // Variables
    int screenSizeX, screenSizeY;
    int boardSizeX, boardSizeY;
    int blockSize;
    int xPos, yPos;
    int level;
    int progressLevel;
    int timerCounter;
    int currentTime;
    int bcurrentTime;
    int gCount;
    int stdModeFlag, endlessModeFlag, survivalModeFlag;
    int x, y, k;
    bool start, gamedone;
    void setUpClock();
    void timeOver();
    void btimeOver();
    void btimeBegin();
    void timeBegin();
    void reset();   
    void updateBomb(int nBlocks);
    void updateProgress(int);
    void graphSwap(int, int, int, int);
	
	//Dan Block Variables
    Block *gameBoard[8][9];

    // Methods
    Ui::MainWindow *ui;
    void setupBlocks();
    void setupGameScreen();
    void setupWindows();
    void startGame();
    void scoreLabelsUpdate();
	
	//Dan Block Functions
    void processMatch(Block*);
	vector<Block*> sortVector(vector<Block*>);
	void determineColor(vector<Block*>);
	vector<Block*> checkSpecials(vector<Block*>);
    vector<Block*> bombCollector(vector<Block*>, int, int);

    void processProgress();
    void generateGraphicObject(int, int);
    void removeBlocks();

    //vector<GraphObject> scoringObjects; //NYI

    //QTimer *blockTimer;
    //int blockTimerCounter;
	
protected:
    void mousePressEvent(QMouseEvent *event);

private slots:
   void menuPressed();
   void timeSlot();
   void gtimeSlot();
   void bombtimeSlot();
   void shufflePressed();
   void newGamePressed();
   void settingsPressed();
   void helpPressed();
   void backToMain();
   void backToPause();
   void backToGameOver();
   void pausedPressed();
   void pauseSettingsPressed();
   void pauseBack();
   void highScoresShow();
   void gameOverRestartSlot();
   void gameOverMenuSlot();
   void addScore();
   void standardMode();
   void endlessMode();
   void survivalMode();
   void nextLevel();
   void changeColorScheme();
   void verticalFlip();
   void horizontalFlip();
   void rotate();
   void confirmQuit();
   void quitRejected();
   void quitRejectedGameOver();
   void quit();

   //void blockTimerSlot();


};

#endif // MAINWINDOW_H
