#include "mainwindow.h"
#include "maininterface.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ComboBoxInit(ui->choiceBankBox, "Банк", "Альфа", "Приор", "Белинвест");
    ComboBoxInit(ui->reasonOfCreditBox, "Причина", "Машина", "Квартира", "Айфон", "Дом", "Бизнес");
    ComboBoxCountMoney(ui->sumCreditBox, "Сумма кредита");
    ComboBoxCountMoney(ui->sumSalaryBox, "Ваша ЗП");
    ComboBoxCountMoney(ui->timePayoutBox, "Время выплаты (в месяцах)");
    //QObject::connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::handleButtonClicked);

    //start.SearchCredit(ui->choiceBank);
    //start.ComboBoxCountMoney(ui->comboBox_4, "ЛОХ");
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

void MainWindow::ComboBoxInit(QComboBox* nameBox, QString firstName, QString itemOne, QString itemTwo, QString itemThree, QString itemFour, QString itemFive){
    nameBox->addItem(firstName);
    nameBox->setItemData(nameBox->count() - 1, false, Qt::UserRole - 1);  // Делаем элемент недоступным
    nameBox->addItem(itemOne);
    nameBox->addItem(itemTwo);
    nameBox->addItem(itemThree);
    nameBox->addItem(itemFour);
    nameBox->addItem(itemFive);
}

void MainWindow::ComboBoxCountMoney(QComboBox* nameBox, QString startName){
    nameBox->setEditable(true);
    QLineEdit *lineEdit = new QLineEdit(nameBox);
    nameBox->setLineEdit(lineEdit);
    nameBox->lineEdit()->setPlaceholderText(startName);
}

void MainWindow::ComboBoxCountMoney(QComboBox* nameBox, QString startName, int maxCount){
    nameBox->setEditable(true);
    QLineEdit *lineEdit = new QLineEdit(nameBox);
    nameBox->setLineEdit(lineEdit);
    nameBox->lineEdit()->setPlaceholderText(startName);

    /*connect(lineEdit, &QLineEdit::editingFinished, [=]() {
        bool ok;
        int enteredValue = lineEdit->text().toInt(&ok);

        if (!ok || enteredValue > maxCount) {
            // Введенное значение либо не является числом, либо превышает максимально допустимое значение
            lineEdit->setText(QString::number(maxCount));
        }
    });*/
}

void MainWindow::handleButtonClicked() {
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

/*void MainWindow::Login(QWidget *parent) {
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
}*/

