/**********************************
 * Plock - An android game
 * MainWindow.cpp
 *
 * @author Devin Rusnak
 * @version Qt:4.8.3
 * UIC CS 340 Fall 2012
 *
 **********************************/
#include "mainwindow_UI.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    setupWindows();
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
    ADDED:
    This is also where the menus are instantiated. They are simple
    group box widgets that take up the whole screen and are .show/.hide
    depending on when we need them.
 *********************************************************************/
void MainWindow::setupWindows(){

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



    // Setup Main Menu
    mainMenu = new QGroupBox(this);
    mainMenu->setFixedSize(screenSizeX, screenSizeY);
    mainMenu->setAutoFillBackground(true);

    mainMenuLayout = new QVBoxLayout(this);
    mainMenuLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    mainMenuLayout->setSpacing(0);
    mainMenu->setLayout(mainMenuLayout);

    titleLabel = new QLabel("   B L O C K S T A R");
    titleLabel->setFixedSize(blockSize*5, blockSize*2);
    mainMenuLayout->addWidget(titleLabel, Qt::AlignHCenter);

    newGameButton = new QPushButton(this);
    newGameButton->setText("New Game");
    newGameButton->setFixedSize(blockSize*3, blockSize);
    connect( newGameButton, SIGNAL(clicked()), this, SLOT(newGamePressed()) );
    mainMenuLayout->addWidget(newGameButton, Qt::AlignTop);

    settingsButton = new QPushButton("Settings", this);
    settingsButton->setFixedSize(blockSize*3, blockSize);
    connect( settingsButton, SIGNAL(clicked()), this, SLOT(settingsPressed()) );
    mainMenuLayout->addWidget(settingsButton, Qt::AlignTop);

    helpButton = new QPushButton("About", this);
    helpButton->setFixedSize(blockSize*3, blockSize);
    connect( helpButton, SIGNAL(clicked()), this, SLOT(helpPressed()) );
    mainMenuLayout->addWidget(helpButton, Qt::AlignTop);



    // Setup Game Mode Menu
    gameModeMenu = new QGroupBox(this);
    gameModeMenu->setFixedSize(screenSizeX, screenSizeY);
    gameModeMenu->setAutoFillBackground(true);
    gameModeMenu->hide();

    modeMenuLayout = new QVBoxLayout(this);
    modeMenuLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    modeMenuLayout->setSpacing(0);
    gameModeMenu->setLayout(modeMenuLayout);

    gameModeTitle = new QLabel("Choose A Game Mode");
    modeMenuLayout->addWidget(gameModeTitle, Qt::AlignTop);

    standardModeButton = new QPushButton("Standard Mode", this);
    connect(standardModeButton, SIGNAL(clicked()), this, SLOT(standardMode()) );
    modeMenuLayout->addWidget(standardModeButton, Qt::AlignTop);

    backToMenu = new QPushButton("Back", this);
    connect(backToMenu, SIGNAL(clicked()), this, SLOT(backToMain()) );
    modeMenuLayout->addWidget(backToMenu, Qt::AlignTop);



    // Setup Settings Menu
    settingsMenu = new QGroupBox(this);
    settingsMenu->setFixedSize(screenSizeX, screenSizeY);
    settingsMenu->setAutoFillBackground(true);
    settingsMenu->hide();

    settingsLayout = new QGridLayout(this);
    settingsLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    settingsLayout->setSpacing(0);
    settingsMenu->setLayout(settingsLayout);

    settingsTitle = new QLabel("S e t t i n g s");
    settingsLayout->addWidget(settingsTitle, 0, 0, Qt::AlignTop);

    soundCheck = new QCheckBox(this);
    soundCheck->setCheckable(true);
    connect(soundCheck, SIGNAL(clicked()), this, SLOT(noSound()) );
    settingsLayout->addWidget(new QLabel("No Sound:"), 1, 0, Qt::AlignLeft);
    settingsLayout->addWidget(soundCheck, 1, 1);

    screenLockCheck = new QCheckBox(this);
    screenLockCheck->setCheckable(true);
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


    // Setup Help Menu
    helpMenu = new QGroupBox(this);
    helpMenu->setFixedSize(screenSizeX, screenSizeY);
    helpMenu->setAutoFillBackground(true);
    helpMenu->hide();

    helpMenuLayout = new QVBoxLayout(this);
    helpMenuLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    helpMenuLayout->setSpacing(0);
    helpMenu->setLayout(helpMenuLayout);

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



} // End setupWindow()

/*********************************************************************
  void setupInterface():
    This method initalizes and places all of the widgets used in the
    game. The main game board is a QGraphicsView with a QGraphicsScene
    with custom QGraphicsRectItems.
 *********************************************************************/
void MainWindow::setupInterface(){

    // Color scheme
    colorPtr = new Colors(0);

    // Set Labels
    grid->addWidget(new QLabel("Bombs:"),0,1);
    grid->addWidget(new QLabel("Score:"),0,0);
    grid->addWidget(new QLabel("Time:"),7,0);

    // Add score board
    scorePtr = new Score();
    sframe = new ScoreFrame();
    sframe->text->setFixedWidth(blockSize*2);
    sframe->text->setFixedHeight(blockSize );
    grid->addWidget(sframe->text,1,0,1,1,Qt::AlignLeft);

    // Bomb Progress Bar
    bombBar = new QProgressBar(this);
    bombBar->setFixedSize(blockSize * 2, blockSize);
    grid->addWidget(bombBar,1, 1, Qt::AlignLeft);

    // Menu Button
    menuButton = new QPushButton("||",this);
    menuButton->setFixedSize(blockSize ,blockSize);
    connect(menuButton, SIGNAL(clicked()),this, SLOT(pausedPressed()));
    grid->addWidget(menuButton,1,3);

    // Pause Menu
    pauseMenu = new QGroupBox(this);
    pauseMenu->setAutoFillBackground(true);
    pauseMenu->setGeometry( (screenSizeX/2) - ((screenSizeX * 0.8) / 2), (screenSizeY/2) - ((screenSizeY * 0.4) / 2),
                           screenSizeX * 0.8 , screenSizeY * 0.4 );
    pauseMenuLayout = new QVBoxLayout(this);
    pauseMenuLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    pauseMenuLayout->setSpacing(25);
    pauseMenu->setLayout(pauseMenuLayout);
    pauseMenu->hide();

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


    // Shuffle Button
    shuffleButton = new QPushButton("Shuffle",this);
    shuffleButton->setGeometry((bombBar->x() + (blockSize*6) ), bombBar->y() + (blockSize / 2), blockSize, blockSize);
    connect(shuffleButton, SIGNAL(clicked()),this, SLOT(shufflePressed()));
    shuffleButton->hide();

    // Block Viewing Area
    theScene = new QGraphicsScene();
    theScene->setSceneRect(0, 0, screenSizeX-4, (blockSize * boardSizeY)-4);
    blockView = new QGraphicsView(theScene);
    blockView->setFixedSize(screenSizeX, blockSize * boardSizeY);
    grid->addWidget(blockView,2,0,5,-1, Qt::AlignLeft);
    blockView->show();

    // Time Progress Bar

    currentTime=60;
//    timeBar = new QProgressBar(this);
//    timeBar->setFixedSize(screenSizeX - (screenSizeX/3), 20);
    QPixmap newMap(ui->Timeclock->width(), ui->Timeclock->height());
    newMap.fill(Qt::magenta);
    ui->Timeclock->setPixmap(newMap);
    newMap.fill(Qt::green);
    ui->Timefill->setPixmap(newMap);
    ui->Timefill->setMaximumWidth(ui->Timeclock->width());

    grid->addWidget(ui->Timeclock,7,1);
    grid->addWidget(ui->Timefill,7,1);
    //grid->addWidget(timeBar,7,1);

    // Setup Paused Menu

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
            rectArray[x][y]->setFlags(QGraphicsItem::ItemIsSelectable);
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
}

/*
 *  The Slots that the buttons use
 */
void MainWindow::menuPressed(){
    reset();
    scorePtr->resetScore();
    sframe->resetScoreBoard();
    shuffleButton->hide();
    pauseMenu->hide();
    mainMenu->show();

}

void MainWindow::pauseBack(){
    pauseMenu->hide();
    timer->start();
}

void MainWindow::pausedPressed(){
    pauseMenu->show();
    timer->stop();
}

void MainWindow::pauseSettingsPressed(){
    pauseMenu->hide();
    shuffleButton->hide();
    settingsMenu->show();
    connect(backToMenu2, SIGNAL(clicked()), this, SLOT(backToPause()) );
}

void MainWindow::backToPause(){
    settingsMenu->hide();
    mainMenu->hide();
    shuffleButton->show();
    pauseMenu->show();
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

void MainWindow::noSound(){
    if(soundCheck->isChecked()){
        soundCheck->setChecked(false);
        // Kill sound
    }
    else if(!soundCheck->isChecked()){
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

    // Mike Son update
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(timeSlot()));
    timer->start(200);//move to start game code
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


   multiplier = 1;

    scorePtr->updateScore((int) gatheredBlocks.size(), false , multiplier);
    sframe->update(scorePtr->getScore());
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
            if(blockVector[j]->getRowX() == blockVector[t]->getRowX() && blockVector[j]->getColY() > blockVector[t]->getColY())
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
        rectArray[blockVector[i]->getRowX()][blockVector[i]->getColY()]->setBrush(QBrush(colorPtr->getQColor(0), Qt::SolidPattern));
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
        int checkY = blockVector[i]->getColY() - 1;
        while(checkY >= 0)
        {
            if(!gameBoard[blockVector[i]->getRowX()][checkY]->getColoredBool())
            {
				//steal the color from other block onto ith block...
                blockVector[i]->setColor(gameBoard[blockVector[i]->getRowX()][checkY]->getColor());
                blockVector[i]->setColoredBool(false);
                rectArray[blockVector[i]->getRowX()][blockVector[i]->getColY()]->setBrush(QBrush(colorPtr->getQColor(blockVector[i]->getColor()), Qt::SolidPattern));
				//..and set the other block for a color change (including transition)
                gameBoard[blockVector[i]->getRowX()][checkY]->setColoredBool(true); //block needs to be changed later
                gameBoard[blockVector[i]->getRowX()][checkY]->setColor(0);
                rectArray[blockVector[i]->getRowX()][checkY]->setBrush(QBrush(colorPtr->getQColor(0),Qt::SolidPattern));
                blockVector.push_back(gameBoard[blockVector[i]->getRowX()][checkY]); //add block to end of vector
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
            rectArray[blockVector[i]->getRowX()][blockVector[i]->getColY()]->setBrush(QBrush(colorPtr->getQColor(tempColor), Qt::SolidPattern));
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
                break;
            case 2 : //bomb case
                blockVector = bombCollector(blockVector, blockVector[i]->getRowX(), blockVector[i]->getColY());
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


void MainWindow::timeSlot(){
x++;
if(x%5==0){
    currentTime--;
}
if(currentTime==-1){
    gameOver();
    close();
    return;
}
//ui->Timenum->setText(QString::number(currentTime));
ui->Timefill->setMaximumWidth(ui->Timefill->maximumWidth()-(ui->Timeclock->width()/300));
}

void MainWindow::gameOver(){
    timer->stop();
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

            rectArray[gameBoard[r1][c1]->getRowX()][gameBoard[r1][c1]->getColY()]->setBrush(QBrush(colorPtr->getQColor(gameBoard[r1][c1]->getColor()), Qt::SolidPattern));
            rectArray[gameBoard[r2][c2]->getRowX()][gameBoard[r2][c2]->getColY()]->setBrush(QBrush(colorPtr->getQColor(gameBoard[r2][c2]->getColor()), Qt::SolidPattern));
            // TO DO: need to swap bombs/multipler -> add getBomb method to Block
        }

    }


}
