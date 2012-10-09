#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameBoard[0][0] = new Block(ui->pushButton6, 0, 0);
    gameBoard[1][0] = new Block(ui->pushButton7, 1, 0);
    gameBoard[2][0] = new Block(ui->pushButton8, 2, 0);
    gameBoard[0][1] = new Block(ui->pushButton3, 0, 1);
    gameBoard[1][1] = new Block(ui->pushButton4, 1, 1);
    gameBoard[2][1] = new Block(ui->pushButton5, 2, 1);
    gameBoard[0][2] = new Block(ui->pushButton0, 0, 2);
    gameBoard[1][2] = new Block(ui->pushButton1, 1, 2);
    gameBoard[2][2] = new Block(ui->pushButton2, 2, 2);

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(i != 0)
                gameBoard[i][j]->assignLeft(gameBoard[i-1][j]);
            if(j != 0)
                gameBoard[i][j]->assignUp(gameBoard[i][j-1]);
            if(i != 2)
                gameBoard[i][j]->assignRight(gameBoard[i+1][j]);
            if(j != 2)
                gameBoard[i][j]->assignDown(gameBoard[i][j+1]);
        }
    }

   // blockSignalMapper = new QSignalMapper(this);
    //blockSignalMapper->setMapping(ui->pushButton0, gameBoard[2][0]);
}

MainWindow::~MainWindow()
{
    delete ui;
}

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
                blockVector[i]->setColor(gameBoard[blockVector[i]->getRowX()][checkY]->getColor());
                blockVector[i]->setColoredBool(false);
                gameBoard[blockVector[i]->getRowX()][checkY]->setColor(0);
                gameBoard[blockVector[i]->getRowX()][checkY]->setColoredBool(true);
                blockVector.push_back(gameBoard[blockVector[i]->getRowX()][checkY]);
                break;
            }
            checkY--;
        }
        if(checkY < 0)
        {
            blockVector[i]->setColor((rand() % 6) + 1);
            blockVector[i]->setColoredBool(false);
        }
    }
}

void MainWindow::button0Clicked()
{
    int colorCheck = gameBoard[0][2]->getColor();
    if(colorCheck == gameBoard[1][2]->getColor() || colorCheck == gameBoard[0][1]->getColor())
        processMatch(gameBoard[0][2]);
}

void MainWindow::button1Clicked()
{
    int colorCheck = gameBoard[1][2]->getColor();
    if(colorCheck == gameBoard[0][2]->getColor() || colorCheck == gameBoard[2][2]->getColor()
            || colorCheck == gameBoard[1][1]->getColor())
        processMatch(gameBoard[1][2]);
}

void MainWindow::button2Clicked()
{
    int colorCheck = gameBoard[2][2]->getColor();
    if(colorCheck == gameBoard[2][1]->getColor() || colorCheck == gameBoard[1][2]->getColor())
        processMatch(gameBoard[2][2]);
}

void MainWindow::button3Clicked()
{
    int colorCheck = gameBoard[0][1]->getColor();
    if(colorCheck == gameBoard[0][0]->getColor() || colorCheck == gameBoard[1][1]->getColor()
            || colorCheck == gameBoard[0][2]->getColor())
        processMatch(gameBoard[0][1]);
}

void MainWindow::button4Clicked()
{
    int colorCheck = gameBoard[1][1]->getColor();
    if(colorCheck == gameBoard[0][1]->getColor() || colorCheck == gameBoard[1][0]->getColor()
            || colorCheck == gameBoard[1][2]->getColor() || colorCheck == gameBoard[2][1]->getColor())
        processMatch(gameBoard[1][1]);
}

void MainWindow::button5Clicked()
{
    int colorCheck = gameBoard[2][1]->getColor();
    if(colorCheck == gameBoard[2][0]->getColor() || colorCheck == gameBoard[1][1]->getColor()
            || colorCheck == gameBoard[2][2]->getColor())
        processMatch(gameBoard[2][1]);
}

void MainWindow::button6Clicked()
{
    int colorCheck = gameBoard[0][0]->getColor();
    if(colorCheck == gameBoard[0][1]->getColor() || colorCheck == gameBoard[1][0]->getColor())
        processMatch(gameBoard[0][0]);
}

void MainWindow::button7Clicked()
{
    int colorCheck = gameBoard[1][0]->getColor();
    if(colorCheck == gameBoard[0][0]->getColor() || colorCheck == gameBoard[1][1]->getColor()
            || colorCheck == gameBoard[2][0]->getColor())
        processMatch(gameBoard[1][0]);
}

void MainWindow::button8Clicked()
{
    int colorCheck = gameBoard[2][0]->getColor();
    if(colorCheck == gameBoard[1][0]->getColor() || colorCheck == gameBoard[2][1]->getColor())
        processMatch(gameBoard[2][0]);
}

void MainWindow::processMatch(Block* matchedBlock)
{
    vector<Block*> gatheredBlocks = matchedBlock->gatherBlocks(gatheredBlocks);
    gatheredBlocks = sortVector(gatheredBlocks);
    determineColor(gatheredBlocks);
}

void MainWindow::quitButtonClicked()
{
    close();
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
        if(i > 3) //needs to be changed for 7x9
            break;
        if(i < 0)
            continue;
        for(int j = (y - 1); j < (y + 2); j++)
        {
            if(j > 3 || j < 0) //needs to be changed for 7x9
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
