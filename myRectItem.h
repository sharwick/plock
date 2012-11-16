#ifndef MYRECTITEM_H
#define MYRECTITEM_H
//soon to potentially include graphobject.h
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QRectF>

class myRectItem : public QGraphicsRectItem
{

public:
    myRectItem();
    QGraphicsEllipseItem *bombPtr;
    void setEllipse(QGraphicsEllipseItem*);
    void removeGraphObject(QGraphicsScene*);

protected:
   void mousePressEvent(QGraphicsSceneMouseEvent *);
   void mouseMoveEvent(QGraphicsSceneMouseEvent *);

};

#endif // MYRECTITEM_H
