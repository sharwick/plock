#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>

class myGraphicsScene : public QGraphicsScene
{
public:
    myGraphicsScene();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MYGRAPHICSSCENE_H
