#ifndef INSTALLMENTPLAN_H
#define INSTALLMENTPLAN_H

#include "credit.h"

class InstallmentPlan : public Credit
{
public:
    InstallmentPlan();
    InstallmentPlan(bool isPercent);
    InstallmentPlan(int time, int percentInstallmentPlan);
    ~InstallmentPlan();
    void FalsePercent();
    void CreateInstallmentPlan(QComboBox *comboBoxBank, QComboBox *comboBoxMoney);
    QList<QJsonObject> LoadInstallmentPlan(QComboBox *comboBoxBank, QComboBox *comboBoxMoney, QComboBox *comboBoxTime,
                                           QComboBox *comboBoxPercent);
private:
    bool isWithPercent;
};

#endif // INSTALLMENTPLAN_H
