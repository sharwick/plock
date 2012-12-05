/**
 * @author Daniel Keasler
 * @author Devin Rusnak
 * @copyright Blockstar 2012
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
    int graphImage;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *);

};
	
#endif
