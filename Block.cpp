/**
 * @author Daniel Keasler
 * @copyright Blockstar
 * @class block block.h "block.h"
 * @brief Underlying data structures and algorithms for game play.
 * @description The Block class contains integers and a series of "adjacent" pointers for easy comparisons used in the game play algorithms
 */
/*
 *One line added; no real changes
 * One line added to show Mike git
 *One line change to show Devin git
 *Block.cpp
 *
 *Version 2.3
 *Author: Daniel Keasler
 *      Plock Team
 *
 *Constructor only needs push button, and push button should
 *  be instantiated at this point. 4 adjacent Blocks set to
 *  null to be assigned later. (rand() % 6) + 1 should return
 *  1 to 6 for color. Bool values are used to quickly check
 *  in the game algorithms for blocks already set for a color
 *  change and for blocks already marked in scoring count.
 *
 *  ADDED: Adjacent Blocks were changed to represent the changed
 *  simpler names. Also, coloredBool and markedBool were added
 *  for game algorithm purposes in scoring and coloring. RowX
 *  and ColY are the array indices from the 2D array. By having
 *  them as members of the Block class, the block vector can
 *  check for matches in a particular column from the actual
 *  block.
 *
 *  CHANGED: minor mutator function changes to directional
 *  blocks, setGraphImage / getGraphImage, 4 directional
 *  block collectors from special blocks
 *
 *  ADDED: graphImage = 0;
 *
 *  CHANGED: setColor only contains int value for comparisons
 *
 *  CHANGED: push butons have been removed from Blocks 
 *  (constructor, algorithms don't have push button)
 *
 *  ADDED: foundMatch to process initial matching. 
 */

#include "Block.h"
//#include "Colors.h"

using namespace std;
/**
 * @brief Block::Block
 * @param xSpot int X Coordinate on game board, also array index
 * @param ySpot int Y Coordinate on game board, also array index
 * @param colorChoice Array Index of QColor in Colors.cpp, also used for adjacent color comparisons
 * @brief Constructor assigns adjacent pointers to 0, bools to false, params to Coords, graph image to 0, and sends colorChoice to setColor
 */
Block::Block(int xSpot, int ySpot, int colorChoice){
    rightBlockPtr = 0;
    upBlockPtr = 0;
    leftBlockPtr = 0;
    downBlockPtr = 0;
    coloredBool = false;
    markedBool = false;
    CoordX = xSpot;
    CoordY = ySpot;
    graphImage = 0;
    setColor(colorChoice);
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
 *
 *  CHANGED: setColor only sets integer value for color 
 *  comparisons
 */
/**
 * @author Daniel Keasler
 * @param _color int Array Index in Colors.cpp
 * @brief setColor updates graphical color changes with corresponding integer index
 */
void Block::setColor(int _color){
    color = _color;
    //QPixmap newMap(31, 31);
    //newMap.fill(firstColor);

    // SH Update: TO DO: Move this outside the Block class (source= Color Brewer)
    //should be complete
    //int transparency=255;  // Alternatively: 127
	//QIcon newIcon(newMap);
    //pushButtonPtr->setIcon(newIcon);
}

/*
 *These next 4 functions take in pointers to Blocks and
 *  assign each to the appropriate adjacent Block pointer.
 *  A for loop will be needed after the entire 2D Block
 *  array has been initialized to ensure these pointers
 *  are not accidentally set to a NULL Block Pointer.
 *
 *  CHANGED: Pointer names were changed to a simpler format.
 *
 *  CHANGED: function names were changed to assign (from set)
 *  because setDown was a QPushButton function
 */
/**
 * @author Daniel Keasler
 * @brief Block::assignRight rightward adjacent pointer is assigned
 * @param tempBlock
 */
void Block::assignRight(Block *tempBlock){
	rightBlockPtr = tempBlock;
}
/**
 * @author Daniel Keasler
 * @brief Block::assignUp upward adjacent pointer is assigned
 * @param tempBlock
 */
void Block::assignUp(Block *tempBlock){
	upBlockPtr = tempBlock;
}
/**
 * @author Daniel Keasler
 * @brief Block::assignDown downward adjacent pointer is assigned
 * @param tempBlock
 */
void Block::assignDown(Block *tempBlock){
	downBlockPtr = tempBlock;
}
/**
 * @author Daniel Keasler
 * @brief Block::assignLeft leftward adjacent pointer is assigned
 * @param tempBlock
 */
void Block::assignLeft(Block *tempBlock){
	leftBlockPtr = tempBlock;
}

/*
 *Accessor function is a short cut to an equals method for color. Every color
 *  will have an associated number and similar colors will also have similar
 *  numbers in the color field.
 */
/**
 * @author Daniel Keasler
 * @brief Block::getColor
 * @return int color for easy color comparisons as an integer value
 */
int Block::getColor(){
	return color;
}

/*
 *The following 4 methods are basic mutator and accessor functions for boolean values.
 *  These values are used to assure proper scoring and coloring.
 */
/**
 * @author Daniel Keasler
 * @brief Block::getMarkedBool - used to determine if this block was collected for scoring yet
 * @return marked bool value
 */
bool Block::getMarkedBool(){
	return markedBool;
}
/**
 * @author Daniel Keasler
 * @brief Block::getColoredBool - used to determine if this block needs to be recolored
 * @return colored bool value
 */
bool Block::getColoredBool(){
	return coloredBool;
}
/**
 * @author Daniel Keasler
 * @brief Block::setMarkedBool
 * @param val
 * @description set to true once particular block is collected for scoring, set to false after all proper blocks have been collected
 */
void Block::setMarkedBool(bool val){
	markedBool = val;
}
/**
 * @author Daniel Keasler
 * @brief Block::setColoredBool
 * @param val
 * @description set to true once particular block needs a color change, set to false after this block has been recolored
 */
void Block::setColoredBool(bool val){
	coloredBool = val;
}

/*
 *Both of the following are simple accessor functions used to have array index
 *  through Block access.
 */
/**
 * @author Daniel Keasler
 * @brief Block::getCoordX - accessor function for Block's X coordinate
 * @return int x coordinate
 */
int Block::getCoordX(){
    return CoordX;
}
/**
 * @author Daniel Keasler
 * @brief Block::getCoordY - accessor function for Block's Y coordinate
 * @return int y coordinate
 */
int Block::getCoordY(){
    return CoordY;
}
/*
 *This function (in all 4 directions) checks if the neighbor is not 0,
 *  and then if their color value matches the calling Block's color 
 *  value. If so, it returns true. Otherwise false is returned at the
 *  end. 
 */
/**
 * @author Daniel Keasler
 * @brief Block::foundMatch - detects if adjacent block matches color
 * @return bool
 * @description Mouse event will call this function on clicked block, will return true if any adjacent pointer has an equivalent color value
 */
bool Block::foundMatch(){
    if(upBlockPtr != 0 && upBlockPtr->getColor() == getColor())
        return true;
    if(downBlockPtr != 0 && downBlockPtr->getColor() == getColor())
        return true;
    if(rightBlockPtr != 0 && rightBlockPtr->getColor() == getColor())
        return true;
    if(leftBlockPtr != 0 && leftBlockPtr->getColor() == getColor())
        return true;
    return false;
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
/**
 * @author Daniel Keasler
 * @brief Block::gatherBlocks - recursive function collecting matching adjacent blocks
 * @param blockVector
 * @return vector<Block*>
 * @description First three lines for algorithm use (is marked, needs color change, block is added to vector),
 *  then if neighbor exists, is not marked, and has same color, recursion expands to that block
 */
vector<Block*> Block::gatherBlocks(vector<Block*> blockVector){
    setMarkedBool(true);
    setColoredBool(true);
    blockVector.push_back(this);
    if(upBlockPtr != 0 && upBlockPtr->getColor() == color && !upBlockPtr->getMarkedBool())
		blockVector = upBlockPtr->gatherBlocks(blockVector);
    if(rightBlockPtr != 0 && rightBlockPtr->getColor() == color && !rightBlockPtr->getMarkedBool())
		blockVector = rightBlockPtr->gatherBlocks(blockVector);
    if(downBlockPtr != 0 && downBlockPtr->getColor() == color && !downBlockPtr->getMarkedBool())
        blockVector = downBlockPtr->gatherBlocks(blockVector);
    if(leftBlockPtr != 0 && leftBlockPtr->getColor() == color && !leftBlockPtr->getMarkedBool())
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
/**
 * @author Daniel Keasler
 * @brief Block::downCollector
 * @param blockVector
 * @return vector<Block*>
 * @note Not used in current game
 * @description would return collection of all down pointers from calling block in vector
 */
vector<Block*> Block::downCollector(vector<Block*> blockVector){
    if(!getMarkedBool())
    {
        setMarkedBool(true);
        setColoredBool(true);
        blockVector.push_back(this);
    }
    if(downBlockPtr != 0)
        blockVector = downBlockPtr->downCollector(blockVector);
    return blockVector;
}
/**
 * @author Daniel Keasler
 * @brief Block::rightCollector
 * @param blockVector
 * @return vector<Block*>
 * @note Not used in current game
 * @description would return collection of all right pointers from calling block in vector
 */
vector<Block*> Block::rightCollector(vector<Block*> blockVector){
    if(!getMarkedBool())
    {
        setMarkedBool(true);
        setColoredBool(true);
        blockVector.push_back(this);
    }
    if(rightBlockPtr != 0)
        blockVector = rightBlockPtr->rightCollector(blockVector);
    return blockVector;
}
/**
 * @author Daniel Keasler
 * @brief Block::upCollector
 * @param blockVector
 * @return vector<Block*>
 * @note Not used in current game
 * @description would return collection of all up pointers from calling block in vector
 */
vector<Block*> Block::upCollector(vector<Block*> blockVector){
    if(!getMarkedBool())
    {
        setMarkedBool(true);
        setColoredBool(true);
        blockVector.push_back(this);
    }
    if(upBlockPtr != 0)
        blockVector = upBlockPtr->upCollector(blockVector);
    return blockVector;
}
/**
 * @author Daniel Keasler
 * @brief Block::leftCollector
 * @param blockVector
 * @return vector<Block*>
 * @note Not used in current game
 * @description would return collection of all left pointers from calling block in vector
 */
vector<Block*> Block::leftCollector(vector<Block*> blockVector){
    if(!getMarkedBool())
    {
        setMarkedBool(true);
        setColoredBool(true);
        blockVector.push_back(this);
    }
    if(leftBlockPtr != 0)
        blockVector = leftBlockPtr->leftCollector(blockVector);
    return blockVector;
}
