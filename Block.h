/*
 *Block.h
 *
 *Version 2.0
 *  CHANGES: Constructor, bool member and functions, adjacent
 *  Block members and functions, RowX and ColY members and
 *  functions, gatherBlocks, removed determine color, and many
 *  mutator functions(see NOTE below).
 *
 *  CHANGES: assign'Direction' replaced set'Direction'.
 *  graphImage and mutator/accessor functions added.
 *  4 directional collectors (from special blocks) added.
 *
 *Author: Daniel Keasler
 *      Plock Team
 *
 *Constructor only needs to take in corresponding PushButton,
 *  color is randomly determined at start and adjacent Blocks
 *  are unknown.
 *
 *  ADDED: Constructor now takes in the 2D array indices from
 *  the 2D location of the Block.
 *
 *  NOTE: All of the mutator functions are public at the moment
 *  When we begin putting all of the pieces together and finalize
 *  class names, many of those mutator methods can be changed to
 *  private with friend of the other function that accesses it.
 */
#ifndef BLOCK
#define BLOCK

#include <QPushButton>
#include <vector>

using namespace std;

class Block{
public:
    Block(QPushButton*, int, int); //edit for QPushButton
    void setColor(int); //edit for QPushButton inheritance
    int getColor(); //edit for QPushButton inheritance
    bool getColoredBool();
    bool getMarkedBool();
    void setMarkedBool(bool);
    void setColoredBool(bool);
    void assignRight(Block*);
    void assignUp(Block*);
    void assignLeft(Block*);
    void assignDown(Block*);
    int getRowX();
    int getColY();
    void setGraphImage(int);
    int getGraphImage();
    vector<Block*> gatherBlocks(vector<Block*>);
    vector<Block*> upCollector(vector<Block*>);
    vector<Block*> rightCollector(vector<Block*>);
    vector<Block*> downCollector(vector<Block*>);
    vector<Block*> leftCollector(vector<Block*>);

private:
    QPushButton *pushButtonPtr; //removal for QPushButton inheritance
    bool markedBool;
    bool coloredBool;
    Block *rightBlockPtr;
    Block *upBlockPtr;
    Block *leftBlockPtr;
    Block *downBlockPtr;
    int color; //edit for QPushButton inheritance
    int RowX;
    int ColY;
    int graphImage;
};
	
#endif
