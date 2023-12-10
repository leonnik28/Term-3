#include "leasing.h"

Leasing::Leasing(){

}

Leasing::Leasing(QString reasonLeasing, int time){
    if(reasonLeasing == "Машина"){
        reason = ReasonLeasing::car;
    }
    else if(reasonLeasing == "Квартира"){
        reason = ReasonLeasing::apartment;
    }
    else if(reasonLeasing == "Дом"){
        reason = ReasonLeasing::house;
    }
    timeOfLeasing = time;
}

Leasing::Leasing(QString reasonLeasing, int time, bool preferential, int percentLeasing){
    if(reasonLeasing == "Машина"){
        reason = ReasonLeasing::car;
    }
    else if(reasonLeasing == "Квартира"){
        reason = ReasonLeasing::apartment;
    }
    else if(reasonLeasing == "Дом"){
        reason = ReasonLeasing::house;
    }
    timeOfLeasing = time;
    isPreferential = preferential;
    percent = percentLeasing;
}

void Leasing::CreateLeasing(QComboBox *comboBoxBank, QComboBox *comboBoxMoney){
    QJsonObject leasing;
    leasing["bank"] = comboBoxBank->currentText();
    leasing["money"] = comboBoxMoney->currentText();
    leasing["percent"] = percent;
    leasing["time"] = timeOfLeasing;
    leasing["reason"] = reason;
    leasing["preferential"] = isPreferential;

    QFile file("C:/Users/leonnik/Desktop/Kursovaia/leasing.json");
    if (!file.open(QIODevice::ReadWrite)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject mainObject = loadDoc.object();
    QJsonArray leasingArray = mainObject["leasings"].toArray();
    leasingArray.append(leasing);
    mainObject["leasings"] = leasingArray;

    file.seek(0);
    file.write(QJsonDocument(mainObject).toJson());
    file.close();
}

QList<QJsonObject> Leasing::LoadLeasing(QComboBox *comboBoxBank, QComboBox *comboBoxMoney, QComboBox *comboBoxTime,
                                        QComboBox *comboBoxPercent, QComboBox* comboBoxReason, bool pensionerMode) {
    QFile file("C:/Users/leonnik/Desktop/Kursovaia/leasing.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open load file.");
        return QList<QJsonObject>();
    }

    QByteArray loadData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
    QJsonObject mainObject = loadDoc.object();
    QJsonArray leasingArray = mainObject["leasings"].toArray();

    QList<QJsonObject> matchingLeasings;

    for (int i = 0; i < leasingArray.size(); ++i) {
        QJsonObject leasing = leasingArray[i].toObject();
        QString bank = leasing["bank"].toString();
        QString money = leasing["money"].toString();
        double percent = leasing["percent"].toDouble();
        QString percentLoan = QString::number(percent);
        int time = leasing["time"].toInt();
        QString timeLoan = QString::number(time);
        int reason = leasing["reason"].toInt();
        bool preferential = leasing["preferential"].toBool();

        if(pensionerMode){
            if ((comboBoxBank->currentText() == "Банк" || bank == comboBoxBank->currentText()) &&
                (comboBoxMoney->currentText().isEmpty() || money == comboBoxMoney->currentText()) &&
                (comboBoxTime->currentText().isEmpty() || timeLoan == comboBoxTime->currentText()) &&
                (comboBoxPercent->currentText().isEmpty() || percentLoan == comboBoxPercent->currentText()) &&
                (comboBoxReason->currentText() == "Причина" || reason == comboBoxReason->currentIndex())) {
                matchingLeasings.append(leasing);
            }
        }
        else{
            if ((comboBoxBank->currentText() == "Банк" || bank == comboBoxBank->currentText()) &&
                (comboBoxMoney->currentText().isEmpty() || money == comboBoxMoney->currentText()) &&
                (comboBoxTime->currentText().isEmpty() || timeLoan == comboBoxTime->currentText()) &&
                (comboBoxPercent->currentText().isEmpty() || percentLoan == comboBoxPercent->currentText()) &&
                (comboBoxReason->currentText() == "Причина" || reason == comboBoxReason->currentIndex()) &&
                preferential == false) {
                matchingLeasings.append(leasing);
            }
        }

    }

    file.close();
    return matchingLeasings;
}
