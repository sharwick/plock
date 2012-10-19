#include "mainwindow.h"
#include "ui_mainwindow.h"

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

/******************************
 * Default Necessitas Methods
 ******************************/
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
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
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

/***************************************************
  setupWindow():
   This method sets the size of the mainWindow
   based on the size of the phone screen. It also
   uses these parameters to determine the size of
   the game blocks so they can appear on screen
   in a aesthicly pleasing manner.
 ***************************************************/
void MainWindow::setupWindow(){

    // Set Size of MainWindow
    screenSizeX = 240;  // Should get the screen size from phone somehow
    screenSizeY = 400;
    ui->centralWidget->setFixedWidth(screenSizeX);
    ui->centralWidget->setFixedHeight(screenSizeY);

    // Set Size of Blocks based on Window Size and Board Size
    boardSizeX = 7;
    boardSizeY = 9;
    int tempSizeY = screenSizeY/.7;

    if( (screenSizeX / boardSizeX) < (tempSizeY / boardSizeY) )
        blockSize = screenSizeX / boardSizeX;
    else
        blockSize = tempSizeY / boardSizeY;

    //ui->centralWidget->setStyle(QStyle(QPixmap("")));
    grid = new QGridLayout(this);
    grid->setAlignment(Qt::AlignTop);
    grid->setContentsMargins(0,0,0,0);
    grid->setHorizontalSpacing(blockSize);
    grid->setVerticalSpacing(0);
    ui->centralWidget->setLayout(grid);

} // End setupWindow()

/***************************************************
  setupInterface():
   This method initalizes and places all of the
   widgets used in the game. The GraphicsView is
   where the Blocks will go and what the user will
   interact with other than the menu button. All
   widget sizes are based on the size of the screen.
 ***************************************************/
void MainWindow::setupInterface(){

    // Set Labels
    grid->addWidget(new QLabel("Bombs:"),0,1);
    grid->addWidget(new QLabel("Score:"),0,0);
    grid->addWidget(new QLabel("Time:"),3,0);

    // Score LCD Number
    scoreLCD = new QLCDNumber(this);
    scoreLCD->setFixedSize(blockSize * 2,blockSize);
    scoreLCD->setDigitCount(7);
    scoreLCD->setSegmentStyle(QLCDNumber::Flat);
    scoreLCD->display(1337);
    grid->addWidget(scoreLCD,1,0,Qt::AlignLeft);

    // Bomb Progress Bar
    bombBar = new QProgressBar(this);
    bombBar->setFixedSize(blockSize * 3,blockSize);
    grid->addWidget(bombBar,1,1, Qt::AlignLeft);

    // Menu Button
    menuButton = new QPushButton("Menu",this);
    menuButton->setFixedSize(blockSize * 1.3 ,blockSize * 1.3);
    connect(menuButton, SIGNAL(clicked()),this, SLOT(menuPressed()));
    grid->addWidget(menuButton,1,3, Qt::AlignRight);

    // Block Viewing Area
    theScene = new QGraphicsScene();
    theScene->setSceneRect(0, 0, screenSizeX-2, (blockSize * boardSizeY)-2);
    blockView = new QGraphicsView(theScene);
    blockView->setFixedSize(screenSizeX, blockSize * boardSizeY);
    grid->addWidget(blockView,2,0);
    blockView->show();

    // Time Progress Bar
    timeBar = new QProgressBar(this);
    timeBar->setFixedSize(screenSizeX - (screenSizeX/4), 20);
    grid->addWidget(timeBar,3,1,1,0,Qt::AlignLeft);

    // Setup Paused Menu

} // End setupInterface()

/***************************************************
  setupBlocks():
   This method......
 ***************************************************/
void MainWindow::setupBlocks(){

    int index = 0;

    for(int y = 0; y < boardSizeY; y++){
        for(int x = 0; x < boardSizeX; x++){

            tempRect = new QGraphicsRectItem();
            tempRect->setRect(blockSize * x, blockSize * y, blockSize, blockSize);
            tempRect->setFlags(QGraphicsItem::ItemIsSelectable);
            theScene->addItem(tempRect);
            //rectArray[x][y] = tempRect;
            index ++;

        }
    }

} // End setupBlocks()


void MainWindow::menuPressed(){

}
