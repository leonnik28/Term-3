#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include "mainwindow.h"
class MainInterface : public MainWindow
{
    Q_OBJECT

public:
    MainInterface(QWidget *parent = nullptr);
    ~MainInterface();
    void SearchCredit(QComboBox* nameBox);
    void createMenu();

public slots:
    void handleButtonClicked();

};
#endif // MAININTERFACE_H
