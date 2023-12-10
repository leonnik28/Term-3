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

protected:
    Ui::MainWindow *ui;
    QVBoxLayout *scrollLayout;

private:
    void ComboBoxInit(QComboBox* nameBox, QString firstName, QString itemOne, QString itemTwo, QString itemThree);
    void ComboBoxInit(QComboBox* nameBox, QString firstName, QString itemOne, QString itemTwo, QString itemThree, QString itemFour);
    void ComboBoxCountMoney(QComboBox* nameBox, QString startName);
    void ComboBoxCountMoney(QComboBox* nameBox, QString startName, int maxCount);
    void CreateScrollLayout();
};
#endif // MAINWINDOW_H
