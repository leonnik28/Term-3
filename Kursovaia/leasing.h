#ifndef LEASING_H
#define LEASING_H

#include "typeofcredit.h"
#include <QString>

class Leasing : public TypeOfCredit
{
public:
    enum ReasonLeasing{
        car = 1,
        apartment,
        house
    };

    Leasing();
    Leasing(QString reasonLeasing, int time);
    Leasing(QString reasonLeasing, int time, bool preferential, int percentLeasing);
    void CreateLeasing(QComboBox *comboBoxBank, QComboBox *comboBoxMoney);
    QList<QJsonObject> LoadLeasing(QComboBox *comboBoxBank, QComboBox *comboBoxMoney, QComboBox *comboBoxTime,
                                   QComboBox *comboBoxPercent, QComboBox* comboBoxReason, bool pensionerMode);

private:
    int timeOfLeasing;
    ReasonLeasing reason;
};

#endif // LEASING_H

