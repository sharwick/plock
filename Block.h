/**
 * @author Daniel Keasler
 * @author Devin Rusnak
 * @copyright Blockstar 2012
 */
/*
 *Block.h
 *
 *Author: Daniel Keasler
 *      Plock Team
 *Version 2.3
 * 
 *Constructor only needs to take in corresponding PushButton,
 *  color is randomly determined at start and adjacent Blocks
 *  are unknown.
 *
 *  CHANGED: Constructor, bool member and functions, adjacent
 *  Block members and functions, RowX and ColY members and
 *  functions, gatherBlocks, removed determine color, and many
 *  mutator functions(see NOTE below).
 *
 *  CHANGED: assign'Direction' replaced set'Direction'.
 *  graphImage and mutator/accessor functions added.
 *  4 directional collectors (from special blocks) added.
 *  
 *  ADDED: Constructor now takes in the 2D array indices from
 *  the 2D location of the Block.
 *
 *  CHANGED: setColor now takes in a QColor (obtained from colors).
 *  No switch needed. Constructor changed to reflect new setColor.
 *  Takes in int color value from caller and QColor
 *
 *  CHANGED: push buttons removed. 
 *
 *  CHANGED: added foundMatch function, setColor only assigns
 *  integer value for comparisons. 
 *
 *  NOTE: All of the mutator functions are public at the moment
 *  When we begin putting all of the pieces together and finalize
 *  class names, many of those mutator methods can be changed to
 *  private with friend of the other function that accesses it.
 */
#ifndef BLOCK
#define BLOCK

#include <vector>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QBrush>

using namespace std;

class Block : public QGraphicsRectItem{
public:
    Block(int, int, int, QColor);
    void setColor(int, QColor);
    int getColor(); 
    bool getColoredBool();
    bool getMarkedBool();
    void setMarkedBool(bool);
    void setColoredBool(bool);
    void assignRight(Block*);
    void assignUp(Block*);
    void assignLeft(Block*);
    void assignDown(Block*);
    int getCoordX();
    int getCoordY();
    void setGraphImage(int);
    int getGraphImage();
    bool foundMatch();
    vector<Block*> gatherBlocks(vector<Block*>);
    vector<Block*> upCollector(vector<Block*>);
    vector<Block*> rightCollector(vector<Block*>);
    vector<Block*> downCollector(vector<Block*>);
    vector<Block*> leftCollector(vector<Block*>);

    QGraphicsSimpleTextItem* textPtr;
    void setTextItem(QGraphicsSimpleTextItem*);
    void removeGraphObject(bool);

private:
    bool markedBool;
    bool coloredBool;
    Block *rightBlockPtr;
    Block *upBlockPtr;
    Block *leftBlockPtr;
    Block *downBlockPtr;
    int color; 
    int CoordX;
    int CoordY;
    int graphImage; //may change based on implementation of graph Image

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *);

};
	
#endif
