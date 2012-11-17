#include "myRectItem.h"
#include "mainwindow_UI.h"

myRectItem::myRectItem()
{
    bombPtr = new QGraphicsEllipseItem();
}

void myRectItem::mousePressEvent(QGraphicsSceneMouseEvent *){
    this->grabMouse();

}
void myRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *){
    this->grabMouse();
}

void myRectItem::setEllipse(QGraphicsEllipseItem *paramBomb){
    bombPtr = paramBomb;
}

void myRectItem::removeGraphObject(QGraphicsScene* theScene){
    if(bombPtr != 0){
        theScene->removeItem(bombPtr);
        bombPtr = 0;
        //bombPtr->setBrush(QBrush(Qt::yellow));
    }
}
