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


    setupWindow();
    setupInterface();
    setupBlocks();

    // Mike Son update
        timer = new QTimer(this);
        timer->start(200);//move to start game code
        connect(timer, SIGNAL(timeout()),this, SLOT(timeSlot()));

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
    int tempSizeY = screenSizeY * .8;
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


    // Shuffle Button
    shuffleButton = new QPushButton("Shuffle",this);
    shuffleButton->setFixedSize(blockSize ,blockSize);
    connect(shuffleButton, SIGNAL(clicked()),this, SLOT(shufflePressed()));
    grid->addWidget(shuffleButton,1,2);

    // Menu Button
    menuButton = new QPushButton("Menu",this);
    menuButton->setFixedSize(blockSize ,blockSize);
    connect(menuButton, SIGNAL(clicked()),this, SLOT(menuPressed()));
    grid->addWidget(menuButton,1,3);

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
            theScene->addItem(rectArray[x][y]);
        }
    }

} // End setupBlocks()

void MainWindow::mousePressEvent(QMouseEvent *event){
    int offset = screenSizeY * 0.15;

    xPos = event->x() / blockSize;
    yPos = (event->y() - offset) / blockSize;
/*
 *Tried to put following code in blockPressed, but it was already included somewhere else.
 *Code can be moved as needed as long as it is in mainwindow_UI.cpp
    Block* tempCheck = gameBoard[xPos][yPos];
    if(tempCheck->getRowX() != 0 && tempCheck->getColor() == gameBoard[xPos - 1][yPos]->getColor())
        processMatch(tempCheck);
    else if(tempCheck->getRowX() != boardSizeX && tempCheck->getColor() == gameBoard[xPos + 1][yPos]->getColor())
        processMatch(tempCheck);
    else if(tempCheck->getColY() != 0 && tempCheck->getColor() == gameBoard[xPos][yPos - 1]->getColor())
        processMatch(tempCheck);
    else if(tempCheck->getColY() != boardSizeY && tempCheck->getColor() == gameBoard[xPos][yPos + 1]->getColor())
        processMatch(tempCheck);
*/
    emit blockPressed(xPos, yPos);
}

void MainWindow::menuPressed(){
    reset();
    scorePtr->resetScore();
    sframe->resetScoreBoard();
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

   // int multiplier;
   // multiplier = 1;

   // scorePtr->updateScore((int) gatheredBlocks.size(), false , multiplier);
   // scoreLCD->display(scorePtr->getScore());
   // sframe->update(scorePtr->getScore());
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
                int tempX;
                tempX = blockVector[i]->getRowX();
                blockVector[i]->setColor(gameBoard[tempX][checkY]->getColor());
                blockVector[i]->setColoredBool(false);
                gameBoard[tempX][checkY]->setColor(0);
                gameBoard[tempX][checkY]->setColoredBool(true);
                blockVector.push_back(gameBoard[tempX][checkY]);
                break;
            }
            checkY--;
        }
        if(checkY < 0)
        {
            int tempColor;
            tempColor = (rand() % 6) + 1;
            blockVector[i]->setColor(tempColor);
            blockVector[i]->setColoredBool(false);
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
ui->Timenum->setText(QString::number(currentTime));
ui->Timefill->setMaximumWidth(ui->Timefill->maximumWidth()-(ui->Timeclock->width()/300));
}

void MainWindow::gameOver(){
    timer->stop();
}

void MainWindow::shufflePressed() {
    // perform Nswaps swaps, passing colors/bombs/multipliers
    int Nswaps, i;
    Nswaps=boardSizeX*boardSizeY;

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

        // TO DO: need to swap bombs/multipler -> add getBomb method to Block
    }




}
