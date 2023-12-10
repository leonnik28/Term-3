#ifndef LOANEXCEPTION_H
#define LOANEXCEPTION_H

#include <QString>
#include <QList>
#include <QDate>

class LoanException : public std::exception {
public:
    explicit LoanException(const std::string& message) : msg_(message) {}
    virtual char const* what() const noexcept { return msg_.c_str(); }

private:
    std::string msg_;
};


#endif // LOANEXCEPTION_H
