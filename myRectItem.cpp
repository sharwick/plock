/** @author Devin Rusnak
 *  @author Daniel Keasler
 *  @copyright Blockstar 2012
 *  @class myRectItem myRectItem.h "myRectItem.h"
 *  @extends QGraphicsRectItem
 *  @brief Custom QGraphicsRectItem
 *
 *  A custom QGraphicsRectItem that has specific methods to handle the mouse clicks and bomb images.
 */

#include "myRectItem.h"
#include "mainwindow_UI.h"

/**
 * @brief myRectItem::myRectItem
 */
myRectItem::myRectItem()
{
    bombPtr = new QGraphicsEllipseItem();
}

/**
 * @brief myRectItem::mousePressEvent
 */
void myRectItem::mousePressEvent(QGraphicsSceneMouseEvent *){
    this->grabMouse();

}

/**
 * @brief myRectItem::mouseMoveEvent
 */
void myRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *){
    this->grabMouse();
}

/**
 * @brief myRectItem::setEllipse
 * @param paramBomb
 */
void myRectItem::setEllipse(QGraphicsEllipseItem *paramBomb){
    bombPtr = paramBomb;
}

/**
 * @brief myRectItem::removeGraphObject
 * @param theScene
 */
void myRectItem::removeGraphObject(QGraphicsScene* theScene){
    if(bombPtr != 0){
        theScene->removeItem(bombPtr);
        bombPtr = 0;
        //bombPtr->setBrush(QBrush(Qt::yellow));
    }
}
