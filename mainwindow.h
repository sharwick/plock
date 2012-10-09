#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include "C:/Users/Dan/Desktop/Block.h" //This will need to be changed for your test to compile

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

    Block *myBlock;

    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    // Note that this will only have an effect on Fremantle.
    void setOrientation(ScreenOrientation orientation);

    void showExpanded();

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

private:
    void processMatch(Block*);
    vector<Block*> sortVector(vector<Block*>);
    Block *gameBoard[3][3];
    void determineColor(vector<Block*>);
    //QSignalMapper *blockSignalMapper;
    Ui::MainWindow *ui;
    vector<Block*> bombCollector(vector<Block*>, int, int);
    vector<Block*> checkSpecials(vector<Block*>);
};

#endif // MAINWINDOW_H
