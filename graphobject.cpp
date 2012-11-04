#include "graphobject.h"

GraphObject::GraphObject(int x, int y)
{
    coordX = x;
    coordY = y;
    vectorIndex = -1;
}

/*
 *When shuffle or flip functions are called, Graph Object is also swapped.
 * To reflect new location, moved function is called to update graph objects
 * new location.
 */
void GraphObject::moved(int x, int y){
    coordX = x;
    coordY = y;
}
/*
 *When scoring graph objects are plocked, the vector will be rearranged so
 * that end object and object to be removed are swapped (to do an erase).
 * If this was the end object, index will be set to -1. If it was swapped,
 * set to the new index.
 */
void GraphObject::changeIndex(int index){
    vectorIndex = index;
}

/*
 *Used to access graph object through myRectItem in main window vector when
 * x, y is known
 */
int GraphObject::getIndex(){
    return vectorIndex;
}
