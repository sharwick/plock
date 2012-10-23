#ifndef MYRECTITEM_H
#define MYRECTITEM_H

#include <QGraphicsRectItem>

class myRectItem : public QGraphicsRectItem
{

public:
    myRectItem();

    void setX(int);
    void setY(int);
    int getX();
    int getY();

protected:
   void mousePressEvent(QGraphicsSceneMouseEvent *event);
   void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
   void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
   // Variables
   int x, y;

};

#endif // MYRECTITEM_H
