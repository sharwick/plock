/***********************************************************
 * Plock - An android game
 * MainWindow.cpp
 *
 * @authors Devin Rusnak, Daniel K, Shannon H, Mike Son
 * @version Qt:4.8.3
 * UIC CS 340 Fall 2012
 *
 ***********************************************************/
#include "mainwindow_UI.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Call our setup methods
    setupWindows();
    setupGameScreen();
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
        // INSERT CODE HERE FOR SCREEN FLIP IF WE DARE
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        // INSERT CODE HERE FOR SCREEN FLIP IF WE DARE
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
} // End Necessitas Stuff

/*********************************************************************
  void setupWindow():
    This method sets the size of the mainWindow based on the size of
    the phone screen. It also uses these parameters to determine the
    size the game blocks should be to fit evenly on the board. Also
    the gridLayout that organizes the items on screen is instantiated.
    The central widget acts as the base widget. The game board is
    placed onto this widget and all accompaning items. The centralWidget
    is also the parent of the menu Widgets so they simply appear over
    the game board which is always there but not always visable or
    interactable.
    ADDED:
    This is also where the menus and their items are instantiated. They
    are simple group box widgets that take up the whole screen and are
    .show/.hide depending on when we need them.
 *********************************************************************/
void MainWindow::setupWindows(){

    /* * * * * * * * * * * * * *
     * Setup the CentralWidget *
     * * * * * * * * * * * * * */
    // Get the size of the phone screen and set centralWidget to that size
    ui->centralWidget->maximumSize();
    screenSizeX = QApplication::desktop()->screenGeometry(-1).width();
    screenSizeY = QApplication::desktop()->screenGeometry(-1).height();
    ui->centralWidget->setBaseSize(screenSizeX, screenSizeY);

    // Set Size of Blocks based on Window Size and Board Size
    int tempSizeY = screenSizeY * 0.8;
    boardSizeX = 8;
    boardSizeY = 9;
    if( (screenSizeX / boardSizeX) < (tempSizeY / boardSizeY) )
        blockSize = screenSizeX / boardSizeX;
    else
        blockSize = tempSizeY / boardSizeY;

    // Setup the grid layout for the game screen
    grid = new QGridLayout(this);
    grid->setAlignment(Qt::AlignTop);
    grid->setContentsMargins(0,0,0,0);
    grid->setHorizontalSpacing(3);
    grid->setVerticalSpacing(0);
    ui->centralWidget->setLayout(grid);



    /* * * * * * * * * * * * * * * * *
     * Setup Main Menu and its items *
     * * * * * * * * * * * * * * * * */
    // Initalize Widget
    mainMenu = new QGroupBox(this);
    mainMenu->setFixedSize(screenSizeX, screenSizeY);
    mainMenu->setAutoFillBackground(true);

    // Create Main Menu's layout
    mainMenuLayout = new QVBoxLayout(this);
    mainMenuLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    mainMenuLayout->setSpacing(0);
    mainMenu->setLayout(mainMenuLayout);

    // Initialize and add items to layout
    titleLabel = new QLabel("B L O C K S T A R");
    titleLabel->setFixedSize(blockSize*5, blockSize*2);
    mainMenuLayout->addWidget(titleLabel, Qt::AlignHCenter);

    newGameButton = new QPushButton(this);
    newGameButton->setText("New Game");
    newGameButton->setFixedSize(blockSize*5, blockSize);
    connect( newGameButton, SIGNAL(clicked()), this, SLOT(newGamePressed()) );
    mainMenuLayout->addWidget(newGameButton, Qt::AlignTop);


    settingsButton = new QPushButton("Settings", this);
    settingsButton->setFixedSize(blockSize*5, blockSize);
    connect( settingsButton, SIGNAL(clicked()), this, SLOT(settingsPressed()) );
    mainMenuLayout->addWidget(settingsButton, Qt::AlignTop);


    helpButton = new QPushButton("About", this);
    helpButton->setFixedSize(blockSize*5, blockSize);
    connect( helpButton, SIGNAL(clicked()), this, SLOT(helpPressed()) );
    mainMenuLayout->addWidget(helpButton, Qt::AlignTop);

    quitButton = new QPushButton("Quit", this);
    quitButton->setFixedSize(blockSize*5, blockSize);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(quit()) );
    mainMenuLayout->addWidget(quitButton, Qt::AlignTop);


    /* * * * * * * * * * * * * * * * * * *
     * Setup GameMode Menu and its items *
     * * * * * * * * * * * * * * * * * * */
    // Initalize Widget
    gameModeMenu = new QGroupBox(this);
    gameModeMenu->setFixedSize(screenSizeX, screenSizeY);
    gameModeMenu->setAutoFillBackground(true);
    gameModeMenu->hide();

    // Create the Menu's layout
    modeMenuLayout = new QGridLayout(this);
    modeMenuLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    modeMenuLayout->setSpacing(30);
    gameModeMenu->setLayout(modeMenuLayout);

    // Initalize and add Items to layout
    gameModeTitle = new QLabel("Choose A Game Mode");
    modeMenuLayout->addWidget(gameModeTitle, 0, 1,  Qt::AlignTop);

    standardModeButton = new QPushButton("Standard Mode", this);
    connect(standardModeButton, SIGNAL(clicked()), this, SLOT(standardMode()) );
    modeMenuLayout->addWidget(standardModeButton, 2, 1, Qt::AlignTop);

    survivalModeButton = new QPushButton("Survival Mode", this);
    connect(survivalModeButton, SIGNAL(clicked()), this, SLOT(survivalMode()) );
    modeMenuLayout->addWidget(survivalModeButton, 3, 1, Qt::AlignTop);

    endlessModeButton = new QPushButton("Endless Mode", this);
    connect(endlessModeButton, SIGNAL(clicked()), this, SLOT(endlessMode()) );
    modeMenuLayout->addWidget(endlessModeButton, 4, 1, Qt::AlignTop);

    backToMenu = new QPushButton("Back", this);
    connect(backToMenu, SIGNAL(clicked()), this, SLOT(backToMain()) );
    modeMenuLayout->addWidget(backToMenu, 6, 1, Qt::AlignTop);



    /* * * * * * * * * * * * * * * * * * *
     * Setup Settings Menu and its items *
     * * * * * * * * * * * * * * * * * * */
    // Initalize Widget
    settingsMenu = new QGroupBox(this);
    settingsMenu->setFixedSize(screenSizeX, screenSizeY);
    settingsMenu->setAutoFillBackground(true);
    settingsMenu->hide();

    // Create the Menu's layout
    settingsLayout = new QGridLayout(this);
    settingsLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    settingsLayout->setSpacing(0);
    settingsMenu->setLayout(settingsLayout);

    // Initalize and add Items to the layout
    settingsTitle = new QLabel("S e t t i n g s");
    settingsLayout->addWidget(settingsTitle, 0, 0, Qt::AlignTop);

    soundCheck = new QCheckBox(this);
    soundCheck->setCheckable(true);
    soundCheck->setAutoExclusive(false);
    soundCheck->setTristate(false);
    connect(soundCheck, SIGNAL(clicked()), this, SLOT(noSound()) );
    settingsLayout->addWidget(new QLabel("No Sound:"), 1, 0, Qt::AlignLeft);
    settingsLayout->addWidget(soundCheck, 1, 1);

    screenLockCheck = new QCheckBox(this);
    screenLockCheck->setCheckable(true);
    screenLockCheck->setAutoExclusive(false);
    screenLockCheck->setTristate(false);
    connect(screenLockCheck, SIGNAL(clicked()), this, SLOT(screenLock()));
    settingsLayout->addWidget(new QLabel("Lock Screen:"), 2, 0, Qt::AlignLeft);
    settingsLayout->addWidget(screenLockCheck, 2, 1);

    backToMenu2 = new QPushButton("Back", this);
    connect(backToMenu2, SIGNAL(clicked()), this, SLOT(backToMain()) );
    settingsLayout->addWidget(backToMenu2, 4, 0, Qt::AlignHCenter);

    colorSlider = new QSlider(Qt::Horizontal ,this);
    colorSlider->setRange(0,3);
    settingsLayout->addWidget(new QLabel("Color Scheme:"), 3, 0, Qt::AlignLeft);
    settingsLayout->addWidget(colorSlider, 3, 1);



    /* * * * * * * * * * * * * * * * *
     * Setup Help Menu and its items *
     * * * * * * * * * * * * * * * * */
    // Initalize Widget
    helpMenu = new QGroupBox(this);
    helpMenu->setFixedSize(screenSizeX, screenSizeY);
    helpMenu->setAutoFillBackground(true);
    helpMenu->hide();

    // Create the Menu's layout
    helpMenuLayout = new QVBoxLayout(this);
    helpMenuLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    helpMenuLayout->setSpacing(0);
    helpMenu->setLayout(helpMenuLayout);

    // Initialize and add Items to the layout
    helpMenuLayout->addWidget(new QLabel("About"), Qt::AlignTop | Qt::AlignHCenter);
    helpMenuLayout->addWidget(new QLabel("B L O C K S T A R"), Qt::AlignTop);

    helpText = new QTextBrowser(this);
    helpText->setFixedSize(screenSizeX * 0.9, screenSizeY * 0.75);
    helpText->setText(QString("Blockstar \n"
                                  "An android game based on Plock. \n"
                                  "UIC CS 340 Fall 2012 \n"
                                  "Authors: Shannon Harwick, Daniel Keasler, Devin Rusnak, Mike Son \n" ));
    helpMenuLayout->addWidget(helpText, Qt::AlignLeft);

    backToMenu3 = new QPushButton("Back", this);
    connect(backToMenu3, SIGNAL(clicked()), this, SLOT(backToMain()) );
    helpMenuLayout->addWidget(backToMenu3, Qt::AlignHCenter);



    /* * * * * * * * * * * * * * * * * *
     * Setup Pause Menu and its Items  *
     * * * * * * * * * * * * * * * * * */
    // Initalize Widget
    pauseMenu = new QGroupBox(this);
    pauseMenu->setAutoFillBackground(true);
    pauseMenu->setGeometry( (screenSizeX/2) - ((screenSizeX * 0.8) / 2), (screenSizeY/2) - ((screenSizeY * 0.4) / 2),
                            screenSizeX * 0.8 , screenSizeY * 0.4 );
    // Create Menu's layout
    pauseMenuLayout = new QVBoxLayout(this);
    pauseMenuLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    pauseMenuLayout->setSpacing(25);
    pauseMenu->setLayout(pauseMenuLayout);
    pauseMenu->hide();

    // Initialize and add Items to the layout
    pauseMenuLayout->addWidget(new QLabel("   Paused"), Qt::AlignHCenter | Qt::AlignTop);
    pauseRejected = new QPushButton("Resume", this);
    pauseSettings = new QPushButton("Settings", this);
    pauseAccept = new QPushButton("Main", this);
    pauseMenuLayout->addWidget(pauseRejected, Qt::AlignTop);
    pauseMenuLayout->addWidget(pauseSettings, Qt::AlignVCenter);
    pauseMenuLayout->addWidget(pauseAccept, Qt::AlignBottom);
    connect(pauseRejected, SIGNAL(clicked()), this, SLOT(pauseBack()) );
    connect(pauseSettings, SIGNAL(clicked()), this, SLOT(pauseSettingsPressed()) );
    connect(pauseAccept, SIGNAL(clicked()), this, SLOT(menuPressed()) );



    /* * * * * * * * * * * * * * * * * * * *
     * Setup Game Over Menu and its Items  *
     * * * * * * * * * * * * * * * * * * * */
    // Initalize Widget
    gameOverMenu = new QGroupBox(this);
    gameOverMenu->setAutoFillBackground(true);
    gameOverMenu->setGeometry( (screenSizeX/2) - ((screenSizeX * 0.8) / 2), (screenSizeY/2) - ((screenSizeY * 0.4) / 2),
                            screenSizeX * 0.8 , screenSizeY * 0.4 );
    // Create Menu's Layout
    gameOverLayout = new QVBoxLayout(this);
    gameOverLayout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    gameOverLayout->setSpacing(20);
    gameOverMenu->setLayout(gameOverLayout);
    gameOverMenu->hide();

    // Initalize and add Items to the layout
    scorePtr = new Score(); // Moved
    gameOverLayout->addWidget(new QLabel("Your Final Score:", this));
    tempScore = new QLabel(this);
    tempScore->setAlignment(Qt::AlignHCenter);
    gameOverLayout->addWidget(tempScore, Qt::AlignHCenter);

    gameOverRestart = new QPushButton("Restart Game", this);
    connect(gameOverRestart, SIGNAL(clicked()), this, SLOT(gameOverRestartSlot()) );
    gameOverLayout->addWidget(gameOverRestart);

    gameOverToMenu = new QPushButton("Main Menu", this);
    connect(gameOverToMenu, SIGNAL(clicked()), this, SLOT(gameOverMenuSlot()) );
    gameOverLayout->addWidget(gameOverToMenu);

} // End setupWindow()

/*********************************************************************
  void setupGameScreen():
    This method initalizes and places all of the widgets used in the
    game. The main game board is a QGraphicsView with a QGraphicsScene
    with custom QGraphicsRectItems.
 *********************************************************************/
void MainWindow::setupGameScreen(){

    // Color scheme
    colorPtr = new Colors(0);
    //colorPtr = new Colors(1);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Button, colorPtr->getQColor(3));
    Pal.setColor(QPalette::ButtonText, QColor(0,0,0,255) );
    Pal.setColor(QPalette::Background, colorPtr->getQColor(0));
    //Pal.setColor(QPalette::Text, QColor(250,250,250,127));
    Pal.setColor(QPalette::Text, colorPtr->getQColor(3));
    ////Pal.setColor(QPalette::BrightText, QColor(250,250,250,127));
    //Pal.setColor(QPalette::WindowText, QColor(250,250,250,127));
    Pal.setColor(QPalette::WindowText, colorPtr->getQColor(3));
    this->setPalette(Pal);


    // Timers
    timer = new QTimer(this);
    btimer = new QTimer(this);

    // Set Game Mode Flags
    stdModeFlag = 0;
    endlessModeFlag = 0;
    survivalModeFlag = 0;

    // Set Labels
    grid->addWidget(new QLabel("Bombs:"),1,0);
    grid->addWidget(new QLabel("Score:"),0,0);
    timeLabel = new QLabel("Time:", this);
    grid->addWidget(timeLabel, 7, 0);

    // Add score board
    sframe = new ScoreFrame();
    sframe->text->setFixedWidth(blockSize*5);
    sframe->text->setFixedHeight(blockSize );
    grid->addWidget(sframe->text,0,1,1,1,Qt::AlignLeft);

    // Menu Button
    menuButton = new QPushButton("||",this);
    //menuButton->setFixedSize(blockSize * 1.25 ,blockSize * 1.25);
    connect(menuButton, SIGNAL(clicked()),this, SLOT(pausedPressed()));
    //menuButton->setGeometry((bombBar->x() + (blockSize*7) ), 0, blockSize, blockSize);
    //grid->addWidget(menuButton,1,2, Qt::AlignLeft);
    menuButton->setGeometry((0 + (blockSize)*6 ), screenSizeY - (blockSize)*1.6, blockSize*2, blockSize);
    menuButton->hide();

    // Shuffle Button

    //shuffleButton = new QPushButton("S",this);
    shuffleButton = new QPushButton(QString::fromUtf8("\u25A6"),this);
    shuffleButton->setGeometry((0 + (blockSize)*4 ), screenSizeY - (blockSize)*1.6, blockSize*2, blockSize);
    connect(shuffleButton, SIGNAL(clicked()),this, SLOT(shufflePressed()));
    shuffleButton->hide();

    // Geometry Buttons

    //verticalFlipButton = new QPushButton("Vflip",this);
    //verticalFlipButton = new QPushButton(QString::fromUtf8("\u2194"),this);
    verticalFlipButton = new QPushButton(QString::fromUtf8("\u21C4"),this);
    verticalFlipButton->setPalette(Pal);
    verticalFlipButton->setGeometry((0 + (blockSize)*0 ), screenSizeY - (blockSize)*1.6, blockSize*2, blockSize);
    connect(verticalFlipButton, SIGNAL(clicked()),this, SLOT(verticalFlip()));
    verticalFlipButton->hide();


    //horizontalFlipButton = new QPushButton("Hflip",this);
    //horizontalFlipButton = new QPushButton(QString::fromUtf8("\u2195"),this);
    horizontalFlipButton = new QPushButton(QString::fromUtf8("\u21C5"),this);
    horizontalFlipButton->setGeometry((0 + (blockSize)*2 ), screenSizeY - (blockSize)*1.6, blockSize*2, blockSize);
    connect(horizontalFlipButton, SIGNAL(clicked()),this, SLOT(horizontalFlip()));
    horizontalFlipButton->hide();


    // Block Viewing Area
    theScene = new QGraphicsScene();
    theScene->setSceneRect(0, 0, screenSizeX-4, (blockSize * boardSizeY)-4);
    blockView = new QGraphicsView(theScene);
    blockView->setFixedSize(screenSizeX, blockSize * boardSizeY);
    grid->addWidget(blockView,2,0,5,-1, Qt::AlignLeft);
    blockView->show();

    // Time Progress Bar

    start = false;

    Timeclock = new QLabel();
    Timefill = new QLabel();

    Timeclock->setGeometry(0,0,300,25);
    Timefill->setGeometry(0,0,300,25);

    QPixmap newMap(Timeclock->width(), Timeclock->height());
    //newMap.fill(Qt::magenta);
    newMap.fill(QColor(250,250,250,255));
    Timeclock->setPixmap(newMap);
    //newMap.fill(Qt::green);
    newMap.fill(colorPtr->getQColor(1));
    Timefill->setPixmap(newMap);
    grid->addWidget(Timeclock,7,1);
    grid->addWidget(Timefill,7,1);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeSlot()));

    // Bomb Progress Bar

    bombLayer = new QLabel();
    bombFill = new QLabel();

    bombLayer->setGeometry(0,0,300,25);
    bombFill->setGeometry(0,0,300,25);
    QPixmap bombColor(bombLayer->width(), bombLayer->height());
    //bombColor.fill(Qt::white);
    bombColor.fill(QColor(250,250,250,255));
    bombLayer->setPixmap(bombColor);
    //bombColor.fill(Qt::gray);
    bombColor.fill(colorPtr->getQColor(1));
    bombFill->setPixmap(bombColor);
    grid->addWidget(bombLayer,1,1);
    grid->addWidget(bombFill,1,1);
    bombLayer->setMaximumWidth(bombLayer->width());
    connect(btimer, SIGNAL(timeout()), this, SLOT(bombtimeSlot()));


} // End setupInterface()

/*********************************************************************
  void setupBlocks():
    This method instantiates a two dimentional array of the custom
    QGraphicsRectItem class myRectItem
 *********************************************************************/
void MainWindow::setupBlocks(){
	int temp;
    for(int y = 0; y < boardSizeY; y++){
        for(int x = 0; x < boardSizeX; x++){
			//Dan Block Updates:
            temp = (rand() % 6) + 1;
			gameBoard[x][y] = new Block(x, y, temp); 
			//End of my loop stuff
			//now would use temp as accessor in color class to send color to rectItem Bruch
            rectArray[x][y] = new myRectItem();
            rectArray[x][y]->setRect(blockSize * x, blockSize * y, blockSize, blockSize);
            rectArray[x][y]->setBrush(QBrush(colorPtr->getQColor(temp), Qt::SolidPattern));
            theScene->addItem(rectArray[x][y]);
        }
    }

    for(int i = 0; i < boardSizeY; i++)
    {
        for(int j = 0; j < boardSizeX; j++)
        {
            if(i != 0)
                gameBoard[j][i]->assignUp(gameBoard[j][i - 1]);
            if(i != (boardSizeY - 1))
                gameBoard[j][i]->assignDown(gameBoard[j][i + 1]);
            if(j != 0)
                gameBoard[j][i]->assignLeft(gameBoard[j - 1][i]);
            if(j != (boardSizeX - 1))
                gameBoard[j][i]->assignRight(gameBoard[j + 1][i]);
        }
    }

} // End setupBlocks()

/************************************************************
 * mousePressEvent(QMouseEvent):
 *  This method handles the mouse event that is generated
 *  when the player selects a block. The mouseEvent is
 *  generated by the RectItems and is accepted by this
 *  method. It gets the (x,y) cords of the click in relation
 *  to the screen as a whole and we compute which block was
 *  clicked based on this information. Then the necessary
 *  functions to collect and process the matches takes place.
 *************************************************************/
void MainWindow::mousePressEvent(QMouseEvent *event){
    if(!pauseMenu->isVisible()){    // Only allow clicks when not paused

        QPoint point = blockView->pos();

        if( event->y() > point.y() &&
                event->y() <= point.y()+blockView->height() )
        {
            xPos = event->x() / blockSize;
            yPos = (event->y() - point.y()) / blockSize;

            // *Tried to put following code in blockPressed, but it was already included somewhere else.
            //*Code can be moved as needed as long as it is in mainwindow_UI.cpp
            Block* tempCheck = gameBoard[xPos][yPos];
            if(tempCheck->foundMatch())
                processMatch(tempCheck);
        }
    }
} // End MousePressEvent



void MainWindow::updateBomb(int nBlocks){

    int updateVal;
//    updateVal = (nBlocks-1)*(nBlocks-1);
    updateVal = nBlocks * 8;

    if ((bombFill->maximumWidth()+updateVal) < bombLayer->maximumWidth()){
        bombFill->setMaximumWidth(bombFill->maximumWidth()+updateVal);
        if (bombFill->maximumWidth() > 0){
            bcurrentTime += (updateVal/2);
            btimeBegin();
        }
    }
    else if ((bombFill->maximumWidth()+updateVal) >= bombLayer->maximumWidth()){
             bombFill->setMaximumWidth(0);
             btimeOver();
             bcurrentTime=0;
    }

}


/************************************
 *  The Slots that the buttons use. *
 ************************************/
void MainWindow::menuPressed(){

    // Quit Game and go back to Main Menu
    reset();
    scorePtr->resetScore();
    sframe->resetScoreBoard();
    shuffleButton->hide();
    verticalFlipButton->hide();
    horizontalFlipButton->hide();
    menuButton->hide();
    timeLabel->hide();
    pauseMenu->hide();
    mainMenu->show();

}

void MainWindow::pauseBack(){
    pauseMenu->hide();
    timeBegin();
    if(bcurrentTime!=0)
        btimeBegin();
}

void MainWindow::pausedPressed(){
    pauseMenu->show();
    timeOver();
    btimeOver();
}

void MainWindow::pauseSettingsPressed(){
    pauseMenu->hide();
    shuffleButton->hide();
    verticalFlipButton->hide();
    horizontalFlipButton->hide();
    menuButton->hide();
    settingsMenu->show();
    disconnect(backToMenu2, SIGNAL(clicked()), this, SLOT(backToMain()) );
    connect(backToMenu2, SIGNAL(clicked()), this, SLOT(backToPause()) );
}

void MainWindow::backToPause(){
    settingsMenu->hide();
    mainMenu->hide();
    shuffleButton->show();
    horizontalFlipButton->show();
    verticalFlipButton->show();
    menuButton->show();
    pauseMenu->show();
    disconnect(backToMenu2, SIGNAL(clicked()), this, SLOT(backToPause()) );
    connect(backToMenu2, SIGNAL(clicked()), this, SLOT(backToMain()) );
}

void MainWindow::newGamePressed(){
    mainMenu->hide();
    gameModeMenu->show();
}

void MainWindow::settingsPressed(){
    mainMenu->hide();
    settingsMenu->show();
}

void MainWindow::helpPressed(){
    mainMenu->hide();
    helpMenu->show();
}

void MainWindow::backToMain(){

    if(gameModeMenu->isVisible())
        gameModeMenu->hide();

    else if(settingsMenu->isVisible())
        settingsMenu->hide();

    else if(helpMenu->isVisible())
        helpMenu->hide();

    mainMenu->show();
}

void MainWindow::gameOverMenuSlot(){
    gameOverMenu->hide();
    shuffleButton->hide();
    verticalFlipButton->hide();
    horizontalFlipButton->hide();
    menuButton->hide();
    mainMenu->show();
}

void MainWindow::gameOverRestartSlot(){
    gameOverMenu->hide();

    if(stdModeFlag == 1){
        standardMode();
    }
    else if(endlessModeFlag == 1){
        endlessMode();
    }
    else if(survivalModeFlag == 1){
        survivalMode();
    }
}

void MainWindow::noSound(){

    if(soundCheck->isChecked()){
        soundCheck->setCheckState(Qt::Unchecked);
        soundCheck->setChecked(false);
        // Kill sound
    }

    else if(!soundCheck->isChecked()){
        soundCheck->setCheckState(Qt::Checked);
        soundCheck->setChecked(true);
        // Allow sound
    }

}

void MainWindow::screenLock(){
    if(screenLockCheck->isChecked()){
        screenLockCheck->setChecked(false);
        // no flipping
    }
   else if(!screenLockCheck->isChecked()){
        screenLockCheck->setChecked(true);
        // Allow flipping
    }
}

void MainWindow::changeColorScheme(){
    // change color scheme based on slider value
}

void MainWindow::standardMode(){
    gameModeMenu->hide();
    shuffleButton->show();
    verticalFlipButton->show();
    horizontalFlipButton->show();
    menuButton->show();
    timeLabel->show();
    Timefill->show();
    Timeclock->show();
    scorePtr->resetScore();
    sframe->resetScoreBoard();


    stdModeFlag = 1;
    endlessModeFlag = 0;
    survivalModeFlag = 0;

    startGame();
}

void MainWindow::survivalMode(){
    gameModeMenu->hide();
    shuffleButton->show();
    verticalFlipButton->show();
    horizontalFlipButton->show();
    menuButton->show();
    timeLabel->show();
    Timefill->show();
    Timeclock->show();
    scorePtr->resetScore();
    sframe->resetScoreBoard();

    stdModeFlag = 0;
    endlessModeFlag = 0;
    survivalModeFlag = 1;

    startGame();
}

void MainWindow::endlessMode(){
    gameModeMenu->hide();
    shuffleButton->show();
    verticalFlipButton->show();
    horizontalFlipButton->show();
    menuButton->show();
    timeLabel->hide();
    Timeclock->hide();
    Timefill->hide();
    scorePtr->resetScore();
    sframe->resetScoreBoard();

    stdModeFlag = 0;
    endlessModeFlag = 1;
    survivalModeFlag = 0;

    startGame();
}

void MainWindow::shufflePressed() {
    // Only shuffles if not paused
    if(!pauseMenu->isVisible()){

        // perform Nswaps swaps, passing colors/bombs/multipliers
        int Nswaps, i;
        Nswaps=(boardSizeX*boardSizeY)*(boardSizeX*boardSizeY);

        for (i=0; i<Nswaps; i++) {
            int r1, c1, r2, c2, tempColor;
            r1=rand()%boardSizeX;
            r2=rand()%boardSizeX;
            c1=rand()%boardSizeY;
            c2=rand()%boardSizeY;

            tempColor = gameBoard[r1][c1]->getColor();
            //now uses QColor with setColor function
            gameBoard[r1][c1]->setColor( gameBoard[r2][c2]->getColor() );
            gameBoard[r2][c2]->setColor(tempColor);

            rectArray[gameBoard[r1][c1]->getCoordX()][gameBoard[r1][c1]->getCoordY()]->setBrush(QBrush(colorPtr->getQColor(gameBoard[r1][c1]->getColor()), Qt::SolidPattern));
            rectArray[gameBoard[r2][c2]->getCoordX()][gameBoard[r2][c2]->getCoordY()]->setBrush(QBrush(colorPtr->getQColor(gameBoard[r2][c2]->getColor()), Qt::SolidPattern));
            // TO DO: need to swap bombs/multipler -> add getBomb method to Block
            /*
             *At this point, graph objects need to be swapped between rect items
             *tempGraphObject = rectArray[gameBoard[r1][c1]->getCoordX()][gameBoard[r1][c1]->getCoordY()]->myGraphObject;
             *rectArray[gameBoard[r1][c1]->getCoordX()][gameBoard[r1][c1]->getCoordY()]->myGraphObject = rectArray[gameBoard[r2][c2]->getCoordX()][gameBoard[r2][c2]->getCoordY()]->myGraphObject;
             *rectArray[gameBoard[r2][c2]->getCoordX()][gameBoard[r2][c2]->getCoordY()->myGraphObject = tempGraphObject;
             *
             *The graph objects were just swapped but they still contain the previous coordinates
             *rectArray[gameBoard[r1][c1]->getCoordX()][gameBoard[r1][c1]->getCoordY()]->myGraphObject->moved(gameBoard[r2][c2]->getCoordX(), gameBoard[r2][c2]->getCoordY());
             *rectArray[gameBoard[r2][c2]->getCoordX()][gameBoard[r2][c2]->getCoordY()]->myGraphObject->moved(gameBoard[r1][c1]->getCoordX(), gameBoard[r1][c1]->getCoordY());
             *
             *May need to force another painting of these graph objects, but data structure continuity is maintained at this point
             */
        }

    }
}

void MainWindow::quit(){
    close();
}

// End Slots

void MainWindow::horizontalFlip() {
    // Only flips if not paused
    if(!pauseMenu->isVisible()){

        int x, y;

        for (x=0; x<boardSizeX; x++) {
            for (y=0; y<boardSizeY/2; y++) {
                int x1, y1, x2, y2, tempColor;
                x1=x;
                x2=x;
                y1=y;
                y2=boardSizeY-1-y;

                tempColor = gameBoard[x1][y1]->getColor();
                gameBoard[x1][y1]->setColor( gameBoard[x2][y2]->getColor() );
                gameBoard[x2][y2]->setColor(tempColor);

                rectArray[gameBoard[x1][y1]->getCoordX()][gameBoard[x1][y1]->getCoordY()]->setBrush(QBrush(colorPtr->getQColor(gameBoard[x1][y1]->getColor()), Qt::SolidPattern));
                rectArray[gameBoard[x2][y2]->getCoordX()][gameBoard[x2][y2]->getCoordY()]->setBrush(QBrush(colorPtr->getQColor(gameBoard[x2][y2]->getColor()), Qt::SolidPattern));
                // TO DO: need to swap bombs/multipler -> add getBomb method to Block
                //Swapping follows similar process commented in shuffle
            }
        }

    }
}

void MainWindow::verticalFlip() {

    // Only flips if not paused
    if(!pauseMenu->isVisible()){

        int x, y;

        for (x=0; x<boardSizeX/2; x++) {
            for (y=0; y<boardSizeY; y++) {
                int x1, y1, x2, y2, tempColor;
                x1=x;
                x2=boardSizeX-1-x;
                y1=y;
                y2=y;

                tempColor = gameBoard[x1][y1]->getColor();
                gameBoard[x1][y1]->setColor( gameBoard[x2][y2]->getColor() );
                gameBoard[x2][y2]->setColor(tempColor);

                rectArray[gameBoard[x1][y1]->getCoordX()][gameBoard[x1][y1]->getCoordY()]->setBrush(QBrush(colorPtr->getQColor(gameBoard[x1][y1]->getColor()), Qt::SolidPattern));
                rectArray[gameBoard[x2][y2]->getCoordX()][gameBoard[x2][y2]->getCoordY()]->setBrush(QBrush(colorPtr->getQColor(gameBoard[x2][y2]->getColor()), Qt::SolidPattern));
                // TO DO: need to swap bombs/multipler -> add getBomb method to Block
                //Swapping follows similar process commented in shuffle
            }
        }
    }
}

/**
  * Reset the colors of all blocks
  *
  *DKeasler:
  *tempColor to get random number first, then uses QColor with setColor
  */
void MainWindow::reset() {
    int r, c;
    for (r=0; r<boardSizeX; r++) {
        for (c=0; c<boardSizeY; c++) {
            int tempColor;
            tempColor = (rand() % 6) + 1;
            gameBoard[r][c]->setColor(tempColor);
        }
    }
}




/*
Start of Block game algorithm functions:
*/

void MainWindow::processMatch(Block* matchedBlock)
{
    // SHupdate - rearranged by Dan for order
    vector<Block*> gatheredBlocks;
    gatheredBlocks = matchedBlock->gatherBlocks(gatheredBlocks);
	//NIY; will test when graphical images are loaded on top
	//gatheredBlocks = checkSpecials(gatheredBlocks); 
    gatheredBlocks = sortVector(gatheredBlocks);

    //transition period right here, after all blocks have been turned black

   multiplier = 1;

    scorePtr->updateScore((int) gatheredBlocks.size(), false , multiplier);
    sframe->update(scorePtr->getScore());
    updateBomb((int) gatheredBlocks.size());
    determineColor(gatheredBlocks);
}

/*
 *Author: Daniel Keasler
 *      Plock Team
 *
 *Outer loop eventually checks every element in the vector. T, initialized to i, is used to keep track
 *  of the maximum (max index, lowest push button on widget) so that if no block is a max over t, then
 *  there won't be a switch. Because j goes to the end of the vector in each inner loop, any Block
 *  swapping will be the max and the next nested iteration can skip that Block for order assuring. For
 *  a swap, both blocks must be in the same row and the ColY must be higher, meaning further down in
 *  the widget representation as well as the the array structure.
 *
 *  Late add: markedBool and setColor(black or 0) are called here as a logical place to process these
 *  intermediate changes in the blocks.
 *
 *  CHANGED: setColor now includes QColor parameter - NOW REMOVED
 *
 *  NOTE: May be unnecessary. determineColor can be extended extra overlaps, and only consideration
 *  overlapping is transitions.
 */

vector<Block*> MainWindow::sortVector(vector<Block*> blockVector)
{
    for(int i = 0; (unsigned)i < blockVector.size(); i++)
    {
        int t = i;
        for(int j = i + 1; (unsigned)j < blockVector.size(); j++)
        {
            if(blockVector[j]->getCoordX() == blockVector[t]->getCoordX() && blockVector[j]->getCoordY() > blockVector[t]->getCoordY())
                t = j;
        }
        if(t != i)
        {
            Block *tempPtr = blockVector[i];
            blockVector[i] = blockVector[t];
            blockVector[t] = tempPtr;
        } 
		//This line may not be needed in general transntions
        blockVector[i]->setColor(0);
        blockVector[i]->setMarkedBool(false);
        rectArray[blockVector[i]->getCoordX()][blockVector[i]->getCoordY()]->setBrush(QBrush(colorPtr->getQColor(0), Qt::SolidPattern));
    }
    return blockVector;
}

/*
 *Author: Daniel Keasler
 *      Plock Team
 *
 *Gives each Block in the vector the proper color. Because color drops
 *  from top to bottom (high indices to low indices), the first proper
 *  color is chosen from the adjacent Block up from the current ith
 *  Block. CheckY, along with the ith Block's RowX, is used to find the
 *  next appropriate color above in the correct column. The only other
 *  factor for the same color in the 2D array is that the color it could
 *  be inheriting is not already scheduled for a color change, which is
 *  what the coloredBool value is for. If the condition for "inheriting"
 *  another color is met, then the Block inheriting the color is sent
 *  the new color and the coloredBool value is set to false (no longer
 *  needs a color change) and the Block that lost the color now also
 *  needs a color change. The color of this available block is set to
 *  Black for a noticeable transition, the coloredBool value is set to
 *  true because the Block needs a color change and its color should not
 *  be taken, and it is added to the end of the blockVector. In the case
 *  of no matches in a column with the ith block, a new random color will
 *  be assigned and the appropriate coloredBool flag is set to false.
 *
 *  CHANGED: setColor now includes QColor - NOW REMOVED
 */

void MainWindow::determineColor(vector<Block*> blockVector)
{
    for(int i = 0; (unsigned)i < blockVector.size(); i++)
    {
        int checkY = blockVector[i]->getCoordY() - 1;
        while(checkY >= 0)
        {
            if(!gameBoard[blockVector[i]->getCoordX()][checkY]->getColoredBool())
            {
				//steal the color from other block onto ith block...
                blockVector[i]->setColor(gameBoard[blockVector[i]->getCoordX()][checkY]->getColor());
                blockVector[i]->setColoredBool(false);
                rectArray[blockVector[i]->getCoordX()][blockVector[i]->getCoordY()]->setBrush(QBrush(colorPtr->getQColor(blockVector[i]->getColor()), Qt::SolidPattern));
				//..and set the other block for a color change (including transition)
                gameBoard[blockVector[i]->getCoordX()][checkY]->setColoredBool(true); //block needs to be changed later
                gameBoard[blockVector[i]->getCoordX()][checkY]->setColor(0);
                rectArray[blockVector[i]->getCoordX()][checkY]->setBrush(QBrush(colorPtr->getQColor(0),Qt::SolidPattern));
                blockVector.push_back(gameBoard[blockVector[i]->getCoordX()][checkY]); //add block to end of vector
                break;
            }
            else
                checkY--;
        }
        if(checkY < 0)
        {
            int tempColor;
            tempColor = (rand() % 6) + 1;
            blockVector[i]->setColor(tempColor); 
            blockVector[i]->setColoredBool(false);
            rectArray[blockVector[i]->getCoordX()][blockVector[i]->getCoordY()]->setBrush(QBrush(colorPtr->getQColor(tempColor), Qt::SolidPattern));
        }
    }
}

/*
 *Author: Daniel Keasler
 *      Plock Team
 *
 *Outer for loop scans every block in blockVector. If statement checks
 *  for 0 first to avoid redundancy of case 0 : break; and overwriting 0
 *  with 0. Relavant cases call for mapped collector methods, assignment
 *  back to blockVector. One statement for all 5 cases to setGraphImage
 *  (and the graphical image itself) to 0 at end. Return blockVector to
 *  processMatches.
 */
 
vector<Block*> MainWindow::checkSpecials(vector<Block*> blockVector)
{
    for(int i = 0; (unsigned)i < blockVector.size(); i++)
    {
        if(blockVector[i]->getGraphImage() != 0)
        {
            switch(blockVector[i]->getGraphImage()){

            case 1 : //score case
                //score mult is updated first
                //vector swap and erase of this scoring object
                //changeIndex called for swapped graph objects
                break;
            case 2 : //bomb case
                blockVector = bombCollector(blockVector, blockVector[i]->getCoordX(), blockVector[i]->getCoordY());
                break;
            case 3 : //vertical case
                blockVector = blockVector[i]->upCollector(blockVector);
                blockVector = blockVector[i]->downCollector(blockVector);
                break;
            case 4 : //horizontal case
                blockVector = blockVector[i]->rightCollector(blockVector);
                blockVector = blockVector[i]->leftCollector(blockVector);
                break;
            case 5 : //4 arrows case
                blockVector = blockVector[i]->upCollector(blockVector);
                blockVector = blockVector[i]->downCollector(blockVector);
                blockVector = blockVector[i]->rightCollector(blockVector);
                blockVector = blockVector[i]->leftCollector(blockVector);
                break;
            }
            blockVector[i]->setGraphImage(0);
            //zero pointer in myRectItem->myGraphObject
            //clear image from myRectItem
        }
    }
    return blockVector;
}

/*
 *Author: Daniel Keasler
 *      Plock Team
 *
 *Outer for loop goes from x - 1 to x + 1, bounds checking prevents errors.
 *  Inner loop goes from y - 1 to y + 1, bounds checking prevents errors.
 *  if block hasn't been marked yet, same process to add block and change
 *  boolean values. Return block back to checkSpecials.
 */
vector<Block*> MainWindow::bombCollector(vector<Block*> blockVector, int x, int y)
{
    for(int i = (x - 1); i < (x + 2); i++)
    {
        if(i > boardSizeX) //needs to be changed for 7x9
            break;
        if(i < 0)
            continue;
        for(int j = (y - 1); j < (y + 2); j++)
        {
            if(j > boardSizeY || j < 0) //needs to be changed for 7x9
                continue;
            if(!gameBoard[i][j]->getMarkedBool())
            {
                gameBoard[i][j]->setColoredBool(true);
                gameBoard[i][j]->setMarkedBool(true);
                blockVector.push_back(gameBoard[i][j]);
            }
        }
    }
    return blockVector;
}

//END Dan Block Functions


void MainWindow::bombtimeSlot(){
y++;
if(y%3==0){
    bcurrentTime--;
}
if(bcurrentTime==-1){
    btimeOver();
    return;
}
bombFill->setMaximumWidth(bombFill->maximumWidth()-(bombLayer->width()/120));
}



void MainWindow::timeSlot(){
    x++;
    if(x%5==0){
        currentTime--;
    }
    if(currentTime==-1){
        tempScore->setText(QString::number(scorePtr->getScore()));
        gameOverMenu->show();
        timeOver();
        btimeOver();
        //close();
        //return;
    }
    Timefill->setMaximumWidth(Timefill->maximumWidth()-(Timeclock->width()/300));
}


void MainWindow::btimeOver(){
    btimer->stop();
}

void MainWindow::btimeBegin(){
    btimer->start();
}

void MainWindow::timeOver(){
    timer->stop();
}
void MainWindow::timeBegin(){
    timer->start();
}

/*
 *This function is called in each game mode. First, the old
 *pointer references are nulled. Then setupBlocks is called
 *to generate a new board. All of our game modes include a
 *bomb, so the bomb timer code is used to set it up. If not
 *in endless mode, the timer code is used to set the timer
 *up.
 *
 *NYI: score reset.
 */
void MainWindow::startGame(){

    for(int i = 0; i < boardSizeX; i++){
        for(int j = 0; j < boardSizeY; j++){
            gameBoard[i][j] = 0;
            rectArray[i][j] = 0;
        }
    }
    setupBlocks();
    bombFill->setMaximumWidth(0);
    bcurrentTime=0;
    btimer->start(333.333);
    if(endlessModeFlag != 1){
        Timefill->setMaximumWidth(Timeclock->width());
        currentTime=60;
        timer->start(200);
    }
}

void MainWindow::processSurvival(){
    //this function would be called from the updateProgressTime function
    //increment level counter (would need to have started at 1 for each survival call)
    //group box with level x incoming, etc
    shufflePressed();//shuffles blocks / graph objects
    //timer stopped here or in updateProgressTime function
    //increment timer speed, maybe formula from level counter
    //set timer to 50%
    //start timer with new incremented timer speed
}


// End mainwindow_UI.cpp
