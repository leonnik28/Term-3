#include "User.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QCryptographicHash>
#include <QDebug>

User::User(){

}

User::User(const QString &username, const QString &password)
    : m_username(username), m_password(password) {}

User::User(const QString &username, const QString &password, UserType type)
    : m_username(username), m_password(password), m_type(type) {}

User::User(const QString &username, const QString &password, UserType type, QList<Loan> loans)
    : m_username(username), m_password(password), m_type(type), m_loans(loans) {}

QString User::username() const { return m_username; }
QString User::password() const { return m_password; }
UserType User::type() const { return m_type; }
QList<Loan> User::loan() const { return m_loans; }

UserType User::getUserType(const QString &username) {
    QFile file("C:/Users/leonnik/Desktop/Kursovaia/users.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return UserType::Error;
    }

    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();

    if (json.contains(username) && json[username].isObject()) {
        QJsonObject userObject = json[username].toObject();
        if (userObject.contains("type") && userObject["type"].isDouble()) {
            return static_cast<UserType>(userObject["type"].toInt());
        }
    }

    return UserType::Error;
}

void User::createUser() {
    QByteArray hash = QCryptographicHash::hash(m_password.toUtf8(), QCryptographicHash::Sha256);

    QFile file("C:/Users/leonnik/Desktop/Kursovaia/users.json");
    if (!file.open(QIODevice::ReadWrite)) {
        throw LoanException("Couldn't open save file.");
    }

    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();

    if (json.contains(m_username)) {
        throw LoanException("User already exists.");
    }

    QJsonObject userObject;
    userObject["password"] = QString(hash.toHex());
    userObject["type"] = static_cast<int>(m_type);

    userObject["loans"] = QJsonArray();

    json[m_username] = userObject;

    file.close();
    if (!file.open(QIODevice::WriteOnly)) {
        throw LoanException("Couldn't open save file for writing.");
    }

    QJsonDocument saveDoc(json);
    if (file.write(saveDoc.toJson()) == -1) {
        throw LoanException("Failed to write to save file.");
    }
}

void User::createLoanStruct(User currentUser, QString type, QString bank, QString money, double percent, QDate startTime, QDate endTime){
    Loan newLoan;
    newLoan.type = type;
    newLoan.bank = bank;
    newLoan.amount = money;
    newLoan.startDate = startTime;
    newLoan.endDate = endTime;
    newLoan.percent = percent;
    for (const Loan &existingLoan : m_loans) {
        if (existingLoan.type == newLoan.type && existingLoan.bank == newLoan.bank && existingLoan.amount == newLoan.amount) {
            throw LoanException("User has already taken this loan.");
        }
    }
    for (const Loan &existingLoan : m_loans) {
        if (existingLoan.type == newLoan.type && existingLoan.bank == newLoan.bank) {
            throw LoanException("User has already taken a loan from this bank.");
        }
    }
    currentUser.addLoan(newLoan);
}

void User::addLoan(const Loan& loan) {

    m_loans.append(loan);

    QFile file("C:/Users/leonnik/Desktop/Kursovaia/users.json");
    if (!file.open(QIODevice::ReadWrite)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();

    if (!json.contains(m_username)) {
        qWarning("User does not exist.");
        return;
    }

    QJsonObject userObject = json[m_username].toObject();

    QJsonArray loansArray;
    for (const Loan &loan : m_loans) {
        QJsonObject loanObject;
        loanObject["type"] = loan.type;
        loanObject["bank"] = loan.bank;
        loanObject["amount"] = loan.amount;
        loanObject["startDate"] = loan.startDate.toString("dd.MM.yyyy");
        loanObject["endDate"] = loan.endDate.toString("dd.MM.yyyy");
        loanObject["percent"] = loan.percent;
        loansArray.append(loanObject);
    }
    userObject["loans"] = loansArray;

    json[m_username] = userObject;

    file.close();
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file for writing.");
        return;
    }

    QJsonDocument saveDoc(json);
    if (file.write(saveDoc.toJson()) == -1) {
        qWarning("Failed to write to save file.");
        return;
    }
}

void User::refreshUserLoans(const QString &username) {
    QFile file("C:/Users/leonnik/Desktop/Kursovaia/users.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();

    if (!json.contains(username)) {
        qWarning("User does not exist.");
        return;
    }

    QJsonObject userObject = json[username].toObject();

    m_loans.clear();
    QJsonArray loansArray = userObject["loans"].toArray();
    for (int i = 0; i < loansArray.size(); ++i) {
        QJsonObject loanObject = loansArray[i].toObject();
        Loan loan;
        loan.type = loanObject["type"].toString();
        loan.bank = loanObject["bank"].toString();
        loan.amount = loanObject["amount"].toString();
        loan.startDate = QDate::fromString(loanObject["startDate"].toString(), "dd.MM.yyyy");
        loan.endDate = QDate::fromString(loanObject["endDate"].toString(), "dd.MM.yyyy");
        loan.percent = loanObject["percent"].toDouble();
        m_loans.append(loan);
    }
}

UserType User::checkCredentials() {

    QByteArray hash = QCryptographicHash::hash(m_password.toUtf8(), QCryptographicHash::Sha256);

    QFile file("C:/Users/leonnik/Desktop/Kursovaia/users.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return UserType::Student;
    }

    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();

    if (json.contains(m_username) && json[m_username].isObject()) {
        QJsonObject userObject = json[m_username].toObject();
        if (userObject["password"].toString() == QString(hash.toHex())) {
            m_type = getUserType(m_username);
            return getUserType(m_username);
        }
    }

    return UserType::Error;
}

