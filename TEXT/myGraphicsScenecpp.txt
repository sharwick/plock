#include "myGraphicsScene.h"
#include <QBrush>


myGraphicsScene::myGraphicsScene()
{

}

void myGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QBrush b = QBrush();
    b.setColor(Qt::red);
    this->setBackgroundBrush(b);
}
