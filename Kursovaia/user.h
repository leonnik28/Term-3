#ifndef USER_H
#define USER_H

#include <QString>
#include <QList>
#include <QDate>
#include "loanexception.h"

enum class UserType {
    Error,
    Student,
    Worker,
    Pensioner,
    Child,
    Admin
};

struct Loan {
    QString type;
    QString bank;
    QString amount;
    double percent;
    QDate startDate;
    QDate endDate;
};

class User {
public:
    User();
    User(const QString &username, const QString &password);
    User(const QString &username, const QString &password, UserType type);
    User(const QString &username, const QString &password, UserType type, QList<Loan> loans);

    QString username() const;
    QString password() const;
    UserType type() const;
    QList<Loan> loan() const;

    UserType getUserType(const QString &username);
    void createUser();
    void createLoanStruct(User currentUser, QString type, QString bank, QString money, double percent, QDate startTime, QDate endTime);
    void addLoan(const Loan& loan);
    void refreshUserLoans(const QString &username);
    UserType checkCredentials();

private:
    QString m_username;
    QString m_password;
    UserType m_type;
    QList<Loan> m_loans;
};

#endif // USER_H
