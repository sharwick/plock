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
    QColor color1;
    QColor color2;
    QColor color3;
    QColor color4;
    QColor color5;
    QColor color6;

    Colors();
    void setScheme(int);
    int getScheme();
};


#endif // COLORS_H
