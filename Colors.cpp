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

    if (n==1) {
        colorArray[0] = QColor(0, 0, 0, 255);
        colorArray[1] = QColor(178, 24, 43, 255);
        colorArray[2] = QColor(239, 138, 98,255);
        colorArray[3] = QColor(253, 219, 199,255);
        colorArray[4] = QColor(209, 229, 240,255);
        colorArray[5] = QColor(103, 169, 207,255);
        colorArray[6] = QColor(33, 102, 172,255);

        return;
    }

    if (n==2) {
        colorArray[0] = QColor(0, 0, 0, 255);
        colorArray[1] = QColor(118, 42, 131, 255);
        colorArray[2] = QColor(175, 141, 195,255);
        colorArray[3] = QColor(231, 212, 232,255);
        colorArray[4] = QColor(217, 240, 211,255);
        colorArray[5] = QColor(127, 191, 123,255);
        colorArray[6] = QColor(27, 120, 55,255);

        return;
    }

    if (n==3) {
        // Blues: probably not good for game, but maybe for menus
        colorArray[0] = QColor(0, 0, 0, 255);
        colorArray[1] = QColor(43, 140, 190,255);
        colorArray[2] = QColor(208, 209, 230,255);
        colorArray[3] = QColor(166, 189, 219,255);
        colorArray[4] = QColor(241, 238, 246, 255);
        colorArray[5] = QColor(4, 90, 141,255);
        colorArray[6] = QColor(116, 169, 207,255);

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
