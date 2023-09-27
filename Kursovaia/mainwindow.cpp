#include "mainwindow.h"
#include "startprogram.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    StartProgram start;
    ComboBoxInit(ui->choiceBank, "Банк", "Альфа", "Приор", "Белинвест");
    ComboBoxCountMoney(ui->comboBox_4, "Сумма");
    start.SearchCredit(ui->choiceBank);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ComboBoxInit(QComboBox* nameBox, QString firstName, QString itemOne, QString itemTwo, QString itemThree){
    nameBox->addItem(firstName);
    nameBox->setItemData(nameBox->count() - 1, false, Qt::UserRole - 1);  // Делаем элемент недоступным
    nameBox->addItem(itemOne);
    nameBox->addItem(itemTwo);
    nameBox->addItem(itemThree);
}

void MainWindow::ComboBoxCountMoney(QComboBox* nameBox, QString startName){
    nameBox->setEditable(true);
    QLineEdit *lineEdit = new QLineEdit(nameBox);
    nameBox->setLineEdit(lineEdit);
    nameBox->lineEdit()->setPlaceholderText(startName);
}

/*void MainWindow::SearchCredit(){

    QObject::connect(&button, &QPushButton::clicked, [&comboBox]() {
        int index = comboBox.currentIndex();
        if (index == 0) {
            QMessageBox::information(nullptr, "Результат", "Правильно");
        } else if (index == 1) {
            QMessageBox::information(nullptr, "Результат", "Неправильно");
        }

    QObject::connect(&button, &QPushButton::clicked, [&comboBox]() {
        QString text = comboBox.currentText();
        int value = text.toInt();
        int result = value + 1000;
        QMessageBox::information(nullptr, "Результат", "Результат: " + QString::number(result));
    });
}*/


void MainWindow::ButtonStyle(){

    connect(ui->pushButton, &QPushButton::clicked, this, [=]() {
        ui->pushButton->setStyleSheet("background-color: red");
    });
}

void MainWindow::Login(QWidget *parent) {
    QLabel *usernameLabel = new QLabel("Username:");
    QLabel *passwordLabel = new QLabel("Password:");
    QLineEdit *usernameEdit = new QLineEdit;
    QLineEdit *passwordEdit = new QLineEdit;
    passwordEdit->setEchoMode(QLineEdit::Password);
    QPushButton *loginButton = new QPushButton("Login");

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(usernameLabel, usernameEdit);
    formLayout->addRow(passwordLabel, passwordEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(loginButton);

    QWidget *loginWidget = new QWidget;
    loginWidget->setLayout(mainLayout);

    QObject::connect(loginButton, &QPushButton::clicked, [usernameEdit, passwordEdit]() {
        QString username = usernameEdit->text();
        QString password = passwordEdit->text();
        if (username == "admin" && password == "password") {
            QMessageBox::information(nullptr, "Login", "Login successful!");
        } else {
            QMessageBox::warning(nullptr, "Login", "Invalid username or password!");
        }
    });

    //loginWidget->show();
}

