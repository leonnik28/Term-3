#ifndef MICROLOAN_H
#define MICROLOAN_H

#include "typeofcredit.h"

class Microloan : public TypeOfCredit
{
public:
    Microloan();
    Microloan(double payment, int time, int percentMicroloan);
    ~Microloan();
    void CreateMicroloan(QComboBox *comboBoxBank, QComboBox *comboBoxMoney);
    QList<QJsonObject> LoadMicroloan(QComboBox *comboBoxBank, QComboBox *comboBoxMoney, QComboBox *comboBoxTime,
                                     QComboBox *comboBoxPercent, QComboBox* comboBoxPenalty);
private:
    int timeOfMicroloan;
    double latePaymentPenalty;
};

#endif // MICROLOAN_H
