#include "maininterface.h"
#include "ui_mainwindow.h"

MainInterface::MainInterface(QWidget *parent)
{
    connect(ui->selectStyleButton, &QPushButton::clicked, this, &MainInterface::handleButtonClicked);
    QObject::connect(ui->toolButton, &QToolButton::clicked, this, &MainInterface::createMenu);
}

MainInterface::~MainInterface()
{

}

void MainInterface::SearchCredit(QComboBox* nameBox){


    /*QObject::connect(&button, &QPushButton::clicked, [&comboBox]() {
        int index = comboBox.currentIndex();
        if (index == 0) {
            QMessageBox::information(nullptr, "Результат", "Правильно");
        } else if (index == 1) {
            QMessageBox::information(nullptr, "Результат", "Неправильно");
        }*/
}

void MainInterface::createMenu()
{
    // Создание меню
    QMenu menu;

    QAction action1("Кнопка 1");
    QAction action2("Кнопка 2");
    QAction action3("Кнопка 3");

    menu.addAction(&action1);
    menu.addAction(&action2);
    menu.addAction(&action3);

    // Показ меню
    QAction* selectedItem = menu.exec(QCursor::pos());
    if (selectedItem)
    {
        qDebug() << "Выбрано: " << selectedItem->text();
    }
}

void MainInterface::handleButtonClicked() {
    static bool isDark = false;
    if (isDark) {
        QApplication::setPalette(QApplication::style()->standardPalette());
        isDark = false;
    }
    else {
        QApplication::setStyle(QStyleFactory::create("Fusion"));
        QPalette darkPalette;
        darkPalette.setColor(QPalette::Window, QColor(53,53,53));
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Base, QColor(25,25,25));
        darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
        darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        darkPalette.setColor(QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Button, QColor(53,53,53));
        darkPalette.setColor(QPalette::ButtonText, Qt::white);
        darkPalette.setColor(QPalette::BrightText, Qt::red);
        darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        darkPalette.setColor(QPalette::HighlightedText, Qt::black);
        QApplication::setPalette(darkPalette);
        isDark = true;
    }

    // Перерисовываем все виджеты
    qApp->changeOverrideCursor(QCursor(Qt::WaitCursor));
    qApp->processEvents();
    qApp->setOverrideCursor(QCursor(Qt::ArrowCursor));
}
