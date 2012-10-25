#include "myRectItem.h"
#include <iostream>
#include "mainwindow.h"
using namespace std;
myRectItem::myRectItem()
{

}

void myRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    this->grabMouse();

}
void myRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    //this->ungrabMouse();
}
void myRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    this->grabMouse();
}


