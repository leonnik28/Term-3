#include "credit.h"

Credit::Credit(){

}

Credit::Credit(int time, int percentCredit){
    timeOfCredit = time;
    percent = percentCredit;
}

Credit::Credit(int time, int percentCredit, bool preferential){
    timeOfCredit = time;
    percent = percentCredit;
    isPreferential = preferential;
}

Credit::~Credit(){

}

void Credit::CreateCredit(QComboBox *comboBoxBank, QComboBox *comboBoxMoney){
    QJsonObject credit;
    credit["bank"] = comboBoxBank->currentText();
    credit["money"] = comboBoxMoney->currentText();
    credit["percent"] = percent;
    credit["time"] = timeOfCredit;
    credit["preferential"] = isPreferential;

    QFile file("C:/Users/leonnik/Desktop/Kursovaia/credit.json");
    if (!file.open(QIODevice::ReadWrite)) {
        qWarning("Couldn't open save file.");
        return;
    }


    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject mainObject = loadDoc.object();
    QJsonArray creditArray = mainObject["credits"].toArray();
    creditArray.append(credit);
    mainObject["credits"] = creditArray;

    file.seek(0);
    file.write(QJsonDocument(mainObject).toJson());
    file.close();
}

QList<QJsonObject> Credit::LoadCredit(QComboBox *comboBoxBank, QComboBox *comboBoxMoney, QComboBox *comboBoxTime,
                                      QComboBox *comboBoxPercent, bool pensionerMode) {
    QFile file("C:/Users/leonnik/Desktop/Kursovaia/credit.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open load file.");
        return QList<QJsonObject>();
    }

    QByteArray loadData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
    QJsonObject mainObject = loadDoc.object();
    QJsonArray creditArray = mainObject["credits"].toArray();

    QList<QJsonObject> matchingCredits;

    for (int i = 0; i < creditArray.size(); ++i) {
        QJsonObject credit = creditArray[i].toObject();
        QString bank = credit["bank"].toString();
        QString money = credit["money"].toString();
        double percent = credit["percent"].toDouble();
        QString percentCredit = QString::number(percent);
        int time = credit["time"].toInt();
        QString timeCredit = QString::number(time);
        bool preferential = credit["preferential"].toBool();

        if(pensionerMode){
            if ((comboBoxBank->currentText() == "Банк" || bank == comboBoxBank->currentText()) &&
                (comboBoxMoney->currentText().isEmpty() || money == comboBoxMoney->currentText()) &&
                (comboBoxTime->currentText().isEmpty() || timeCredit == comboBoxTime->currentText()) &&
                (comboBoxPercent->currentText().isEmpty() || percentCredit == comboBoxPercent->currentText())) {
                matchingCredits.append(credit);
            }
        }
        else{
            if ((comboBoxBank->currentText() == "Банк" || bank == comboBoxBank->currentText()) &&
                (comboBoxMoney->currentText().isEmpty() || money == comboBoxMoney->currentText()) &&
                (comboBoxTime->currentText().isEmpty() || timeCredit == comboBoxTime->currentText()) &&
                (comboBoxPercent->currentText().isEmpty() || percentCredit == comboBoxPercent->currentText()) &&
                preferential == false) {
                matchingCredits.append(credit);
            }
        }
    }

    file.close();
    return matchingCredits;
}



