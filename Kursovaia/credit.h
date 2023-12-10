#ifndef CREDIT_H
#define CREDIT_H

#include "typeofcredit.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

class Credit : public TypeOfCredit
{
public:
    Credit();
    Credit(int time, int percentCredit);
    Credit(int time, int percentCredit, bool preferential);
    ~Credit();
    void CreateCredit(QComboBox *comboBoxBank, QComboBox *comboBoxMoney);
    QList<QJsonObject> LoadCredit(QComboBox *comboBoxBank, QComboBox *comboBoxMoney, QComboBox *comboBoxTime,
                                  QComboBox *comboBoxPercent, bool pensionerMode);
protected:
    int timeOfCredit;
};

#endif // CREDIT_H
