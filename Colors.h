/** @author     Shannon Harwick
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
