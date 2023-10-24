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
    void OnButtonClicked();
    void handleButtonClicked();

protected:
    Ui::MainWindow *ui;

private:
    void ComboBoxInit(QComboBox* nameBox, QString firstName, QString itemOne, QString itemTwo, QString itemThree);
    void ComboBoxInit(QComboBox* nameBox, QString firstName, QString itemOne, QString itemTwo, QString itemThree, QString itemFour, QString itemFive);
    void ComboBoxCountMoney(QComboBox* nameBox, QString startName);
    void ComboBoxCountMoney(QComboBox* nameBox, QString startName, int maxCount);
};
#endif // MAINWINDOW_H
