#include "LoginDialog.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>
#include <QCryptographicHash>
#include <QLabel>
#include <QComboBox>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent){
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *usernameLabel = new QLabel(tr("Username"), this);
    QLabel *passwordLabel = new QLabel(tr("Password"), this);
    QLabel *noAccountLabel = new QLabel(tr("If you don't have an account"), this);
    m_usernameLineEdit = new QLineEdit(this);
    m_passwordLineEdit = new QLineEdit(this);
    m_passwordLineEdit->setEchoMode(QLineEdit::Password);

    usernameLabel->setStyleSheet("background-color: lightgray;");
    passwordLabel->setStyleSheet("background-color: lightgray;");

    QComboBox *userTypeComboBox = new QComboBox(this);
    userTypeComboBox->addItem(tr("Студент"));
    userTypeComboBox->addItem(tr("Ребенок"));
    userTypeComboBox->addItem(tr("Пенсионер"));
    userTypeComboBox->addItem(tr("Рабочий"));
    userTypeComboBox->hide(); // Скрыть combobox при инициализации

    QPushButton *loginButton = new QPushButton(tr("Login"), this);
    loginButton->setStyleSheet("border: 1px solid black;");
    QPushButton *createAccountButton = new QPushButton(tr("Create Account"), this);
    createAccountButton->setStyleSheet("border: 1px solid black;");


    layout->addWidget(usernameLabel);
    layout->addWidget(m_usernameLineEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(m_passwordLineEdit);
    layout->addWidget(userTypeComboBox);
    layout->addWidget(loginButton);
    layout->addWidget(noAccountLabel);
    layout->addWidget(createAccountButton);
    layout->setAlignment(Qt::AlignCenter);

    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::handleLogin);
    connect(createAccountButton, &QPushButton::clicked, this, [this, userTypeComboBox, loginButton, createAccountButton, noAccountLabel]()
        {
            if (userTypeComboBox->isHidden()) {
                userTypeComboBox->show(); // Показать combobox при нажатии на "Создать аккаунт"
                loginButton->hide(); // Скрыть кнопку "Войти" при нажатии на "Создать аккаунт"
                noAccountLabel->hide();
                createAccountButton->setStyleSheet("background-color: lightgray;"); // Изменить стиль кнопки "Создать аккаунт"
            } else {
                handleCreateAccount(userTypeComboBox->currentText());
                accept();
            }
        });

    auto resetUI =(
            [this, userTypeComboBox, loginButton, noAccountLabel, createAccountButton]
                {
                userTypeComboBox->hide();
                loginButton->show();
                noAccountLabel->show();
                createAccountButton->setStyleSheet("border: 1px solid black;");
                m_usernameLineEdit->clear();
                m_passwordLineEdit->clear();
    });

    connect(this, &QDialog::rejected, this, resetUI); // Сбросить все при закрытии окна
    connect(this, &QDialog::accepted, this, resetUI); // Сбросить все при принятии диалога

    setLayout(layout);
    setFixedSize(300, 300);
    setStyleSheet("background-color: white;");
}



void LoginDialog::handleLogin() {
    User currentUser(m_usernameLineEdit->text(), m_passwordLineEdit->text());

    if (currentUser.checkCredentials() == UserType::Admin) {
        emit adminLogin(m_usernameLineEdit->text(), m_passwordLineEdit->text(), currentUser.getUserType(m_usernameLineEdit->text()));
        accept();
    }
    else {
        emit disableAdminMode();
    }
    if(currentUser.checkCredentials() == UserType::Error) {
        QMessageBox::warning(this, tr("Error"), tr("Invalid username or password."));
        accept();
    }
    else{
        emit userLogin(m_usernameLineEdit->text(), m_passwordLineEdit->text(), currentUser.getUserType(m_usernameLineEdit->text()));
        accept();
    }
}

void LoginDialog::handleCreateAccount(QString userType) {
    UserType type = UserType::Error;

    if (userType == "Студент") {
        type = UserType::Student;
    } else if (userType == "Админ") {
        type = UserType::Admin;
    } else if (userType == "Ребенок") {
        type = UserType::Child;
    } else if (userType == "Пенсионер") {
        type = UserType::Pensioner;
    } else if (userType == "Рабочий") {
        type = UserType::Worker;
    }

    try {
        User newUser(m_usernameLineEdit->text(), m_passwordLineEdit->text(), type);
        newUser.createUser();
        QMessageBox::information(this, tr("Success"), tr("Account created successfully."));
    } catch (const LoanException& e) {
        QMessageBox::warning(this, tr("Error"), tr(e.what()));
    }
}

