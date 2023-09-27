#include "mainwindow.h"
#include "startprogram.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.ButtonStyle();
    window.show();

    return app.exec();
}
