#include "myRectItem.h"
#include "mainwindow.h"

myRectItem::myRectItem()
{

}

void myRectItem::mousePressEvent(QGraphicsSceneMouseEvent *){
    this->grabMouse();

}
void myRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *){
    this->grabMouse();
}


