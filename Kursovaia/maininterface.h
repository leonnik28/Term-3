#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include "mainwindow.h"
#include "logindialog.h"
#include "user.h"

class MainInterface : public MainWindow
{
    Q_OBJECT

public:
    enum class LoanType{
        Credit,
        InstallmentPlan,
        Leasing,
        Microloan
    };

    explicit MainInterface();
    ~MainInterface();

public slots:
    void initializeAdminMode(const QString &username, const QString &password, UserType type);
    void removeAdminControls();
    void initializeUserAndRefreshLoans(const QString &username, const QString &password, UserType type);

private:
    LoanType loanType;
    LoginDialog* loginDialog;
    User currentUser;
    QString m_username;
    QPushButton *AdminButton = nullptr;
    QCheckBox* AdminCheckBox = nullptr;

    void ClearLayout(QLayout *layout);
    bool IsChildOrStudent(UserType userType);
    void ShowWarning(QString message);
    void ProcessCredit(UserType userType);
    void ProcessInstallmentPlan();
    void ProcessLeasing(UserType userType);
    void ProcessMicroloan();
    void DisplayLoan(QJsonObject jsonObject);
    void CreateLoanField(QString bank, QString money, double percent, int time, bool isPreferential, int reason = 0, double payment = 0);
    void DisplayLoanInformation(QString bank, QString money, double percent, int time, bool isPreferential, int reason, double payment);
    QString GetLeasingReason(int reason);
    QWidget* CreateCurrentWidget();
    QLineEdit* CreateReadOnlyLineEdit(QString text);
    QPushButton* CreateButton(QString text);
    QPushButton* CreateCloseButton();
    void ShowLoanConfirmation(QString bank, QString money, double percent, int time);
    void CreateLoanBasedOnType(QString bank, QString money, double percent, QDate currentDate, QDate futureDate);
    QString GetLoanTypeString(LoanType loanType);
    void ShowLoanConfirmationMessage(QDate currentDate, QDate futureDate);
    void ShowError(QString errorMessage);
    QString BuildUserInfo();
    QString BuildLoanInfo(const Loan &loan);
    void ShowUserInfo(QString userInfo);
    void InitializeUser(const QString &username, const QString &password, UserType type);
    void CreateAdminButton();
    void CreateAdminCheckBox();
    void CreateCredit(int payoutTime, int creditPercent, bool isPreferential = false);
    void CreateInstallmentPlan(int payoutTime, int creditPercent);
    void CreateLeasing(int payoutTime, int creditPercent);
    void CreateMicroloan(int payoutTime, int creditPercent);

private slots:
    void searchCredit();
    void displayUserInfo();
    void displayLoginDialog();
    void createCredit();
};
#endif // MAININTERFACE_H
