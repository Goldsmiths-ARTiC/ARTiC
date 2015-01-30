// main.cpp

#include <QApplication>
#include <QDesktopWidget>

#include "zwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window window;
    window.resize(window.sizeHint());

    window.setWindowTitle("ARTiC visualizer v0.1");

    window.showMaximized();
    return app.exec();
}
