#ifndef MYRECTITEM_H
#define MYRECTITEM_H

#include <QGraphicsRectItem>

class myRectItem : public QGraphicsRectItem
{

public:
    myRectItem();

protected:
   void mousePressEvent(QGraphicsSceneMouseEvent *);
   void mouseMoveEvent(QGraphicsSceneMouseEvent *);

};

#endif // MYRECTITEM_H
