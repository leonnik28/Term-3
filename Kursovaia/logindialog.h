#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include "User.h"

class LoginDialog : public QDialog {
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = nullptr);

signals:
    void adminLogin(const QString &username, const QString &password, UserType type);
    void userLogin(const QString &username, const QString &password, UserType type);
    void disableAdminMode();

private slots:
    void handleLogin();
    void handleCreateAccount(QString userType);

private:
    QLineEdit *m_usernameLineEdit;
    QLineEdit *m_passwordLineEdit;
};
