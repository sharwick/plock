/** @author     Shannon Harwick
  * @note       Note that this class is not operational yet because
  *             it can't be instantiated in the mainWindow and called
  *             in the Block class without restructuring the data.
  */


#ifndef COLORS_H
#define COLORS_H

#include <QColor>

class Colors {

public:
    int colorScheme;

    Colors(int); //now takes in color scheme val
    QColor colorArray[7]; //added to take colors out of Block
    void setScheme(int);
    int getScheme();
    QColor getQColor(int); //added with colorArray
};


#endif // COLORS_H
