#ifndef GRAPHOBJECT_H
#define GRAPHOBJECT_H
/*
 *Author: Daniel Keasler
 *      Plock Team
 *Each myRectItem will have a graph object.
 *Functions eventually included to null and assign pointers
 *coordX and Y needed for scoring ones
 *when assigned a scoring pointer, will also add graph object to vector
 *vectorIndex is coordX, coordY constant time access to scoring graph objects
 *  contained in a vector in mainwindow, will be -1 for all other graph objects
 *changeIndex called when a scoring object is plocked
 *moved is for shuffle and flip functions
 */

class GraphObject
{
public:
    GraphObject();
    //erase method for null pointers but may be easier to set all to 0 rather than if/else if/else if...
    //createPointer method to assign relavant pointer value, can be overloaded with different pointer parameters
    //create pointer could also take in graphImage as well as pointer, switch on graphImage to assign correct pointer

private:

    /*
     *Add pointer references here to QClass used to graphically represent bombs/scores/arrows etc
     */
};

#endif // GRAPHOBJECT_H
