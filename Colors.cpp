/** @author     Shannon Harwick
  * @note       Note that this class is not operational yet because
  *             it can't be instantiated in the mainWindow and called
  *             in the Block class without restructuring the data.
  */



#include "Colors.h"

Colors::Colors() {
    colorScheme=0;
}

void Colors::setScheme(int n) {
    if (n==0) {
        color1=QColor(215,48,39,0);
        color2=QColor(252,141,89,0);
        color3=QColor(254,224,144,0);
        color4=QColor(224,243,248,0);
        color5=QColor(145,191,219,0);
        color6=QColor(69,117,180,0);

        return;
    }

    // default to n=0 scheme
    color1=QColor(215,48,39,0);
    color2=QColor(252,141,89,0);
    color3=QColor(254,224,144,0);
    color4=QColor(224,243,248,0);
    color5=QColor(145,191,219,0);
    color6=QColor(69,117,180,0);
    return;
}


int Colors::getScheme() {
    return colorScheme;
}
