#include "mainwindow.h"
#include "maininterface.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    //MainWindow window;
    MainInterface start;
    start.show();
    //window.ButtonStyle();
    //window.show();
    return app.exec();
}
