/**********************************
 * Plock - An android game
 * MainWindow.cpp
 *
 * @author Devin Rusnak
 * @version Qt:4.8.3
 * UIC CS 340 Fall 2012
 *
 * Updates:
 *  10/25 - Got QBrush working, added some comments.
 *
 *
 *
 **********************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    setupWindow();
    setupInterface();
    setupBlocks();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**********************
 * Necessitas Methods *
 **********************/
void MainWindow::setOrientation(ScreenOrientation orientation)
{
    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
        // INSERT CODE HERE
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        // INSET CODE HERE
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
#endif // QT_VERSION < 0x040702
    };
    setAttribute(attribute, true);
}

void MainWindow::showExpanded()
{
#if defined(Q_WS_SIMULATOR)
    showFullScreen();
#elif defined(Q_WS_MAEMO_5)
    showMaximized();
#else
    show();
#endif
}

/*********************************************************************
  void setupWindow():

    This method sets the size of the mainWindow based on the size of
    the phone screen. It also uses these parameters to determine the
    size the game blocks should be to fit evenly on the board. Also
    the gridLayout that organizes the items on screen is instantiated.

 *********************************************************************/
void MainWindow::setupWindow(){

    // Get the size of the phone screen and set centralWidget to that size
    ui->centralWidget->maximumSize();
    screenSizeX = QApplication::desktop()->screenGeometry(-1).width();
    screenSizeY = QApplication::desktop()->screenGeometry(-1).height();
    ui->centralWidget->setBaseSize(screenSizeX, screenSizeY);

    // Set Size of Blocks based on Window Size and Board Size
    int tempSizeY = screenSizeY/.7;
    boardSizeX = 7;
    boardSizeY = 9;

    if( (screenSizeX / boardSizeX) < (tempSizeY / boardSizeY) )
        blockSize = screenSizeX / boardSizeX;
    else
        blockSize = tempSizeY / boardSizeY;

    grid = new QGridLayout(this);
    grid->setAlignment(Qt::AlignTop);
    grid->setContentsMargins(0,0,0,0);
    grid->setHorizontalSpacing(3);
    grid->setVerticalSpacing(0);
    ui->centralWidget->setLayout(grid);

} // End setupWindow()

/*********************************************************************
  void setupInterface():

    This method initalizes and places all of the widgets used in the
    game. The main game board is a QGraphicsView with a QGraphicsScene
    with custom QGraphicsRectItems.

 *********************************************************************/
void MainWindow::setupInterface(){

    // Set Labels
    grid->addWidget(new QLabel("Bombs:"),0,1);
    grid->addWidget(new QLabel("Score:"),0,0);
    grid->addWidget(new QLabel("Time:"),7,0);

    // Score LCD Number
    scoreLCD = new QLCDNumber(this);
    scoreLCD->setFixedSize(blockSize*2,blockSize);
    scoreLCD->setDigitCount(7);
    scoreLCD->setSegmentStyle(QLCDNumber::Flat);
    scoreLCD->display(1337);
    grid->addWidget(scoreLCD,1,0,Qt::AlignLeft);

    // Bomb Progress Bar
    bombBar = new QProgressBar(this);
    bombBar->setFixedSize(blockSize * 2, blockSize);
    grid->addWidget(bombBar,1,1);

    // Menu Button
    menuButton = new QPushButton("Menu",this);
    menuButton->setFixedSize(blockSize * 1.2 ,blockSize * 1.2);
    connect(menuButton, SIGNAL(clicked()),this, SLOT(menuPressed()));
    grid->addWidget(menuButton,1,2);

    // Block Viewing Area
    theScene = new QGraphicsScene();
    theScene->setSceneRect(0, 0, screenSizeX-4, (blockSize * boardSizeY)-4);
    blockView = new QGraphicsView(theScene);
    blockView->setFixedSize(screenSizeX, blockSize * boardSizeY);
    grid->addWidget(blockView,2,0,5,5);
    blockView->show();

    // Time Progress Bar
    timeBar = new QProgressBar(this);
    timeBar->setFixedSize(screenSizeX - (screenSizeX/4), 20);
    grid->addWidget(timeBar,7,1);

    // Setup Paused Menu

} // End setupInterface()

/*********************************************************************
  void setupBlocks():

    This method instantiates a two dimentional array of the custom
    QGraphicsRectItem class myRectItems. They are set to selectable
    so that they will emit mouse events. Then they are added to the
    QGraphicsScene theScene.

 *********************************************************************/
void MainWindow::setupBlocks(){

    for(int y = 0; y < boardSizeY; y++){
        for(int x = 0; x < boardSizeX; x++){

            rectArray[x][y] = new myRectItem();
            rectArray[x][y]->setRect(blockSize * x, blockSize * y, blockSize, blockSize);
            rectArray[x][y]->setFlags(QGraphicsItem::ItemIsSelectable);
            theScene->addItem(rectArray[x][y]);
        }
    }

} // End setupBlocks()

/*********************************************************************
  void mousePressEvent(QMouseEvent):

    This method accepts the mouse event that the QGraphicsScene
    emit and calculates the cords of the selected rectItem in
    the rectArray. Then other things will be done.

 *********************************************************************/
void MainWindow::mousePressEvent(QMouseEvent *event){
    // Accont for the size of the GraphicsScene
    int offset = screenSizeY * 0.15;

    // Calculate the array cords
    xPos = event->x() / blockSize;
    yPos = (event->y() - offset) / blockSize;

    // Color it
    theBrush = QBrush(Qt::red, Qt::SolidPattern);
    rectArray[xPos][yPos]->setBrush(theBrush);

    // Ungrab the mouse
    rectArray[xPos][yPos]->ungrabMouse();

    // Unselect it so others can be
    rectArray[xPos][yPos]->setSelected(false);

    // Emit cords
    emit blockPressed(xPos, yPos);

} // End mousePressEvent

void MainWindow::menuPressed(){

}
