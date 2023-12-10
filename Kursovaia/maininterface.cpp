#include "maininterface.h"
#include "ui_mainwindow.h"
#include "credit.h"
#include "installmentplan.h"
#include "leasing.h"
#include "microloan.h"
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>

MainInterface::MainInterface(){
    QPushButton* searchButton = new QPushButton("Search Credit", this);
    searchButton->setFixedSize(100, 60);

    QObject::connect(searchButton, &QPushButton::clicked, this, &MainInterface::searchCredit);

    QObject::connect(ui->infoUserButton, &QPushButton::clicked, this, &MainInterface::displayUserInfo);
    QObject::connect(ui->loginButton, &QPushButton::clicked, this, &MainInterface::displayLoginDialog);

    loginDialog = new LoginDialog(this);
    QObject::connect(loginDialog, &LoginDialog::adminLogin, this, &MainInterface::initializeAdminMode);
    QObject::connect(loginDialog, &LoginDialog::disableAdminMode, this, &MainInterface::removeAdminControls);
    QObject::connect(loginDialog, &LoginDialog::userLogin, this, &MainInterface::initializeUserAndRefreshLoans);
}

MainInterface::~MainInterface(){

}

void MainInterface::searchCredit() {
    ClearLayout(scrollLayout);

    QString creditType = ui->typeOfCreditBox->currentText();
    UserType currentUserType = currentUser.getUserType(m_username);

    if (creditType == "Кредит") {
        if (IsChildOrStudent(currentUserType)) {
            ShowWarning("The credit is not issued to children or students!");
            return;
        }
        ProcessCredit(currentUserType);

    } else if (creditType == "Рассрочка") {
        if (currentUserType == UserType::Child) {
            ShowWarning("The installmentPlan is not issued to children!");
            return;
        }
        ProcessInstallmentPlan();

    } else if (creditType == "Лизинг") {
        if (IsChildOrStudent(currentUserType)) {
            ShowWarning("The credit is not issued to children or students!");
            return;
        }
        ProcessLeasing(currentUserType);

    } else if (creditType == "Микрозайм") {
        if (currentUserType == UserType::Child) {
            ShowWarning("The installmentPlan is not issued to children!");
            return;
        }
        ProcessMicroloan();
    }
}

void MainInterface::ClearLayout(QLayout *layout) {
    QLayoutItem *item;
    while ((item = layout->takeAt(0))) {
        delete item->widget();
        delete item;
    }
}

bool MainInterface::IsChildOrStudent(UserType userType) {
    return userType == UserType::Child || userType == UserType::Student;
}

void MainInterface::ShowWarning(QString message) {
    QMessageBox::warning(this, tr("Error"), tr(message.toStdString().c_str()));
}

void MainInterface::ProcessCredit(UserType userType) {
    loanType = LoanType::Credit;
    Credit credit;
    QList<QJsonObject> creditVariants;

    if (userType == UserType::Pensioner) {
        creditVariants = credit.LoadCredit(ui->choiceBankBox, ui->sumCreditBox, ui->timePayoutBox, ui->percentCreditBox, true);
    } else {
        creditVariants = credit.LoadCredit(ui->choiceBankBox, ui->sumCreditBox, ui->timePayoutBox, ui->percentCreditBox, false);
    }

    for (auto &creditVariant : creditVariants) {
        DisplayLoan(creditVariant);
    }
}

void MainInterface::ProcessInstallmentPlan() {
    loanType = LoanType::InstallmentPlan;
    InstallmentPlan installmentPlan;

    if (ui->percentCreditBox->currentText() == "") {
        installmentPlan.FalsePercent();
    }

    QList<QJsonObject> installmentPlanVariants = installmentPlan.LoadInstallmentPlan(ui->choiceBankBox, ui->sumCreditBox,
                                                                                     ui->timePayoutBox, ui->percentCreditBox);

    for (auto &installmentPlanVariant : installmentPlanVariants) {
        DisplayLoan(installmentPlanVariant);
    }
}

void MainInterface::ProcessLeasing(UserType userType) {
    loanType = LoanType::Leasing;
    Leasing leasing;
    QList<QJsonObject> leasingVariants;

    if (userType == UserType::Pensioner) {
        leasingVariants = leasing.LoadLeasing(ui->choiceBankBox, ui->sumCreditBox, ui->timePayoutBox,
                                              ui->percentCreditBox, ui->reasonBox, true);
    } else {
        leasingVariants = leasing.LoadLeasing(ui->choiceBankBox, ui->sumCreditBox, ui->timePayoutBox,
                                              ui->percentCreditBox, ui->reasonBox, false);
    }

    for (auto &leasingVariant : leasingVariants) {
        DisplayLoan(leasingVariant);
    }
}

void MainInterface::ProcessMicroloan() {
    loanType = LoanType::Microloan;
    Microloan microloan;

    QList<QJsonObject> microloanVariants = microloan.LoadMicroloan(ui->choiceBankBox, ui->sumCreditBox, ui->timePayoutBox,
                                                                   ui->percentCreditBox, ui->paymentBox);

    for (auto &microloanVariant : microloanVariants) {
        DisplayLoan(microloanVariant);
    }
}

void MainInterface::DisplayLoan(QJsonObject jsonObject){
    QString bank = jsonObject["bank"].toString();
    QString money = jsonObject["money"].toString();
    float percent = jsonObject["percent"].toDouble();
    int time = jsonObject["time"].toInt();
    bool isPreferential = jsonObject["preferential"].toBool();
    int reasonLeasing = jsonObject["reason"].toInt();
    double payment = jsonObject["latePaymentPenalty"].toDouble();

    switch (loanType) {
    case LoanType::Credit:
        CreateLoanField(bank, money, percent, time, isPreferential);
        break;
    case LoanType::InstallmentPlan:
        CreateLoanField(bank, money, percent, time, false);
        break;
    case LoanType::Leasing:
        CreateLoanField(bank, money, percent, time, isPreferential, reasonLeasing);
        break;
    case LoanType::Microloan:
        CreateLoanField(bank, money, percent, time, false, 0, payment);
        break;
    }
}

void MainInterface::CreateLoanField(QString bank, QString money, double percent, int time, bool isPreferential, int reason, double payment){
    QWidget *loanWidget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(loanWidget);

    QLineEdit *bankLineEdit = CreateReadOnlyLineEdit(QString("Банк: %1").arg(bank));
    QLineEdit *moneyLineEdit = CreateReadOnlyLineEdit(QString("Сумма: %1").arg(money));
    QPushButton *detailsButton = new QPushButton("Подробнее");

    loanWidget->setStyleSheet("background-color: white;");
    loanWidget->setFixedSize(600, 100);

    layout->addWidget(bankLineEdit, 0, Qt::AlignTop);
    layout->addWidget(moneyLineEdit, 0, Qt::AlignTop);
    layout->setAlignment(Qt::AlignTop);
    layout->addWidget(detailsButton);

    detailsButton->show();
    scrollLayout->addWidget(loanWidget);

    loanWidget->setObjectName("loanWidget");
    loanWidget->setStyleSheet("#loanWidget { border: 1px solid black; }");

    QObject::connect(detailsButton, &QPushButton::clicked, this, [this, bank, money, percent, time, isPreferential, reason, payment]()
                     { DisplayLoanInformation(bank, money, percent, time, isPreferential, reason, payment); });
}

void MainInterface::DisplayLoanInformation(QString bank, QString money, double percent, int time, bool isPreferential, int reason, double payment) {
    QString reasonLeasing = GetLeasingReason(reason);

    QWidget* currentWidget = CreateCurrentWidget();
    QVBoxLayout *layout = new QVBoxLayout(currentWidget);

    QLineEdit *lineEditBank = CreateReadOnlyLineEdit(QString("Банк: %1").arg(bank));
    QLineEdit *lineEditMoney = CreateReadOnlyLineEdit(QString("Сумма кредита: %1").arg(money));
    QLineEdit *lineEditTime = CreateReadOnlyLineEdit(QString("Время на выплату: %1 дней").arg(time));
    QLineEdit *lineEditPreferential = CreateReadOnlyLineEdit(QString("Льготный"));
    lineEditPreferential->setVisible(isPreferential);

    QPushButton *button = CreateButton("Оформить кредит");
    QPushButton *closeButton = CreateCloseButton();

    QHBoxLayout *titleLayout = new QHBoxLayout;
    titleLayout->addStretch();
    titleLayout->addWidget(closeButton);

    layout->addLayout(titleLayout);
    layout->addWidget(lineEditBank, 0, Qt::AlignTop);
    layout->addWidget(lineEditMoney, 0, Qt::AlignTop);
    layout->addWidget(lineEditTime, 0, Qt::AlignTop);

    if(percent != 0){
        QLineEdit *lineEditPercent = CreateReadOnlyLineEdit(QString("Процентная ставка: %1 %").arg(percent));
        layout->addWidget(lineEditPercent, 0, Qt::AlignTop);
    }
    if(!reasonLeasing.isEmpty()){
        QLineEdit *lineEditReason = CreateReadOnlyLineEdit(QString("Дается на: %1").arg(reasonLeasing));
        layout->addWidget(lineEditReason, 0, Qt::AlignTop);
    }
    if(payment != 0){
        QLineEdit *lineEditPayment = CreateReadOnlyLineEdit(QString("Штраф за позднюю оплату: %1 ").arg(payment));
        lineEditPayment->setStyleSheet("border: none; background-color: red;");
        layout->addWidget(lineEditPayment, 0, Qt::AlignTop);
    }
    layout->addWidget(lineEditPreferential, 0, Qt::AlignTop);
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(button);
    if(currentUser.getUserType(m_username) == UserType::Error) {
        ShowWarning("You are not login");
        return;
    }
    QObject::connect(button, &QPushButton::clicked, this,[this, bank, money, percent, time]()
                    { ShowLoanConfirmation(bank, money, percent, time); });
    QObject::connect(closeButton, &QPushButton::clicked, currentWidget, &QWidget::close);

    currentWidget->show();
}

QString MainInterface::GetLeasingReason(int reason) {
    switch (reason) {
    case 1:
        return "Машину";
    case 2:
        return "Квартиру";
    case 3:
        return "Дом";
    default:
        return "";
    }
}

QWidget* MainInterface::CreateCurrentWidget() {
    QWidget* currentWidget = new QWidget;
    currentWidget->setStyleSheet("background-color: white;");
    currentWidget->setFixedSize(300, 300);
    return currentWidget;
}

QLineEdit* MainInterface::CreateReadOnlyLineEdit(QString text) {
    QLineEdit *lineEdit = new QLineEdit(text);
    lineEdit->setReadOnly(true);
    lineEdit->setMaxLength(50);
    lineEdit->setAlignment(Qt::AlignCenter);
    lineEdit->setStyleSheet("border: none;");
    return lineEdit;
}

QPushButton* MainInterface::CreateButton(QString text) {
    QPushButton *button = new QPushButton();
    button->setText(text);
    return button;
}

QPushButton* MainInterface::CreateCloseButton() {
    QPushButton *closeButton = new QPushButton("X");
    closeButton->setFixedSize(25, 25);
    closeButton->setStyleSheet("background-color: red; color: white;");
    return closeButton;
}

void MainInterface::ShowLoanConfirmation(QString bank, QString money, double percent, int time) {
    QDate currentDate = QDate::currentDate();
    QDate futureDate = currentDate.addMonths(time);

    try {
        CreateLoanBasedOnType(bank, money, percent, currentDate, futureDate);
        currentUser.refreshUserLoans(m_username);
        ShowLoanConfirmationMessage(currentDate, futureDate);
    } catch (const LoanException& e) {
        ShowError(e.what());
    }
}

void MainInterface::CreateLoanBasedOnType(QString bank, QString money, double percent, QDate currentDate, QDate futureDate) {
    QString loanTypeString = GetLoanTypeString(loanType);
    currentUser.createLoanStruct(currentUser, loanTypeString, bank, money, percent, currentDate, futureDate);
}

QString MainInterface::GetLoanTypeString(LoanType loanType) {
    switch (loanType) {
    case LoanType::Credit:
        return "Кредит";
    case LoanType::InstallmentPlan:
        return "Рассрочка";
    case LoanType::Leasing:
        return "Лизинг";
    case LoanType::Microloan:
        return "Микрозайм";
    default:
        return "";
    }
}

void MainInterface::ShowLoanConfirmationMessage(QDate currentDate, QDate futureDate) {
    QMessageBox msgBox;
    msgBox.setText(QString("Кредит оформлен %1").arg(currentDate.toString("dd.MM.yyyy")));
    msgBox.setInformativeText(QString("Дата окончания кредита: %1").arg(futureDate.toString("dd.MM.yyyy")));
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void MainInterface::ShowError(QString errorMessage) {
    QMessageBox msgBox;
    msgBox.setText(errorMessage);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void MainInterface::displayUserInfo() {
    if(currentUser.getUserType(m_username) == UserType::Error){
        ShowWarning("You are not login");
        return;
    }

    QString userInfo = BuildUserInfo();
    ShowUserInfo(userInfo);
}

QString MainInterface::BuildUserInfo() {
    QString userInfo = "Username: " + currentUser.username() + "\n";
    userInfo += "Loans:\n";
    userInfo += "-----------------\n";

    for (const Loan &loan : currentUser.loan()) {
        userInfo += BuildLoanInfo(loan);
    }

    return userInfo;
}

QString MainInterface::BuildLoanInfo(const Loan &loan) {
    QString loanInfo = "Type: " + loan.type + "\n";
    loanInfo += "Bank: " + loan.bank + "\n";
    loanInfo += "Amount: " + loan.amount + "\n";
    loanInfo += "Start Date: " + loan.startDate.toString("dd.MM.yyyy") + "\n";
    loanInfo += "End Date: " + loan.endDate.toString("dd.MM.yyyy") + "\n";
    loanInfo += "Percent: " + QString::number(loan.percent) + "\n";
    loanInfo += "-----------------\n";

    return loanInfo;
}

void MainInterface::ShowUserInfo(QString userInfo) {
    QMessageBox msgBox;
    msgBox.setText(userInfo);
    msgBox.exec();
}

void MainInterface::displayLoginDialog(){
    loginDialog->show();
}

void MainInterface::initializeAdminMode(const QString &username, const QString &password, UserType type){
    InitializeUser(username, password, type);
    CreateAdminButton();
    CreateAdminCheckBox();
}

void MainInterface::InitializeUser(const QString &username, const QString &password, UserType type) {
    User user(username, password, type);
    currentUser = user;
    m_username = username;
}

void MainInterface::CreateAdminButton() {
    AdminButton = new QPushButton("Create Credit", this);
    AdminButton->setFixedSize(100, 60);
    AdminButton->show();
    QObject::connect(AdminButton, &QToolButton::clicked, this, &MainInterface::createCredit);
}

void MainInterface::CreateAdminCheckBox() {
    AdminCheckBox = new QCheckBox("IsPreferential", this);
    AdminCheckBox->move(100, 0);
    AdminCheckBox->show();
}

void MainInterface::createCredit() {
    QString creditType = ui->typeOfCreditBox->currentText();
    int payoutTime = ui->timePayoutBox->currentText().toInt();
    int creditPercent = ui->percentCreditBox->currentText().toInt();

    if (creditType == "Кредит") {
        CreateCredit(payoutTime, creditPercent, AdminCheckBox->isChecked());
    } else if (creditType == "Рассрочка") {
        CreateInstallmentPlan(payoutTime, creditPercent);
    } else if (creditType == "Лизинг") {
        CreateLeasing(payoutTime, creditPercent);
    } else if (creditType == "Микрозайм") {
        CreateMicroloan(payoutTime, creditPercent);
    }
}

void MainInterface::CreateCredit(int payoutTime, int creditPercent, bool isPreferential) {
    Credit credit(payoutTime, creditPercent, isPreferential);
    credit.CreateCredit(ui->choiceBankBox, ui->sumCreditBox);
}

void MainInterface::CreateInstallmentPlan(int payoutTime, int creditPercent) {
    InstallmentPlan installmentPlan(payoutTime, creditPercent);
    installmentPlan.CreateInstallmentPlan(ui->choiceBankBox, ui->sumCreditBox);
}

void MainInterface::CreateLeasing(int payoutTime, int creditPercent) {
    Leasing leasing(ui->reasonBox->currentText(), payoutTime, AdminCheckBox->isChecked(), creditPercent);
    leasing.CreateLeasing(ui->choiceBankBox, ui->sumCreditBox);
}

void MainInterface::CreateMicroloan(int payoutTime, int creditPercent) {
    Microloan microloan(ui->paymentBox->currentText().toDouble(), payoutTime, creditPercent);
    microloan.CreateMicroloan(ui->choiceBankBox, ui->sumCreditBox);
}

void MainInterface::removeAdminControls() {
    delete AdminButton;
    delete AdminCheckBox;
    AdminButton = nullptr;
    AdminCheckBox = nullptr;
}

void MainInterface::initializeUserAndRefreshLoans(const QString &username, const QString &password, UserType type) {
    InitializeUser(username, password, type);
    currentUser.refreshUserLoans(username);
}
