#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //void SearchCredit();
    void Login(QWidget *parent = nullptr);
    void ButtonStyle();

private:
    Ui::MainWindow *ui;
    void ComboBoxInit(QComboBox* nameBox, QString firstName, QString itemOne, QString itemTwo, QString itemThree);
    void ComboBoxCountMoney(QComboBox* nameBox, QString startName);
};

#endif // MAINWINDOW_H
