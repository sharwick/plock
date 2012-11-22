#ifndef MYRECTITEM_H
#define MYRECTITEM_H
//soon to potentially include graphobject.h
#include <QGraphicsRectItem>
//#include <QGraphicsEllipseItem>
//#include <QRectF>
#include <QGraphicsSimpleTextItem>

class myRectItem : public QGraphicsRectItem
{

public:
    myRectItem();
    QGraphicsSimpleTextItem* textPtr;
    void setTextItem(QGraphicsSimpleTextItem*);
    void removeGraphObject(bool);

protected:
   void mousePressEvent(QGraphicsSceneMouseEvent *);
   void mouseMoveEvent(QGraphicsSceneMouseEvent *);

};

#endif // MYRECTITEM_H
