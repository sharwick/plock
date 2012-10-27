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
    QGridLayout *grid;
    QGraphicsScene *theScene;
    QGraphicsView *blockView;
    QGraphicsRectItem *tempBlock;
    QLCDNumber *scoreLCD;
    QProgressBar *bombBar, *timeBar;
    QPushButton *menuButton;
    myRectItem* rectArray[7][9];
    int screenSizeX, screenSizeY;
    int boardSizeX, boardSizeY;
    int blockSize;
    int xPos, yPos;
	
	//Dan Block Variables
	Block *gameBoard[7][9];

    // Methods
    Ui::MainWindow *ui;
    void setupBlocks();
    void setupInterface();
    void setupWindow();
	
	//Dan Block Functions
	void processMatches(Block*);
	vector<Block*> sortVector(vector<Block*>);
	void determineColor(vector<Block*>);
	vector<Block*> checkSpecials(vector<Block*>);
	vector<Block*> bombCollector(vector<Block*>);
	
protected:
    void mousePressEvent(QMouseEvent *event);

private slots:
   void menuPressed();

signals:
   void blockPressed(int, int);
};

#endif // MAINWINDOW_H
