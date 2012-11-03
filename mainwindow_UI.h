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
    QProgressBar *bombBar, *timeBar;
    QPushButton *menuButton,*shuffleButton, *verticalFlipButton, *horizontalFlipButton,  *newGameButton, *settingsButton,
    *helpButton, *backToMenu, *backToMenu2, *backToMenu3, *standardModeButton,
    *pauseAccept, *pauseRejected;
    QGroupBox *mainMenu, *settingsMenu, *helpMenu, *gameModeMenu, *pauseMenu;
    QCheckBox *soundCheck, *screenLockCheck;
    QLabel *titleLabel, *gameModeTitle, *settingsTitle;
    QTextBrowser *helpText;
    QSlider *colorSlider;
    myRectItem* rectArray[8][9];
    QTimer *timer;
    Colors *colorPtr;
    Score *scorePtr;
    ScoreFrame *sframe;

    // Variables
    int screenSizeX, screenSizeY;
    int boardSizeX, boardSizeY;
    int blockSize;
    int xPos, yPos;
    int currentTime;
    int x;
    void setUpClock();
    void gameOver();
    void reset();   
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
   void backToMain();
   void pausedPressed();
   void pauseBack();
   void standardMode();
   void screenLock();
   void noSound();
   void changeColorScheme();
   void verticalFlip();
   void horizontalFlip();

signals:
   void blockPressed(int, int);
};

#endif // MAINWINDOW_H
