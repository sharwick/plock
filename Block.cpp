/**
 * @author Daniel Keasler
 * @author Devin Rusnak
 * @copyright Blockstar
 * @brief Underlying data structures and algorithms for game play.
 * @description The Block class contains integers and a series of "adjacent" pointers for easy comparisons used in the game play algorithms
 */

#include "Block.h"

using namespace std;
/**
 * @brief Block::Block
 * @param xSpot int X Coordinate on game board, also array index
 * @param ySpot int Y Coordinate on game board, also array index
 * @param colorChoice Array Index of QColor in Colors.cpp, also used for adjacent color comparisons
 * @brief Constructor assigns adjacent pointers to 0, bools to false, params to Coords,
 *          graph image to 0, creates a new textPtr, and sends color to setColor
 */
Block::Block(int xSpot, int ySpot, int colorChoice, QColor colorChosen){
    rightBlockPtr = 0;
    upBlockPtr = 0;
    leftBlockPtr = 0;
    downBlockPtr = 0;
    coloredBool = false;
    markedBool = false;
    CoordX = xSpot;
    CoordY = ySpot;
    graphImage = 0;
    setColor(colorChoice, colorChosen);
    textPtr = new QGraphicsSimpleTextItem();
}
/**
 * @brief Block::mousePressEvent
 */
void Block::mousePressEvent(QGraphicsSceneMouseEvent *){
    this->grabMouse();
}
/**
 * @brief Block::mouseMoveEvent
 */
void Block::mouseMoveEvent(QGraphicsSceneMouseEvent *){
    //this->grabMouse();
}
/**
 * @author Daniel Keasler
 * @brief Block::setTextItem sets graph image and assigns pointer reference to textPtr
 * @param paramBomb
 * @return void
 */
void Block::setTextItem(QGraphicsSimpleTextItem* paramBomb){
    setGraphImage(2);
    textPtr = paramBomb;
}
/**
 * @author Daniel Keasler
 * @brief Block::removeGraphObject sets graph image and nulls / deletes pointer
 * @param endGame
 * @return void
 */
void Block::removeGraphObject(bool endGame){
    setGraphImage(0);
    //if not null, null and delete it
    if(textPtr != 0){
        //delete memory space at end of game
        if(endGame)
            delete textPtr;
        textPtr = 0;
    }
}

/**
 * @author Daniel Keasler
 * @param _color int Array Index in Colors.cpp
 * @brief setColor updates graphical color changes with QColor and color integer
 * @return void
 */
void Block::setColor(int _color, QColor colorChosen){
    color = _color;
    setBrush(QBrush(colorChosen, Qt::SolidPattern));
}

/**
 * @author Daniel Keasler
 * @brief Block::assignRight rightward adjacent pointer is assigned
 * @param tempBlock
 * @return void
 */
void Block::assignRight(Block *tempBlock){
	rightBlockPtr = tempBlock;
}
/**
 * @author Daniel Keasler
 * @brief Block::assignUp upward adjacent pointer is assigned
 * @param tempBlock
 * @return void
 */
void Block::assignUp(Block *tempBlock){
	upBlockPtr = tempBlock;
}
/**
 * @author Daniel Keasler
 * @brief Block::assignDown downward adjacent pointer is assigned
 * @param tempBlock
 * @return void
 */
void Block::assignDown(Block *tempBlock){
	downBlockPtr = tempBlock;
}
/**
 * @author Daniel Keasler
 * @brief Block::assignLeft leftward adjacent pointer is assigned
 * @param tempBlock
 * @return void
 */
void Block::assignLeft(Block *tempBlock){
	leftBlockPtr = tempBlock;
}

/**
 * @author Daniel Keasler
 * @brief Block::getColor returns color for easy color comparisons as an integer value
 * @return int
 */
int Block::getColor(){
	return color;
}

/**
 * @author Daniel Keasler
 * @brief Block::getMarkedBool - used to determine if this block was collected for scoring yet
 * @return bool
 */
bool Block::getMarkedBool(){
	return markedBool;
}
/**
 * @author Daniel Keasler
 * @brief Block::getColoredBool - used to determine if this block needs to be recolored
 * @return bool
 */
bool Block::getColoredBool(){
	return coloredBool;
}
/**
 * @author Daniel Keasler
 * @brief Block::setMarkedBool
 * @param val
 * @description set to true once particular block is collected for scoring, set to false after all proper blocks have been collected
 * @return void
 */
void Block::setMarkedBool(bool val){
	markedBool = val;
}
/**
 * @author Daniel Keasler
 * @brief Block::setColoredBool
 * @param val
 * @description set to true once particular block needs a color change, set to false after this block has been recolored
 * @return void
 */
void Block::setColoredBool(bool val){
	coloredBool = val;
}

/**
 * @author Daniel Keasler
 * @brief Block::getCoordX - accessor function for Block's X coordinate
 * @return int
 */
int Block::getCoordX(){
    return CoordX;
}
/**
 * @author Daniel Keasler
 * @brief Block::getCoordY - accessor function for Block's Y coordinate
 * @return int
 */
int Block::getCoordY(){
    return CoordY;
}

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

/**
 * @author Daniel Keasler
 * @brief Block::gatherBlocks - recursive function collecting matching adjacent blocks
 * @param blockVector
 * @return vector<Block*>
 * @description First three lines for algorithm use (is marked, needs color change, block is added to vector),
 *  then if neighbor exists, is not marked, and has same color, recursion expands to that block
 */
vector<Block*> Block::gatherBlocks(vector<Block*> blockVector){
    //bookkeeping for other game play algorithms
    setMarkedBool(true);
    setColoredBool(true);
    //add calling block to vector
    blockVector.push_back(this);
    //check 4 adjacent pointer references
    //if reference isn't null, and the color integers are equal, and the block hasn't been added yet,
    //  recursively expand to that block
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

/**
 * @author Daniel Keasler
 * @brief Block::getGraphImage returns value for integer comparison of special graphics objects
 * @return int
 */
int Block::getGraphImage(){
    return graphImage;
}
/**
 * @author Daniel Keasler
 * @brief Block::setGraphImage assign integer value of special graphics objects
 * @param _graphImage
 */
void Block::setGraphImage(int _graphImage){
    graphImage = _graphImage;
}

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
