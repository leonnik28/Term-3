#include "mainwindow.h"
#include "maininterface.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    ComboBoxInit(ui->choiceBankBox, "Банк", "Альфа", "Приор", "Белинвест");
    ComboBoxInit(ui->typeOfCreditBox, "Тип кредита", "Кредит", "Рассрочка", "Лизинг", "Микрозайм");
    ComboBoxCountMoney(ui->sumCreditBox, "Сумма кредита", 1000000);
    ComboBoxCountMoney(ui->percentCreditBox, "Процент", 30);
    ComboBoxCountMoney(ui->timePayoutBox, "Время выплаты", 480);

    ComboBoxInit(ui->reasonBox, "Причина", "Машина", "Квартира", "Дом");
    ui->reasonBox->setVisible(false);
    QObject::connect(ui->typeOfCreditBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]()
        {
            if(ui->typeOfCreditBox->currentText() == "Лизинг")
            {
                ui->reasonBox->setVisible(true);
            }
            else
            {
                ui->reasonBox->setVisible(false);
            }
        });

    ComboBoxCountMoney(ui->paymentBox, "Штраф за задержку", 50000);
    ui->paymentBox->setVisible(false);
    QObject::connect(ui->typeOfCreditBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]()
    {
        if(ui->typeOfCreditBox->currentText() == "Микрозайм")
            {
            ui->paymentBox->setVisible(true);
        }
        else
        {
            ui->paymentBox->setVisible(false);
        }
    });

    CreateScrollLayout();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::ComboBoxInit(QComboBox* nameBox, QString firstName, QString itemOne, QString itemTwo, QString itemThree){
    nameBox->addItem(firstName);
    nameBox->setItemData(nameBox->count() - 1, false, Qt::UserRole - 1);  // Делаем элемент недоступным
    nameBox->addItem(itemOne);
    nameBox->addItem(itemTwo);
    nameBox->addItem(itemThree);
}

void MainWindow::ComboBoxInit(QComboBox* nameBox, QString firstName, QString itemOne, QString itemTwo, QString itemThree, QString itemFour){
    nameBox->addItem(firstName);
    nameBox->setItemData(nameBox->count() - 1, false, Qt::UserRole - 1);  // Делаем элемент недоступным
    nameBox->addItem(itemOne);
    nameBox->addItem(itemTwo);
    nameBox->addItem(itemThree);
    nameBox->addItem(itemFour);
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

    connect(lineEdit, &QLineEdit::editingFinished, [=]() {
        bool ok;
        int enteredValue = lineEdit->text().toInt(&ok);

        if (!ok || enteredValue > maxCount) {
            lineEdit->setText(QString::number(maxCount));
        }
    });
}

void MainWindow::CreateScrollLayout(){

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget *scrollWidget = new QWidget;
    scrollArea->setWidget(scrollWidget);

    scrollLayout = new QVBoxLayout(scrollWidget);
    scrollWidget->setLayout(scrollLayout);

    scrollArea->setFixedSize(700, 400);
    scrollArea->move(120,70);
}
