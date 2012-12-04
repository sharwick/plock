/** @author     Shannon Harwick
  * @brief      A single color class is called which contains a set of color schemes.
  *             Color scheme 0 is the default, but the user is free to change to one of
  *             the other color schemes from within the Settings menu.
  *
  *             For every color scheme, color 0 is black.  This is the background color for every scheme.
  *
  *             The currently chosen scheme is the basis for the palette used by the text (in QLabels)
  *             and the QPushButtons.
  */



#include "Colors.h"

/** @author     Shannon Harwick
  * @brief    Creates an instance of the Color class and sets the color scheme to the requested scheme.
  * @param          The single input parameter is an integer from 0 to 4,
  *                 allowing user to choose a different scheme.
  *                 Color scheme 0 (default is not color-blind safe but shows the most variation in block colors)
  *                 All other schemes are color-blind safe and cover a range of different colors.
  *
  */
Colors::Colors(int scheme) {
    setScheme(scheme);
}

/** @author     Shannon Harwick
  * @brief  This method is called by the constructor.  Each scheme is represented by an integer (ranging from 0 to 4).
  *         The colors are stored in a single colorArray.  Each call to the setScheme() method updates this array.
  * @param  Input parameter n is an integer from 0 to 4, representing a unique color palette.
  * @return Void
  */
void Colors::setScheme(int n) {
    colorScheme = n;

    if (n==1) {
        colorArray[0] = QColor(0, 0, 0, 255);
        colorArray[1] = QColor(215,48,39,255);
        colorArray[2] = QColor(252,141,89,255);
        colorArray[3] = QColor(254,224,144,255);
        colorArray[4] = QColor(224,243,248,255);
        colorArray[5] = QColor(145,191,219,255);
        colorArray[6] = QColor(69,117,180,255);

        return;
    }

    if (n==2) {
        colorArray[0] = QColor(0, 0, 0, 255);
        colorArray[1] = QColor(178, 24, 43, 255);
        colorArray[2] = QColor(239, 138, 98,255);
        colorArray[3] = QColor(253, 219, 199,255);
        colorArray[4] = QColor(209, 229, 240,255);
        colorArray[5] = QColor(103, 169, 207,255);
        colorArray[6] = QColor(33, 102, 172,255);

        return;
    }

    if (n==3) {
        colorArray[0] = QColor(0, 0, 0, 255);
        colorArray[1] = QColor(118, 42, 131, 255);
        colorArray[2] = QColor(175, 141, 195,255);
        colorArray[3] = QColor(231, 212, 232,255);
        colorArray[4] = QColor(217, 240, 211,255);
        colorArray[5] = QColor(127, 191, 123,255);
        colorArray[6] = QColor(27, 120, 55,255);

        return;
    }

    if (n==4) {
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

    // default
    colorArray[0] = QColor(0, 0, 0, 255);
    colorArray[1] = QColor(228,26,28,255);
    colorArray[2] = QColor(55,126,184,255);
    colorArray[3] = QColor(77,175,74,255);
    colorArray[4] = QColor(152,78,163,255);
    colorArray[5] = QColor(255,255,51,255);
    colorArray[6] = QColor(255,127,0,255);

    return;
}


/** @author     Shannon Harwick
  * @brief  Determines the current color scheme being used.
  * @param  No input variable required.
  * @return An integer from 0 to 4, identifying the current color scheme being used.
  */
int Colors::getScheme() {
    return colorScheme;
}



/** @author     Shannon Harwick
  * @brief  This method takes an integer from 0 to 6 and obtains the relevant QColor of that index in the array of QColors defined by setScheme().
  * @param  Input parameter index is an integer from 0 to 6.  It identifies an index of the colorArray.
  * @return QColor
  */
QColor Colors::getQColor(int index){
    return colorArray[index];
}
