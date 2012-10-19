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
    QSignalMapper *signalMap;
    QGridLayout *grid;
    QLCDNumber *scoreLCD;
    QGraphicsScene *theScene;
    QGraphicsView *blockView;
    QGraphicsRectItem *tempBlock;
    QProgressBar *bombBar, *timeBar;
    QPushButton *menuButton;
    QGraphicsRectItem *tempRect;
    int screenSizeX, screenSizeY;
    int boardSizeX, boardSizeY;
    int blockSize;

    // Methods
    Ui::MainWindow *ui;
    void setupBlocks();
    void setupInterface();
    void setupWindow();
    void mousePressEvent(QFocusEvent *);

private slots:
   void menuPressed();
};

#endif // MAINWINDOW_H
