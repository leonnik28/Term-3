#ifndef TYPEOFCREDIT_H
#define TYPEOFCREDIT_H
#include "maininterface.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>

class TypeOfCredit
{
public:
    TypeOfCredit();

protected:
    double percent;
    bool isPreferential;
};

#endif // TYPEOFCREDIT_H
