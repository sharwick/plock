/** @author Shannon Harwick
 *  @author Daniel Keasler
 *  @author Devin Rusnak
 *  @author Mikael Son
 *  @copyright Blockstar 2012
 *  @class mainwindow_UI mainwindow_UI.h "mainwindow_UI.h"
 *  @extends QMainWindow
 *  @brief The main class of the program where all the interface items and most of the calculations are handled.
 *
 *  Some lengthy discription
 *
 */

#include "mainwindow_UI.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QCoreApplication>

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Call our setup methods
    setupWindows();
    setupGameScreen();
}

/**
 * @brief MainWindow::~MainWindow
 */
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


/**
 *  @brief MainWindow::setupWindows
 *
 *  This method sets the size of the mainWindow based on the size of
 *  the phone screen. It also uses these parameters to determine the
 *  size the game blocks should be to fit evenly on the board.
 *  The central widget acts as the base widget. The game board is
 *  placed onto this widget and all accompaning items. The centralWidget
 *  is also the parent of the menu Widgets so they simply appear over
 *  the game board which is always there but not always visable or
 *  interactable. The other windows for the menus and their items
 *  and initialized here.
 *
 */
void MainWindow::setupWindows(){

    start = false;//necessary to avoid segfault in startGame function
    gamedone = false; ///necessary to avoid asking to quit again when the game is done.
    timerCounter = 200; //timer for survival and hot potato
    gCount=4;
    gtimer = new QTimer(this);
    connect(gtimer, SIGNAL(timeout()), this, SLOT(gtimeSlot()));
    gtimer->start(1000);
    gtimer->stop();

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
    mainMenuLayout->setSpacing(20);
    mainMenu->setLayout(mainMenuLayout);

    // Initialize and add items to layout
    tempFont = QFont();
    tempFont.setPointSize(blockSize/6);
    tempFont.setBold(true);
    titleLabel = new QLabel("B O M B S T A R"); labelVector.push_back(titleLabel);
    titleLabel->setFixedSize(blockSize*4.25, blockSize*2);
    titleLabel->setFont(tempFont);
    mainMenuLayout->addWidget(titleLabel, Qt::AlignHCenter);

    newGameButton = new QPushButton(this); buttonVector.push_back(newGameButton);
    newGameButton->setText("New Game");
    newGameButton->setFixedSize(blockSize*4, blockSize);
    connect( newGameButton, SIGNAL(clicked()), this, SLOT(newGamePressed()) );
    mainMenuLayout->addWidget(newGameButton, Qt::AlignTop);

    highScoreButton = new QPushButton("High Scores", this); buttonVector.push_back(highScoreButton);
    highScoreButton->setFixedSize(blockSize*4, blockSize);
    connect( highScoreButton, SIGNAL(clicked()), this, SLOT(highScoresShow()) );
    mainMenuLayout->addWidget(highScoreButton, Qt::AlignTop);

    settingsButton = new QPushButton("Settings", this); buttonVector.push_back(settingsButton);
    settingsButton->setFixedSize(blockSize*4, blockSize);
    connect( settingsButton, SIGNAL(clicked()), this, SLOT(settingsPressed()) );
    mainMenuLayout->addWidget(settingsButton, Qt::AlignTop);

    helpButton = new QPushButton("About", this);buttonVector.push_back(helpButton);
    helpButton->setFixedSize(blockSize*4, blockSize);
    connect( helpButton, SIGNAL(clicked()), this, SLOT(helpPressed()) );
    mainMenuLayout->addWidget(helpButton, Qt::AlignTop);

    quitButton = new QPushButton("Quit", this); buttonVector.push_back(quitButton);
    quitButton->setFixedSize(blockSize*4, blockSize);
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
    gameModeTitle = new QLabel("Choose A Game Mode"); labelVector.push_back(gameModeTitle);
    modeMenuLayout->addWidget(gameModeTitle, 0, 1,  Qt::AlignTop);

    standardModeButton = new QPushButton("Standard Mode", this); buttonVector.push_back(standardModeButton);
    connect(standardModeButton, SIGNAL(clicked()), this, SLOT(standardMode()) );
    modeMenuLayout->addWidget(standardModeButton, 2, 1, Qt::AlignTop);

    survivalModeButton = new QPushButton("Survival Mode", this); buttonVector.push_back(survivalModeButton);
    connect(survivalModeButton, SIGNAL(clicked()), this, SLOT(survivalMode()) );
    modeMenuLayout->addWidget(survivalModeButton, 3, 1, Qt::AlignTop);

    endlessModeButton = new QPushButton("Endless Mode", this); buttonVector.push_back(endlessModeButton);
    connect(endlessModeButton, SIGNAL(clicked()), this, SLOT(endlessMode()) );
    modeMenuLayout->addWidget(endlessModeButton, 4, 1, Qt::AlignTop);

    backToMenu = new QPushButton("Back", this); buttonVector.push_back(backToMenu);
    connect(backToMenu, SIGNAL(clicked()), this, SLOT(backToMain()) );
    modeMenuLayout->addWidget(backToMenu, 6, 1, Qt::AlignTop);



    /* * * * * * * * * * * * * * * * * *
     * Setup Start Menu and its items  *
     * * * * * * * * * * * * * * * * * */
    // Initalize Widget
    startScreen = new QGroupBox(this);
    startScreen->setAutoFillBackground(true);
    startScreen->setGeometry(0, screenSizeY * 0.82, screenSizeX, screenSizeY);
    // Create Layout
    startLayout = new QVBoxLayout(this);
    startLayout->setAlignment(Qt::AlignTop);
    startLayout->setSpacing(0);
    startScreen->setLayout(startLayout);
    pressScreenLabel = new QLabel("Double tap board to begin!", this); labelVector.push_back(pressScreenLabel);
    pressScreenLabel->setFont(tempFont);
    startLayout->addWidget(pressScreenLabel);
    startScreen->hide();



    /* * * * * * * * * * * * * * * * * * * *
     * Setup High Score Menu and its items *
     * * * * * * * * * * * * * * * * * * * */
    theHighScores = new HighScores();

    // Initalize Widget
    highScoreMenu = new QGroupBox(this);
    highScoreMenu->setFixedSize(screenSizeX, screenSizeY);
    highScoreMenu->setAutoFillBackground(true);
    highScoreMenu->hide();

    // Create the Menu's layout
    highScoreLayout = new QGridLayout(this);
    highScoreLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    highScoreLayout->setSpacing(10);
    highScoreMenu->setLayout(highScoreLayout);

    // Initalize and add Items to layout
    highScoresLabel = new QLabel("HIGH SCORES"); labelVector.push_back(highScoresLabel);
    highScoresLabel->setFixedSize(blockSize * 4, blockSize);
    highScoresLabel->setFont(tempFont);
    highScoreLayout->addWidget(highScoresLabel, 0, 0, Qt::AlignLeft);

    standardLabel = new QLabel("Standard", this); labelVector.push_back(standardLabel);
    highScoreLayout->addWidget(standardLabel, 1, 0, Qt::AlignLeft);
    survivalLabel = new QLabel("Survival", this); labelVector.push_back(survivalLabel);
    highScoreLayout->addWidget(survivalLabel, 7, 0, Qt::AlignLeft);
    endlessLabel = new QLabel("Endless", this); labelVector.push_back(endlessLabel);
    highScoreLayout->addWidget(endlessLabel, 13, 0, Qt::AlignLeft);

    for(int index = 0; index < 5; index++){
        labelVector.push_back(theHighScores->getLabel(QString("standard"), index));
        highScoreLayout->addWidget(theHighScores->getLabel(QString("standard"), index), index+2, 0, Qt::AlignLeft);

        labelVector.push_back(theHighScores->getLabel(QString("survival"), index));
        highScoreLayout->addWidget(theHighScores->getLabel(QString("survival"), index), index+8, 0, Qt::AlignLeft);

        labelVector.push_back(theHighScores->getLabel(QString("endless"), index));
        highScoreLayout->addWidget(theHighScores->getLabel(QString("endless"), index), index+14, 0, Qt::AlignLeft);
    }

    backToMenu4 = new QPushButton("Menu", this); buttonVector.push_back(backToMenu4);
    backToMenu4->setFixedSize(blockSize * 2, blockSize);
    connect(backToMenu4, SIGNAL(clicked()), this, SLOT(backToMain()) );
    highScoreLayout->addWidget(backToMenu4, 0, 1, Qt::AlignRight);


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
    settingsLayout->setSpacing(30);
    settingsMenu->setLayout(settingsLayout);

    // Initalize and add Items to the layout
    settingsTitle = new QLabel("Settings"); labelVector.push_back(settingsTitle);
    settingsTitle->setFont(tempFont);
    settingsLayout->addWidget(settingsTitle, 0, 1);

    backToMenu2 = new QPushButton("Back", this); buttonVector.push_back(backToMenu2);
    backToMenu2->setFixedSize(blockSize * 3, blockSize);
    connect(backToMenu2, SIGNAL(clicked()), this, SLOT(backToMain()) );
    settingsLayout->addWidget(backToMenu2, 6, 1, Qt::AlignBottom);

    colorSlider = new QSlider(Qt::Horizontal ,this);
    colorSlider->setRange(0,4);
    colorSlider->setStyleSheet("QSlider {background: black}");
    colorSchemeLabel=new QLabel("Color Scheme:"); labelVector.push_back(colorSchemeLabel);
    settingsLayout->addWidget(colorSchemeLabel, 3, 0, Qt::AlignLeft);
    settingsLayout->addWidget(colorSlider, 3, 1);
    connect(colorSlider, SIGNAL(valueChanged(int)), this, SLOT(changeColorScheme()));


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
    aboutLabel = new QLabel("About Blockstar", this); labelVector.push_back(aboutLabel);
    aboutLabel->setFont(tempFont);
    helpMenuLayout->addWidget(aboutLabel, Qt::AlignHCenter);

    helpText = new QTextBrowser(this);
    helpText->setFixedSize(screenSizeX * 0.9, screenSizeY * 0.75);
    QPalette helpPal = helpText->palette();
    helpPal.setColor(QPalette::Base, QColor(0, 0, 0));
    helpText->setPalette(helpPal);
    aboutText = QString("An android game based on Plock. \n"
                        "UIC CS 340 Fall 2012 \n"
                        "Authors: Shannon Harwick, Daniel Keasler, Devin Rusnak, Mike Son. \n"
                        "\n"
                        "How to Play: \n"
                        "The goal of the game is to match similar colored blocks. "
                        "As the blocks are cleared new blocks fill in from the top of the board. "
                        "As you score points, your bomb bar grows and when it is full a random "
                        "bomb is placed on the board in the form of a star. When you click on them "
                        "an area around them are cleared out. "
                        "There are three game modes to choose from. First is Standard Mode, which "
                        "is a sixty second game where you have to score as high as possible. "
                        "Next is Survival Mode where you have a certian amount of time to accumulate "
                        "a certian score, which changes with each level. Last there is Endless Mode "
                        " where you have an unlimited amount of time to play.");
    helpText->setText(aboutText);
    helpMenuLayout->addWidget(helpText, Qt::AlignTop);

    backToMenu3 = new QPushButton("Back", this); buttonVector.push_back(backToMenu3);
    backToMenu3->setFixedSize(blockSize * 4, blockSize);
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
    pauseMenuLayout->setAlignment(Qt::AlignHCenter);
    pauseMenuLayout->setSpacing(10);
    pauseMenu->setLayout(pauseMenuLayout);
    pauseMenu->hide();

    // Initialize and add Items to the layout
    pauseLabel = new QLabel("The Game is Paused"); labelVector.push_back(pauseLabel);
    pauseMenuLayout->addWidget(pauseLabel, Qt::AlignHCenter);

    pauseRejected = new QPushButton("Resume", this); buttonVector.push_back(pauseRejected);
    pauseRejected->setFixedSize(blockSize * 3, blockSize);
    pauseMenuLayout->addWidget(pauseRejected, Qt::AlignHCenter);
    connect(pauseRejected, SIGNAL(clicked()), this, SLOT(pauseBack()) );

    pauseHighScore = new QPushButton("High Scores", this); buttonVector.push_back(pauseHighScore);
    pauseHighScore->setFixedSize(blockSize * 3, blockSize);
    pauseMenuLayout->addWidget(pauseHighScore, Qt::AlignHCenter);
    connect(pauseHighScore, SIGNAL(clicked()), this, SLOT(highScoresShow()) );

    pauseSettings = new QPushButton("Settings", this); buttonVector.push_back(pauseSettings);
    pauseSettings->setFixedSize(blockSize * 3, blockSize);
    pauseMenuLayout->addWidget(pauseSettings, Qt::AlignHCenter);
    connect(pauseSettings, SIGNAL(clicked()), this, SLOT(pauseSettingsPressed()) );

    pauseAccept = new QPushButton("Main", this); buttonVector.push_back(pauseAccept);
    pauseAccept->setFixedSize(blockSize * 3, blockSize);
    pauseMenuLayout->addWidget(pauseAccept, Qt::AlignHCenter);
    connect(pauseAccept, SIGNAL(clicked()), this, SLOT(confirmQuit()) );



    /* * * * * * * * * * * * * * * * * * * * *
     * Setup Confirm Exit Menu and its Items *
     * * * * * * * * * * * * * * * * * * * * */
    // Initalize Widget
    confirmMenu = new QGroupBox(this);
    confirmMenu->setAutoFillBackground(true);
    confirmMenu->setGeometry( (screenSizeX/2) - ((screenSizeX * 0.7) / 2), (screenSizeY/2) - ((screenSizeY * 0.2) / 2),
                            screenSizeX * 0.7 , screenSizeY * 0.2 );
    // Create Menu's layout
    confirmLayout = new QGridLayout(this);
    confirmLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    confirmLayout->setSpacing(10);
    confirmMenu->setLayout(confirmLayout);
    confirmMenu->hide();

    // Initialize Items and add them to the layout
    quitLabel = new QLabel("Quit?"); labelVector.push_back(quitLabel);
    quitLabel->setFont(tempFont);
    confirmLayout->addWidget(quitLabel, 0, 1, Qt::AlignHCenter);
    confirmAcceptButton = new QPushButton("Yes", this); buttonVector.push_back(confirmAcceptButton);
    confirmAcceptButton->setFixedSize(blockSize * 1.5, blockSize * 0.8);
    connect(confirmAcceptButton, SIGNAL(clicked()), this, SLOT(menuPressed()) );
    confirmLayout->addWidget(confirmAcceptButton, 2, 0, Qt::AlignHCenter);
    confirmRejectButton = new QPushButton("No", this); buttonVector.push_back(confirmRejectButton);
    confirmRejectButton->setFixedSize(blockSize * 1.5, blockSize * 0.8);
    connect(confirmRejectButton, SIGNAL(clicked()), this, SLOT(quitRejected()) );
    confirmLayout->addWidget(confirmRejectButton, 2, 2, Qt::AlignHCenter);



    /* * * * * * * * * * * * * * * * * * * *
     * Setup Game Over Menu and its Items  *
     * * * * * * * * * * * * * * * * * * * */
    // Initalize Widget
    gameOverMenu = new QGroupBox(this);
    gameOverMenu->setAutoFillBackground(true);
    gameOverMenu->setGeometry( (screenSizeX/2) - ((screenSizeX * 0.8) / 2), (screenSizeY/2) - ((screenSizeY * 0.5) / 2),
                            screenSizeX * 0.8 , screenSizeY * 0.5 );
    // Create Menu's Layout
    gameOverLayout = new QVBoxLayout(this);
    gameOverLayout->setAlignment(Qt::AlignHCenter);
    gameOverLayout->setSpacing(10);
    gameOverMenu->setLayout(gameOverLayout);
    gameOverMenu->hide();

    // Initalize and add Items to the layout
    scorePtr = new Score(); // Moved
    newHighScore = new QLabel("New High Score!");
    tempFont.setPointSize(blockSize/8);
    newHighScore->setFont(tempFont);
    gameOverLayout->addWidget(newHighScore, Qt::AlignHCenter);
    finalScoreLabel = new QLabel("Your Final Score:", this); labelVector.push_back(finalScoreLabel);
    gameOverLayout->addWidget(finalScoreLabel);
    tempScore = new QLabel(this); labelVector.push_back(tempScore);
    tempScore->setAlignment(Qt::AlignHCenter);
    gameOverLayout->addWidget(tempScore, Qt::AlignHCenter);

    finalLevelLabel = new QLabel("Your Final Level:", this); labelVector.push_back(finalLevelLabel);
    gameOverLayout->addWidget(finalLevelLabel);
    tempLevel = new QLabel(this); labelVector.push_back(tempLevel);
    tempLevel->setAlignment(Qt::AlignHCenter);
    gameOverLayout->addWidget(tempLevel, Qt::AlignHCenter);

    if (survivalModeFlag!=1) {
        finalLevelLabel->setText(""); labelVector.push_back(finalLevelLabel);
        tempLevel->setText("");
    }

    gameOverHighScore = new QPushButton("High Scores", this); buttonVector.push_back(gameOverHighScore);
    gameOverHighScore->setFixedSize(blockSize * 3, blockSize);
    connect(gameOverHighScore, SIGNAL(clicked()), this, SLOT(highScoresShow()) );
    gameOverLayout->addWidget(gameOverHighScore, Qt::AlignTop);

    gameOverRestart = new QPushButton("Restart Game", this); buttonVector.push_back(gameOverRestart);
    gameOverRestart->setFixedSize(blockSize * 3, blockSize);
    connect(gameOverRestart, SIGNAL(clicked()), this, SLOT(gameOverRestartSlot()) );
    gameOverLayout->addWidget(gameOverRestart, Qt::AlignTop);

    gameOverToMenu = new QPushButton("Main Menu", this); buttonVector.push_back(gameOverToMenu);
    gameOverToMenu->setFixedSize(blockSize * 3, blockSize);
    connect(gameOverToMenu, SIGNAL(clicked()), this, SLOT(menuPressed()) );
    gameOverLayout->addWidget(gameOverToMenu, Qt::AlignTop);


    /* * * * * * * * * * * * * * * * * * * *
     *          Survival Mode Items        *
     * * * * * * * * * * * * * * * * * * * */
    levelClear = new QGroupBox(this);
    levelClear->setAutoFillBackground(true);
    levelClear->setGeometry( (screenSizeX/2) - ((screenSizeX * 0.7) / 2), (screenSizeY/2) - ((screenSizeY * 0.2) / 2),
                             screenSizeX * 0.7 , screenSizeY * 0.2 );

    // create layout
    levelClearLayout = new QVBoxLayout(this);
    levelClearLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    levelClearLayout->setSpacing(25);
    levelClear->setLayout(levelClearLayout);
    levelClear->hide();

    //Initalize and add Items to the layout

    levelClearLabel = new QLabel(" Level Clear !"); labelVector.push_back(levelClearLabel);
    levelClearLabel->setFont(tempFont);
    levelClearLayout->addWidget(levelClearLabel, Qt::AlignHCenter | Qt::AlignTop);
    levelNext = new QPushButton("Next Level", this); buttonVector.push_back(levelNext);
    //    levelQuit = new QPushButton("Quit", this); buttonVector.push_back(levelQuit);
    levelNext->setFixedSize(blockSize * 2.7, blockSize);
    //    levelQuit->setFixedSize(blockSize * 3, blockSize);
    levelClearLayout->addWidget(levelNext, Qt::AlignHCenter);
    //    levelClearLayout->addWidget(levelQuit, Qt::AlignVCenter);
    connect(levelNext, SIGNAL(clicked()), this, SLOT(nextLevel()) );
    //    connect(levelQuit, SIGNAL(clicked()), this, SLOT(confirmQuit()) );

} // End setupWindow()


/**
 *  @brief MainWindow::setupGameScreen
 */
void MainWindow::setupGameScreen(){

    // Color scheme
    colorPtr = new Colors(0);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Button, colorPtr->getQColor(3));
    Pal.setColor(QPalette::ButtonText, QColor(0,0,0,255) );
    Pal.setColor(QPalette::Background, colorPtr->getQColor(0));
    Pal.setColor(QPalette::Text, colorPtr->getQColor(3));
    Pal.setColor(QPalette::WindowText, colorPtr->getQColor(3));
    this->setPalette(Pal);


    // Timers
    timer = new QTimer(this);
    btimer = new QTimer(this);
    //blockTimer = new QTimer(this);

    // Set Game Mode Flags
    stdModeFlag = 0;
    endlessModeFlag = 0;
    survivalModeFlag = 0;

    // Set Labels
    bombLabel=new QLabel("Bombs:"); labelVector.push_back(bombLabel);
    grid->addWidget(bombLabel,1,0);
    scoreLabel = new QLabel("Score: x1"); labelVector.push_back(scoreLabel);
    grid->addWidget(scoreLabel,0,0);
    timeLabel = new QLabel("Time:", this); labelVector.push_back(timeLabel);
    grid->addWidget(timeLabel, 7, 0);
    progressLabel = new QLabel("Progress:", this); labelVector.push_back(progressLabel);
    grid->addWidget(progressLabel, 7, 0);


    // Add score board
    sframe = new ScoreFrame();
    sframe->text->setFixedWidth(blockSize*5); labelVector.push_back(sframe->text);
    sframe->text->setFixedHeight(blockSize );
    grid->addWidget(sframe->text,0,1,1,1,Qt::AlignLeft);

    // Menu Button
    menuButton = new QPushButton("||",this); buttonVector.push_back(menuButton);
    connect(menuButton, SIGNAL(clicked()),this, SLOT(pausedPressed()));
    menuButton->setGeometry((0 + (blockSize)*6 ), screenSizeY - (blockSize)*1.6, blockSize*2, blockSize);
    menuButton->hide();

    // Shuffle Button

    shuffleButton = new QPushButton(QString::fromUtf8("\u2248"),this); // or 25A6
    buttonVector.push_back(shuffleButton);
    shuffleButton->setGeometry((0 + (blockSize)*4 ), screenSizeY - (blockSize)*1.6, blockSize*2, blockSize);
    connect(shuffleButton, SIGNAL(clicked()),this, SLOT(shufflePressed()));
    shuffleButton->hide();

    // Geometry Buttons

    rotateButton = new QPushButton(QString::fromUtf8("\u21B1"),this); buttonVector.push_back(rotateButton);
    rotateButton->setGeometry((0 + (blockSize)*0 ), screenSizeY - (blockSize)*1.6, blockSize*2, blockSize);
    connect(rotateButton, SIGNAL(clicked()),this, SLOT(rotate()));
    rotateButton->hide();

    horizontalFlipButton = new QPushButton(QString::fromUtf8("\u21C5"),this); buttonVector.push_back(horizontalFlipButton);
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

    Timeclock = new QLabel();
    Timefill = new QLabel();

    Timeclock->setGeometry(0,0,300,25);
    Timefill->setGeometry(0,0,300,25);

    Timeclock->setMaximumWidth(Timeclock->width());

    QPixmap newMap(Timeclock->width(), Timeclock->height());
    newMap.fill(QColor(250,250,250,255)); // Back color
    Timeclock->setPixmap(newMap);
    newMap.fill(colorPtr->getQColor(6)); // Front color
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
    bombColor.fill(QColor(250,250,250,255)); // Back layer
    bombLayer->setPixmap(bombColor);
    bombColor.fill(colorPtr->getQColor(1)); // Front layer
    bombFill->setPixmap(bombColor);
    grid->addWidget(bombLayer,1,1);
    grid->addWidget(bombFill,1,1);
    bombLayer->setMaximumWidth(bombLayer->width());
    connect(btimer, SIGNAL(timeout()), this, SLOT(bombtimeSlot()));

    //connect(blockTimer, SIGNAL(timeout()), this, SLOT(blockTimerSlot()));

    /* would ideally place an ellipse on the game board but doesn't work yet
    QGraphicsEllipseItem *myEllipse = new QGraphicsEllipseItem();
    myEllipse->setRect(3 * blockSize, 4 * blockSize, (blockSize - 1), (blockSize - 1));
    myEllipse->setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
    theScene->addItem(myEllipse);
    */
} // End setupInterface()

/**
 *  @brief MainWindow::setupBlocks
 *
 */
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

/**
 *  @brief MainWindow::mousePressEvent
 *  @param event
 */
void MainWindow::mousePressEvent(QMouseEvent *event){
    if(!pauseMenu->isVisible() && !gameOverMenu->isVisible() && !levelClear->isVisible()){    // Only allow clicks when no menu is displayed

        // On first press hide start screen & start
        if(startScreen->isVisible()){
            startScreen->hide();
            shuffleButton->show();
            rotateButton->show();
            horizontalFlipButton->show();
            menuButton->show();

            btimer->start(333.333);
            if(stdModeFlag == 1){
                Timefill->setMaximumWidth(Timeclock->width());
                currentTime=60;
                timer->start(200);
            }
            else if(survivalModeFlag == 1){
                Timefill->setMaximumWidth(Timeclock->width() / 2);
                currentTime = 30;
//                timer->start(timerCounter);
            }
        }

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


/**
 * @brief MainWindow::updateBomb
 * @param nBlocks
 */
void MainWindow::updateBomb(int nBlocks){

    int updateVal;
//    updateVal = (nBlocks-1)*(nBlocks-1);
    updateVal = nBlocks * 8;

    if ((bombFill->maximumWidth()+updateVal) < bombLayer->maximumWidth()){
        bombFill->setMaximumWidth(bombFill->maximumWidth()+updateVal);
        if (bombFill->maximumWidth() > 0){
            bcurrentTime += (updateVal/4);
            btimeBegin();
        }
    }
    else if ((bombFill->maximumWidth()+updateVal) >= bombLayer->maximumWidth()){
             bombFill->setMaximumWidth(0);
             //funciton call to make new image
             generateGraphicObject(-1, -1);
             btimeOver();
             bcurrentTime=0;
    }

}

/**
 * @brief MainWindow::updateProgress
 * @param nBlocks
 */
void MainWindow::updateProgress(int nBlocks){
    int updateVal;
    updateVal = nBlocks * 7;

    if((Timefill->maximumWidth() + updateVal) < Timeclock->maximumWidth()){
        Timefill->setMaximumWidth(Timefill->maximumWidth() + updateVal);
        if(Timefill->maximumWidth() > 0){
            currentTime += (updateVal/3);
            timeBegin();
        }
    }
    else if((Timefill->maximumWidth() + updateVal) >= Timeclock->maximumWidth()){
        processProgress();//reached new level of survival
    }
}


/************************************
 *  The Slots that the buttons use. *
 ************************************/

/**
 * @brief MainWindow::menuPressed
 */
void MainWindow::menuPressed(){

    // Quit Game and go back to Main Menu
    if(endlessModeFlag == 1)
        addScore();
    reset();
    scorePtr->resetScore();
    sframe->resetScoreBoard();
    shuffleButton->hide();
    rotateButton->hide();
    horizontalFlipButton->hide();
    menuButton->hide();
    timeLabel->hide();
    confirmMenu->hide();

    mainMenu->show();

    if(gamedone==true)
        gameOverMenu->hide();

}

/**
 * @brief MainWindow::confirmQuit
 */
void MainWindow::confirmQuit(){

    if(gamedone!=true){
    if(pauseMenu->isVisible())
        pauseMenu->hide();

    else if(gameOverMenu->isVisible()){
        gameOverMenu->hide();
        disconnect(confirmRejectButton, SIGNAL(clicked()), this, SLOT(quitRejected()) );
        connect(confirmRejectButton, SIGNAL(clicked()), this, SLOT(quitRejectedGameOver()) );
    }

    confirmMenu->show();
    }
}

/**
 * @brief MainWindow::quitRejected
 */
void MainWindow::quitRejected(){
    confirmMenu->hide();
    pauseMenu->show();
}

/**
 * @brief MainWindow::quitRejectedGameOver
 */
void MainWindow::quitRejectedGameOver(){
    confirmMenu->hide();
    gameOverMenu->show();
    disconnect(confirmRejectButton, SIGNAL(clicked()), this, SLOT(quitRejectedGameOver()) );
    connect(confirmRejectButton, SIGNAL(clicked()), this, SLOT(quitRejected()) );
}

/**
 * @brief MainWindow::pauseBack
 */
void MainWindow::pauseBack(){
    pauseMenu->hide();
    if(endlessModeFlag != 1)
        timeBegin();
    if(bcurrentTime!=0)
        btimeBegin();
}

/**
 * @brief MainWindow::pausedPressed
 */
void MainWindow::pausedPressed(){
    if (!levelClear->isVisible()){
    pauseMenu->show();
    timeOver();
    btimeOver();
    }
}
/**
 * @brief MainWindow::pauseSettingsPressed
 */
void MainWindow::pauseSettingsPressed(){
    pauseMenu->hide();
    shuffleButton->hide();
    rotateButton->hide();
    horizontalFlipButton->hide();
    menuButton->hide();
    settingsMenu->show();
    disconnect(backToMenu2, SIGNAL(clicked()), this, SLOT(backToMain()) );
    connect(backToMenu2, SIGNAL(clicked()), this, SLOT(backToPause()) );
}

/**
 * @brief MainWindow::backToPause
 */
void MainWindow::backToPause(){
    highScoreMenu->hide();
    settingsMenu->hide();
    mainMenu->hide();
    shuffleButton->show();
    horizontalFlipButton->show();
    rotateButton->show();
    menuButton->show();
    pauseMenu->show();
    disconnect(backToMenu2, SIGNAL(clicked()), this, SLOT(backToPause()) );
    connect(backToMenu2, SIGNAL(clicked()), this, SLOT(backToMain()) );

    disconnect(backToMenu4, SIGNAL(clicked()), this, SLOT(backToPause()) );
    connect(backToMenu4, SIGNAL(clicked()), this, SLOT(backToMain()) );
}

/**
 * @brief MainWindow::newGamePressed
 */
void MainWindow::newGamePressed(){
    mainMenu->hide();
    gameModeMenu->show();
}
/**
 * @brief MainWindow::settingsPressed
 */
void MainWindow::settingsPressed(){
    mainMenu->hide();
    settingsMenu->show();
}

/**
 * @brief MainWindow::helpPressed
 */
void MainWindow::helpPressed(){
    mainMenu->hide();
    helpMenu->show();
}

/**
 * @brief MainWindow::backToMain
 */
void MainWindow::backToMain(){

    if(gameModeMenu->isVisible())
        gameModeMenu->hide();

    else if(settingsMenu->isVisible())
        settingsMenu->hide();

    else if(helpMenu->isVisible())
        helpMenu->hide();

    else if(highScoreMenu->isVisible())
        highScoreMenu->hide();

    mainMenu->show();
}

/**
 * @brief MainWindow::gameOverMenuSlot
 */
void MainWindow::gameOverMenuSlot(){
    gameOverMenu->hide();
    shuffleButton->hide();
    rotateButton->hide();
    horizontalFlipButton->hide();
    menuButton->hide();
    mainMenu->show();
}

/**
 * @brief MainWindow::gameOverRestartSlot
 */
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

/**
 * @brief   changeColorScheme() creates a new palette based on the users input on the slider provided in the Settings menu.  A new palette is created and then all QLabels and QPushButtons are reassigned to this palette.
 *          The update affects QPushButtons, QLabels, and the timers (both time and bomb).
 * @bug     On 3 of 4 computers used in this group, no way could be found to update the color scheme of the QPushButtons.  On 1 computer, we were successful in updating the QPushButtons using both style sheets and palettes, but neither method worked on the other machines.
 */
void MainWindow::changeColorScheme(){
    // change color scheme based on slider value (by setting all labels and buttons to new palette)
    colorPtr->setScheme(colorSlider->value());

    QPalette Pal(palette());
    Pal.setColor(QPalette::Button, colorPtr->getQColor(3));
    Pal.setColor(QPalette::ButtonText, QColor(0,0,0,255) );
    Pal.setColor(QPalette::Background, colorPtr->getQColor(0));
    Pal.setColor(QPalette::Text, colorPtr->getQColor(3));
    Pal.setColor(QPalette::WindowText, colorPtr->getQColor(3));
    Pal.setColor(QPalette::Base, QColor(0, 0, 0));

    helpText->setPalette(Pal);  // Change about menu text's color

    for (int i=0; i< (int) labelVector.size(); i++) {
        ((QLabel*) labelVector.at(i))->setPalette(Pal);
    }

    for (int i=0; i< (int) buttonVector.size(); i++) {
        //((QLabel*) buttonVector.at(i))->setPalette(Pal);
        // Buttons do not change colors on all machines when a palette is used
        ((QPushButton*) buttonVector.at(i))->setStyleSheet("* {background-color: " + colorPtr->getQColor(3).name() + "}");
        // Buttons do not change colors on all machines when a style sheet is used
    }

    // Reset gameboard colors
    if (start) {
        for (int x=0; x<boardSizeX; x++) {
            for (int y=0; y<boardSizeY; y++) {
                rectArray[x][y]->setBrush(QBrush(colorPtr->getQColor(gameBoard[x][y]->getColor()), Qt::SolidPattern));
            }
        }
    }

    // Reset bar colors
    QPixmap newMap(Timeclock->width(), 25);
    newMap.fill(colorPtr->getQColor(1)); // Back color
    Timefill->setPixmap(newMap);

    QPixmap newMapB(Timeclock->width(), 25);
    newMapB.fill(colorPtr->getQColor(6)); // Back color
    bombFill->setPixmap(newMapB);

}

/**
 * @brief MainWindow::highScoresShow
 */
void MainWindow::highScoresShow(){
    if(mainMenu->isVisible()){
        mainMenu->hide();

    }
    else if(gameOverMenu->isVisible()){
        gameOverMenu->hide();
        horizontalFlipButton->hide();
        rotateButton->hide();
        shuffleButton->hide();
        menuButton->hide();
        disconnect(backToMenu4, SIGNAL(clicked()), this, SLOT(backToMain()) );
        connect(backToMenu4, SIGNAL(clicked()), this, SLOT(backToGameOver()) );
    }
    else if(pauseMenu->isVisible()){
        pauseMenu->hide();
        horizontalFlipButton->hide();
        rotateButton->hide();
        shuffleButton->hide();
        menuButton->hide();
        disconnect(backToMenu4, SIGNAL(clicked()), this, SLOT(backToMain()) );
        connect(backToMenu4, SIGNAL(clicked()), this, SLOT(backToPause()) );
    }

    pauseMenu->hide();
    highScoreMenu->show();
}

/**
 * @brief MainWindow::backToGameOver
 */
void MainWindow::backToGameOver(){
    disconnect(backToMenu4, SIGNAL(clicked()), this, SLOT(backToGameOver()) );
    connect(backToMenu4, SIGNAL(clicked()), this, SLOT(backToMain()) );

    highScoreMenu->hide();
    shuffleButton->show();
    rotateButton->show();
    horizontalFlipButton->show();
    menuButton->show();
    gameOverMenu->show();
}

/**
 * @brief MainWindow::standardMode
 */
void MainWindow::standardMode(){
    newHighScore->hide();
    gameModeMenu->hide();
    startScreen->show();
    shuffleButton->hide();
    rotateButton->hide();
    progressLabel->hide();
    horizontalFlipButton->hide();
    menuButton->hide();
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

/**
 * @brief MainWindow::nextLevel
 */
void MainWindow::nextLevel(){
    startScreen->hide();
    timeLabel->hide();
    levelClear->hide();
    progressLabel->show();
    Timefill->show();
    Timeclock->show();
    gtimer->stop();
    gCount = 4;
    k=0;

    shufflePressed();//shuffles blocks / graph objects
//    timer->start(timerCounter);//start timer with new incremented timer speed
    timer->start(timerCounter);
    btimeBegin();
}


/**
 * @brief MainWindow::survivalMode
 */
void MainWindow::survivalMode(){
    newHighScore->hide();
    gameModeMenu->hide();
    startScreen->show();
    shuffleButton->hide();
    rotateButton->hide();
    horizontalFlipButton->hide();
    menuButton->hide();
    timeLabel->hide();
    progressLabel->show();
    Timefill->show();
    Timeclock->show();
    scorePtr->resetScore();
    sframe->resetScoreBoard();

    stdModeFlag = 0;
    endlessModeFlag = 0;
    survivalModeFlag = 1;
    level=1;
    progressLevel= 180;
    timerCounter = 200;

    startGame();
}

/**
 * @brief MainWindow::endlessMode
 */
void MainWindow::endlessMode(){
    newHighScore->hide();
    gameModeMenu->hide();
    startScreen->show();
    shuffleButton->hide();
    rotateButton->hide();
    horizontalFlipButton->hide();
    menuButton->hide();
    timeLabel->hide();
    Timeclock->hide();
    Timefill->hide();
    scorePtr->resetScore();
    sframe->resetScoreBoard();
    progressLabel->hide();

    stdModeFlag = 0;
    endlessModeFlag = 1;
    survivalModeFlag = 0;

    startGame();
}

/**
 * @brief MainWindow::addScore
 */
void MainWindow::addScore(){
    menuButton->hide();
    if(stdModeFlag == 1){
        if(theHighScores->addHighScore("standard", scorePtr->getScore(), 0) == 1)
            newHighScore->show();
    }
    else if(survivalModeFlag == 1){
        if(theHighScores->addHighScore("survival", scorePtr->getScore(), level) == 1)
            newHighScore->show();
    }
    else if(endlessModeFlag == 1){
        theHighScores->addHighScore("endless", scorePtr->getScore(), 0);
    }

    theHighScores->writeHighScores();
    theHighScores->loadHighScores();
}

/**
 * @brief   shufflePressed() preserves the blocks' color and any stars but shuffles the blocks randomly.
            The shuffle is performed by randomly swapping pairs of blocks.  The number of swaps performed is quadratic in the area of the board.
            This button is inactive if the game is paused.
 * @param   None
 * @return  Void
 */

void MainWindow::shufflePressed() {
    // Only shuffles if not paused
    if(!pauseMenu->isVisible() && !levelClear->isVisible() && !gameOverMenu->isVisible()){

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

            if(gameBoard[r1][c1]->getGraphImage() != gameBoard[r2][c2]->getGraphImage())
                graphSwap(r1, c1, r2, c2);
        }

    }
}

/**
 * @brief MainWindow::quit
 */
void MainWindow::quit(){
    close();
}

// End Slots


/**
 * @brief   horizontalFlip() preserves the blocks' color and any stars but shuffles the blocks so that they get flipped along the horizontal access.
            This button is inactive if the game is paused.
 * @param   None
 * @return  Void
 */

void MainWindow::horizontalFlip() {
    // Only flips if not paused
    if(!pauseMenu->isVisible() && !gameOverMenu->isVisible() && !levelClear->isVisible()){

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

                if(gameBoard[x1][y1]->getGraphImage() != gameBoard[x2][y2]->getGraphImage())
                    graphSwap(x1, y1, x2, y2);
            }
        }

    }
}


/**
 * @brief   rotate() preserves the blocks' color and any stars but rotates the blocks 180 degrees.
            This button is inactive if the game is paused.
 * @param   None
 * @return  Void
 */

void MainWindow::rotate() {

    // Only flips if not paused
    if(!pauseMenu->isVisible() && !levelClear->isVisible() && !gameOverMenu->isVisible()){

        int x, y;

        for (x=0; x<boardSizeX/2; x++) {
            for (y=0; y<boardSizeY; y++) {
                int x1, y1, x2, y2, tempColor;
                x1=x;
                x2=boardSizeX-1-x;
                y1=y;
                y2=boardSizeY-1-y;;

                tempColor = gameBoard[x1][y1]->getColor();
                gameBoard[x1][y1]->setColor( gameBoard[x2][y2]->getColor() );
                gameBoard[x2][y2]->setColor(tempColor);

                rectArray[gameBoard[x1][y1]->getCoordX()][gameBoard[x1][y1]->getCoordY()]->setBrush(QBrush(colorPtr->getQColor(gameBoard[x1][y1]->getColor()), Qt::SolidPattern));
                rectArray[gameBoard[x2][y2]->getCoordX()][gameBoard[x2][y2]->getCoordY()]->setBrush(QBrush(colorPtr->getQColor(gameBoard[x2][y2]->getColor()), Qt::SolidPattern));
                if(gameBoard[x1][y1]->getGraphImage() != gameBoard[x2][y2]->getGraphImage())
                    graphSwap(x1, y1, x2, y2);
            }
        }
    }
}



/**
 * @brief   verticalFlip() preserves the blocks' color and any stars but shuffles the blocks so that they get flipped along the vertical access.
            This button is inactive if the game is paused.
            This method is not currently in use in the game because it does not offer a strategic benefit the way the other shuffles do.
 * @param   None
 * @return  Void
 */

void MainWindow::verticalFlip() {

    // Only flips if not paused
    if(!pauseMenu->isVisible() && !gameOverMenu->isVisible() && !levelClear->isVisible()){

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
                if(gameBoard[x1][y1]->getGraphImage() != gameBoard[x2][y2]->getGraphImage())
                    graphSwap(x1, y1, x2, y2);
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
/**
 * @brief MainWindow::reset
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

    // Need to undo any updates to the multiplier label
    scoreLabel->setText("Score: x1");
}




/*
Start of Block game algorithm functions:
*/
/**
 * @author Daniel Keasler
 * @author Shannon Harwick
 * @author Mike Son
 * @brief MainWindow::processMatch basic game flow from gathering matched blocks to processing scoring and new colors
 * @description gatherBlocks is called from the matchedBlock to collect all matching adjacent blocks.
 *      all gathered blocks are checked for stars, more could be added
 *      all blocks are sorted relative to column height and set to black
 *      .05 second timer to show noticeable transition
 *      score is updated
 *      bomb bar is incremented
 *      progress bar is incremented if in survival mode
 *      new colors are assigned
 * @param matchedBlock
 * @return void
 */
void MainWindow::processMatch(Block* matchedBlock)
{
    // SHupdate - rearranged by Dan for order
    vector<Block*> gatheredBlocks;
    gatheredBlocks = matchedBlock->gatherBlocks(gatheredBlocks);
	//NIY; will test when graphical images are loaded on top
    gatheredBlocks = checkSpecials(gatheredBlocks);
    gatheredBlocks = sortVector(gatheredBlocks);

    QEventLoop loop;
    QTimer::singleShot(50, &loop, SLOT(quit()) );
    loop.exec();
        //transition period right here, after all blocks have been turned black

    scorePtr->updateScore((int) gatheredBlocks.size(), false);
    sframe->update(scorePtr->getScore());
    updateBomb((int) gatheredBlocks.size());
    if(survivalModeFlag == 1)
        updateProgress((int) gatheredBlocks.size());
    //blockTimerCounter = 0;
    //while(blockTimerCounter <= 1){

    //}
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
/**
 * @author Daniel Keasler
 * @brief MainWindow::sortVector all blocks in blockVector are sorted in descending order with respect to y
 * @param blockVector
 * @return vector<Block*>
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

/**
 * @author Daniel Keasler
 * @brief MainWindow::determineColor swaps color of blocks upwards from the column of the ith block
 * @description checky is a walker variable upwards in the 2D array of blocks. while checky is still
 *      in bounds of the array, the algorithm searches for a block that is not also needing a color change.
 *      The blocks are already sorted based on y so the algorithm will never replace the same blocks color more
 *      than once. If it steals a color from a block, that block that lost its color is put on the end of the vector.
 *      If it doesn't find a color to steal, then a new color is randomly determined.
 * @param blockVector
 * @return void
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
                if(gameBoard[blockVector[i]->getCoordX()][checkY]->getGraphImage() != gameBoard[blockVector[i]->getCoordX()][blockVector[i]->getCoordY()]->getGraphImage())
                    graphSwap(blockVector[i]->getCoordX(), blockVector[i]->getCoordY(), blockVector[i]->getCoordX(), checkY);
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
 
/**
 * @author Daniel Keasler
 * @brief MainWindow::checkSpecials checks every single block for a special star (graph image of 2) and takes care
 *      of some bookkeeping if it finds one.
 * @param blockVector
 * @return vector<Block*>
 */
vector<Block*> MainWindow::checkSpecials(vector<Block*> blockVector)
{
    for(int i = 0; (unsigned)i < blockVector.size(); i++)
    {
        if(blockVector[i]->getGraphImage() == 2)
        {
         //           switch(blockVector[i]->getGraphImage()){

         //           case 1 : //score case
                        //score mult is updated first
                        //vector swap and erase of this scoring object
                        //changeIndex called for swapped graph objects
          //              break;
           //         case 2 : //bomb case
           //             blockVector = bombCollector(blockVector, blockVector[i]->getCoordX(), blockVector[i]->getCoordY());
           //             break;
          //          case 3 : //vertical case
          //              blockVector = blockVector[i]->upCollector(blockVector);
          //              blockVector = blockVector[i]->downCollector(blockVector);
          //              break;
          //          case 4 : //horizontal case
           //             blockVector = blockVector[i]->rightCollector(blockVector);
           //             blockVector = blockVector[i]->leftCollector(blockVector);
          //              break;
          //          case 5 : //4 arrows case
          //              blockVector = blockVector[i]->upCollector(blockVector);
          //              blockVector = blockVector[i]->downCollector(blockVector);
          //              blockVector = blockVector[i]->rightCollector(blockVector);
         //               blockVector = blockVector[i]->leftCollector(blockVector);
         //               break;
         //           }
            scorePtr->incrementMultiplier();
            QString m = QLocale(QLocale::English).toString((double) scorePtr->getMultiplier(), 'f', 0);
            scoreLabel->setText("Score: x" + m);

            blockVector = bombCollector(blockVector, blockVector[i]->getCoordX(), blockVector[i]->getCoordY());
            blockVector[i]->setGraphImage(0);
            theScene->removeItem(rectArray[blockVector[i]->getCoordX()][blockVector[i]->getCoordY()]->textPtr);
            rectArray[blockVector[i]->getCoordX()][blockVector[i]->getCoordY()]->removeGraphObject(false);
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
/**
 * @author Daniel Keasler
 * @brief MainWindow::bombCollector searches a 3x3 subset of the array (centered at the x and y) for new blocks to collect
 * @param blockVector
 * @param x
 * @param y
 * @return vector<Block*>
 */
vector<Block*> MainWindow::bombCollector(vector<Block*> blockVector, int x, int y)
{
    for(int i = (x - 1); i < (x + 2); i++)
    {
        if(i > (boardSizeX - 1)) //needs to be changed for 7x9
            break;
        if(i < 0)
            continue;
        for(int j = (y - 1); j < (y + 2); j++)
        {
            if(j > (boardSizeY-1) || j < 0) //needs to be changed for 7x9
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


/**
 * @brief MainWindow::gtimeSlot
 */
void MainWindow::gtimeSlot(){
k++;
if(k%1==0){
    gCount--;
}
if(gCount==-1){
    nextLevel();
    gtimer->stop();
}
//bombFill->setMaximumWidth(bombFill->maximumWidth()-(bombLayer->width()/120));
}


/**
 * @brief MainWindow::bombtimeSlot
 */
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

/**
 * @brief MainWindow::timeSlot
 */
void MainWindow::timeSlot(){
    x++;
    if(x%4==0){
        currentTime--;
    }
//    if(currentTime==-1){
//        int n= scorePtr->getScore();
//        QString num = QLocale(QLocale::English).toString((double) n, 'f', 0);
//        tempScore->setText(num);

//        if (survivalModeFlag==1) {
//            tempLevel->setText(QString::number(level));
//            finalLevelLabel->setText("Your Final Level:");
//        }
//        else {
//            tempLevel->setText("");
//            finalLevelLabel->setText("");
//        }

//        gameOverMenu->show();
//        addScore();
//        timeOver();
//        btimeOver();
//        //close();
//        //return;
//    }
    if(Timefill->maximumWidth() == 0){
                gamedone = true;


                int n= scorePtr->getScore();
                QString num = QLocale(QLocale::English).toString((double) scorePtr->getScore(), 'f', 0);
                tempScore->setText(num);

                if (survivalModeFlag==1) {
                    tempLevel->setText(QString::number(level));
                    finalLevelLabel->setText("Your Final Level:");
                }
                else {
                    tempLevel->setText("");
                    finalLevelLabel->setText("");
                }

                gameOverMenu->show();
                addScore();
                theHighScores->writeHighScores();
                timeOver();
                btimeOver();
                //close();
                //return;
    }
    Timefill->setMaximumWidth(Timefill->maximumWidth()-(Timeclock->width()/150));
}

//void MainWindow::blockTimerSlot(){
    //blockTimerCounter++;
//}

/**
 * @brief MainWindow::btimeOver
 */
void MainWindow::btimeOver(){
    btimer->stop();
}

/**
 * @brief MainWindow::btimeBegin
 */
void MainWindow::btimeBegin(){
    btimer->start();
}

/**
 * @brief MainWindow::timeOver
 */
void MainWindow::timeOver(){
    timer->stop();
}
/**
 * @brief MainWindow::timeBegin
 */
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
 */
/**
 * @author Daniel Keasler
 * @author Mike Son
 * @author Shannon Harwick
 * @brief MainWindow::startGame destroys and creates a new board. Also restarts the timers.
 * @return void
 */
void MainWindow::startGame(){
    removeBlocks();
    setupBlocks();
    bombFill->setMaximumWidth(0);
    gamedone = false;
    bcurrentTime=0;
    btimer->start(333.333);
    Timefill->setMaximumWidth(Timeclock->width());
    currentTime = 60;
    if(stdModeFlag == 1){
        timer->start(200);
    }
    else if(survivalModeFlag == 1){
        Timefill->setMaximumWidth(Timeclock->width() / 2);
        currentTime = 30;
        timer->start(200);
    }
    scoreLabel->setText("Score: x1");
}

/**
 * @author Daniel Keasler
 * @author Mike Son
 * @brief MainWindow::processProgress stops previous timers, increments level and new timer speed, starts next timer
 * @return void
 */
void MainWindow::processProgress(){
    //this function would be called from the updateProgressTime function
        timeOver();//stop timer
        btimeOver();
        levelClear->show();
        level++;//increment level counter (would need to have started at 1 for each survival call)
        //group box with level x incoming, etc
        timerCounter -= (7 * (level-1));//increment timer speed, maybe formula from level counter
        if (timerCounter == 0 || timerCounter < 0)
            timerCounter =1;
//        progressLevel = ((1000 / timerCounter) * 60);
        Timefill->setMaximumWidth(Timeclock->width() / 2);//set timer to 50%
        currentTime = 30;

//        connect(gtimer, SIGNAL(timeout()), this, SLOT(gtimeSlot()));

        gtimer->start();

}

/**
 * @author Daniel Keasler
 * @brief MainWindow::generateGraphicObject creates a Unicode star for either a random location or an assigned location
 * @description If CoordX is < 0, then I passed -1 to the function to generate a random set of coordinates
 *      There is also a check for generating a random coordinate pair that already contains a star.
 *      QGraphicsSimpleTextItem can be used to display unicode characters on a graphics scene.
 *      0x2605 is a unicode star.
 *      There is also some centering and scaling.
 *      Star is added to the scene and stored in the block.
 * @bug Star is correctly centered and scaled on 3/4 computers.
 * @return void
 */
void MainWindow::generateGraphicObject(int CoordX, int CoordY){
    bool randomAssign = false;
    if(CoordX < 0)
    {
        CoordX = rand() % 8;
        CoordY = rand() % 9;
        randomAssign = true;
    }
    while(randomAssign && gameBoard[CoordX][CoordY]->getGraphImage() == 2)
    {
        CoordX = rand() % 8;
        CoordY = rand() % 9;
    }

    //QGraphicsEllipseItem *myEllipse = new QGraphicsEllipseItem();
    //myEllipse->setRect((blockSize * CoordX) + 5, (blockSize * CoordY) + 5, blockSize - 10, blockSize - 10);
    //myEllipse->setBrush(QBrush(Qt::black, Qt::SolidPattern));
    //rectArray[CoordX][CoordY]->setEllipse(myEllipse);
    //delete myEllipse;
    //gameBoard[CoordX][CoordY]->setGraphImage(2);
    //theScene->addItem(myEllipse);

    QGraphicsSimpleTextItem *myTextItem = new QGraphicsSimpleTextItem();
    QString myString(QChar(0x2605));
    myTextItem->setText(myString);
    myTextItem->setX((CoordX * blockSize) + 4.5);
    myTextItem->setY((CoordY * blockSize) - 4);
    myTextItem->setScale(3);
    myTextItem->setBrush(QBrush(Qt::black, Qt::SolidPattern));
    rectArray[CoordX][CoordY]->setTextItem(myTextItem);
    gameBoard[CoordX][CoordY]->setGraphImage(2);
    theScene->addItem(myTextItem);

}


/**
 * @author Daniel Keasler
 * @brief MainWindow::graphSwap removes and deletes one star, creates a new one to display in the other coordinate pair
 * @param firstX
 * @param firstY
 * @param secondX
 * @param secondY
 * @return void
 */
void MainWindow::graphSwap(int firstX, int firstY, int secondX, int secondY){
    if(gameBoard[firstX][firstY]->getGraphImage() == 2){
        theScene->removeItem(rectArray[firstX][firstY]->textPtr);
        rectArray[firstX][firstY]->removeGraphObject(false);
        gameBoard[firstX][firstY]->setGraphImage(0);
        generateGraphicObject(secondX, secondY);
    }
    else{
        theScene->removeItem(rectArray[secondX][secondY]->textPtr);
        rectArray[secondX][secondY]->removeGraphObject(false);
        gameBoard[secondX][secondY]->setGraphImage(0);
        generateGraphicObject(firstX, firstY);
    }

}
/**
 * @author Daniel Keasler
 * @brief MainWindow::removeBlocks deletes and nulls everything from the previous game board. start decision to avoid segfaults for the first game.
 * @return void
 */
void MainWindow::removeBlocks(){
    if(start){
        for(int i = 0; i < boardSizeX; i++){
            for(int j = 0; j < boardSizeY; j++){
                delete gameBoard[i][j];
                gameBoard[i][j] = 0;
                //if(rectArray[i][j]->bombPtr != 0)
                    //rectArray[i][j]->bombPtr->setBrush(QBrush(Qt::yellow));
                if(rectArray[i][j]->textPtr != 0)
                    theScene->removeItem(rectArray[i][j]->textPtr);
                rectArray[i][j]->removeGraphObject(true);
                //delete rectArray[i][j]->textPtr;
                theScene->removeItem(rectArray[i][j]);
                //rectArray[i][j]->setBrush(QBrush(Qt::yellow));
                delete rectArray[i][j];
                rectArray[i][j] = 0;
            }
        }
    }
    else
        start = true; //start is initialized to false in menu set up
}

// End mainwindow_UI.cpp
