/** @author     Shannon Harwick
  * @note       Note that this class is not operational yet because
  *             it can't be instantiated in the mainWindow and called
  *             in the Block class without restructuring the data.
  */



#include "Colors.h"

Colors::Colors(int scheme) {
    setScheme(scheme);
}

/*
 *DKeasler:
 *setScheme called from constructor. Same QColors but
 *  now stored in QColor array.
 */
void Colors::setScheme(int n) {
    colorScheme = n;
    if (n==0) {
        colorArray[0] = QColor(0, 0, 0, 255);
        colorArray[1] = QColor(215,48,39,255);
        colorArray[2] = QColor(252,141,89,255);
        colorArray[3] = QColor(254,224,144,255);
        colorArray[4] = QColor(224,243,248,255);
        colorArray[5] = QColor(145,191,219,255);
        colorArray[6] = QColor(69,117,180,255);

        return;
    }

    // default to n=0 scheme
    colorArray[0] = QColor(0, 0, 0, 255);
    colorArray[1] = QColor(215,48,39,255);
    colorArray[2] = QColor(252,141,89,255);
    colorArray[3] = QColor(254,224,144,255);
    colorArray[4] = QColor(224,243,248,255);
    colorArray[5] = QColor(145,191,219,255);
    colorArray[6] = QColor(69,117,180,255);
    return;
}


int Colors::getScheme() {
    return colorScheme;
}
/*
 *DKeasler:
 *getColor takes index and returns corresponding
 *  QColor
 */
QColor Colors::getQColor(int index){
    return colorArray[index];
}
