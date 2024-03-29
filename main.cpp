#include "mainwindow.h"
#include <stdlib.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    srand(unsigned(NULL));

    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.setOrientation(MainWindow::ScreenOrientationAuto);
    mainWindow.showExpanded();

    return app.exec();
}
