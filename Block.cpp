<<<<<<< HEAD
/*ONE LINE ADDED; NO REAL CHANGES
=======
/*One line added; no real changes
 * One line added to show Mike git
 *One line change to show Devin git
>>>>>>> d165cd1cd67ed919b133224c03e005d80e6728b4
 *Block.cpp
 *
 *Version 2.1
 *Author: Daniel Keasler
 *      Plock Team
 *
 *  CHANGES: Constructor, bool member and functions, adjacent
 *  Block members and functions, RowX and ColY members and
 *  functions, gatherBlocks, removed determine color, and many
 *  mutator functions(see NOTE below).
 *
 *  CHANGES: minor mutator function changes to directional
 *  blocks, setGraphImage / getGraphImage, 4 directional
 *  block collectors from special blocks
 *
 *Constructor only needs push button, and push button should
 *  be instantiated at this point. 4 adjacent Blocks set to
 *  null to be assigned later. (rand() % 6) + 1 should return
 *  1 to 6 for color. Bool values are used to quickly check
 *	in the game algorithms for blocks already set for a color
 *	change and for blocks already marked in scoring count.
 *
 *  ADDED: Adjacent Blocks were changed to represent the changed
 *  simpler names. Also, coloredBool and markedBool were added
 *  for game algorithm purposes in scoring and coloring. RowX
 *  and ColY are the array indices from the 2D array. By having
 *  them as members of the Block class, the block vector can
 *  check for matches in a particular column from the actual
 *  block.
 *
 *  ADDED: graphImage = 0;
 */
//#include "Block.h"
#include "Block.h"
#include "Colors.h"
#include <QPixmap>
#include <QIcon>

using namespace std;
Block::Block(QPushButton *button, int rowSpot, int colSpot, int colorChoice, QColor firstColor){
	pushButtonPtr = button;
	rightBlockPtr = NULL;
	upBlockPtr = NULL;
	leftBlockPtr = NULL;
	downBlockPtr = NULL;
	coloredBool = false;
    markedBool = false;
    RowX = rowSpot;
    ColY = colSpot;
    graphImage = 0;
    setColor(colorChoice, firstColor);
}

/*
 *setColor takes in an int value and immediately assigns that
 *  to the Blocks color. QIcon can be used to show an icon on
 *  the push buttons, and QPixmap can create a push button
 *  sized map of a certain color, which can be used to create
 *  a QIcon. Qt::(insert color here) did not have orange and
 *  purple, to do later is fully create the color scheme and
 *  I can change these values to either RGB or actual locally
 *  stored Icons.
 *
 *  CHANGED: No switch needed. Color int is index in colorArray,
 *  QColor is color at that index.
 */
void Block::setColor(int _color, QColor firstColor){
    color = _color;
    QPixmap newMap(31, 31);
    newMap.fill(firstColor);

    // SH Update: TO DO: Move this outside the Block class (source= Color Brewer)
    //should be complete
    //int transparency=255;  // Alternatively: 127
	QIcon newIcon(newMap);
    pushButtonPtr->setIcon(newIcon);
}

/*
 *These next 4 functions take in pointers to Blocks and
 *  assign each to the appropriate adjacent Block pointer.
 *  A for loop will be needed after the entire 2D Block
 *  array has been initialized to ensure these pointers
 *  are not accidentally set to a NULL Block Pointer.
 *
 *  ADDED: Names were changed to a simpler format.
 *
 *  ADDED: Changed names to assign because setDown was
 *  QPushButton function
 */
void Block::assignRight(Block *tempBlock){
	rightBlockPtr = tempBlock;
}

void Block::assignUp(Block *tempBlock){
	upBlockPtr = tempBlock;
}

void Block::assignDown(Block *tempBlock){
	downBlockPtr = tempBlock;
}

void Block::assignLeft(Block *tempBlock){
	leftBlockPtr = tempBlock;
}

/*
 *Accessor function is a short cut to an equals method for color. Every color
 *  will have an associated number and similar colors will also have similar
 *  numbers in the color field.
 */
int Block::getColor(){
	return color;
}

/*
 *The following 4 methods are basic mutator and accessor functions for boolean values.
 *  These values are used to assure proper scoring and coloring.
 */
bool Block::getMarkedBool(){
	return markedBool;
}

bool Block::getColoredBool(){
	return coloredBool;
}

void Block::setMarkedBool(bool val){
	markedBool = val;
}

void Block::setColoredBool(bool val){
	coloredBool = val;
}

/*
 *Both of the following are simple accessor functions used to have array index
 *  through Block access.
 */
int Block::getRowX(){
    return RowX;
}

int Block::getColY(){
    return ColY;
}

/*
 *setMarkedBool and setColoredBool assure, respectively, that this particular
 *  Block does not call the gatherBlocks method in another part of the
 *  recursion and that it is colored properly. Blocks are added to vector to
 *  access later for total score and proper coloring, and these 3 statements
 *  occur first to avoid useless or unending recursion. The 4 if statements
 *  first check that each adjacent Block is not null, then check if the color
 *  matches the adjacent color, and then check to make sure the Blocks have
 *  not yet been selected in the recursion. If it passes those conditions,
 *  a new match is found and that Block needs to check its adjacent blocks.
 *  Block vector is returned through recursion to have access to all tiles
 *  found in the current match.
 */
vector<Block*> Block::gatherBlocks(vector<Block*> blockVector){
    setMarkedBool(true);
    setColoredBool(true);
    blockVector.push_back(this);
    if(upBlockPtr != NULL && upBlockPtr->getColor() == color && !upBlockPtr->getMarkedBool())
		blockVector = upBlockPtr->gatherBlocks(blockVector);
    if(rightBlockPtr != NULL && rightBlockPtr->getColor() == color && !rightBlockPtr->getMarkedBool())
		blockVector = rightBlockPtr->gatherBlocks(blockVector);
    if(downBlockPtr != NULL && downBlockPtr->getColor() == color && !downBlockPtr->getMarkedBool())
        blockVector = downBlockPtr->gatherBlocks(blockVector);
    if(leftBlockPtr != NULL && leftBlockPtr->getColor() == color && !leftBlockPtr->getMarkedBool())
        blockVector = leftBlockPtr->gatherBlocks(blockVector);
	return blockVector;
}

/*Next two functions serve as mutator and accessor method for our map
 *  to graphical images. Still a work in progress.
 */
int Block::getGraphImage(){
    return graphImage;
}

void Block::setGraphImage(int _graphImage){
    graphImage = _graphImage;
    //switch to assign a loaded graphics image? still a work in progress
}

/*Next four functions are recursive in respective direction.
 *  They keep going until relavant neighbor is null. Add block
 *  if !getMarkedBool(), or if block hasnt been marked. Same
 *  process to add and change bool flags. Return and pass
 *  blockVector through recursion.
 */
vector<Block*> Block::downCollector(vector<Block*> blockVector){
    if(!getMarkedBool())
    {
        setMarkedBool(true);
        setColoredBool(true);
        blockVector.push_back(this);
    }
    if(downBlockPtr != NULL)
        blockVector = downBlockPtr->downCollector(blockVector);
    return blockVector;
}

vector<Block*> Block::rightCollector(vector<Block*> blockVector){
    if(!getMarkedBool())
    {
        setMarkedBool(true);
        setColoredBool(true);
        blockVector.push_back(this);
    }
    if(rightBlockPtr != NULL)
        blockVector = rightBlockPtr->rightCollector(blockVector);
    return blockVector;
}

vector<Block*> Block::upCollector(vector<Block*> blockVector){
    if(!getMarkedBool())
    {
        setMarkedBool(true);
        setColoredBool(true);
        blockVector.push_back(this);
    }
    if(upBlockPtr != NULL)
        blockVector = upBlockPtr->upCollector(blockVector);
    return blockVector;
}

vector<Block*> Block::leftCollector(vector<Block*> blockVector){
    if(!getMarkedBool())
    {
        setMarkedBool(true);
        setColoredBool(true);
        blockVector.push_back(this);
    }
    if(leftBlockPtr != NULL)
        blockVector = leftBlockPtr->leftCollector(blockVector);
    return blockVector;
}
