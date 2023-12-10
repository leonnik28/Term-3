#include "microloan.h"

Microloan::Microloan(){

}

Microloan::Microloan(double payment, int time, int percentMicroloan){
    latePaymentPenalty = payment;
    timeOfMicroloan = time;
    percent = percentMicroloan;
}

Microloan::~Microloan(){

}

void Microloan::CreateMicroloan(QComboBox *comboBoxBank, QComboBox *comboBoxMoney){
    QJsonObject microloan;
    microloan["bank"] = comboBoxBank->currentText();
    microloan["money"] = comboBoxMoney->currentText();
    microloan["percent"] = percent;
    microloan["time"] = timeOfMicroloan;
    microloan["latePaymentPenalty"] = latePaymentPenalty;

    QFile file("C:/Users/leonnik/Desktop/Kursovaia/microloan.json");
    if (!file.open(QIODevice::ReadWrite)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject mainObject = loadDoc.object();
    QJsonArray microloanArray = mainObject["microloans"].toArray();
    microloanArray.append(microloan);
    mainObject["microloans"] = microloanArray;

    file.seek(0);
    file.write(QJsonDocument(mainObject).toJson());
    file.close();
}

QList<QJsonObject> Microloan::LoadMicroloan(QComboBox *comboBoxBank, QComboBox *comboBoxMoney, QComboBox *comboBoxTime,
                                            QComboBox *comboBoxPercent, QComboBox* comboBoxPenalty) {
    QFile file("C:/Users/leonnik/Desktop/Kursovaia/microloan.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open load file.");
        return QList<QJsonObject>();
    }

    QByteArray loadData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
    QJsonObject mainObject = loadDoc.object();
    QJsonArray microloanArray = mainObject["microloans"].toArray();

    QList<QJsonObject> matchingMicroloan;

    for (int i = 0; i < microloanArray.size(); ++i) {

        QJsonObject microloan = microloanArray[i].toObject();
        QString bank = microloan["bank"].toString();
        QString money = microloan["money"].toString();
        double percent = microloan["percent"].toDouble();
        QString percentLoan = QString::number(percent);
        int time = microloan["time"].toInt();
        QString timeLoan = QString::number(time);
        double latePaymentPenalty = microloan["latePaymentPenalty"].toDouble();
        QString latePaymentPenaltyLoan = QString::number(latePaymentPenalty);

        if ((comboBoxBank->currentText() == "Банк" || bank == comboBoxBank->currentText()) &&
            (comboBoxMoney->currentText().isEmpty() || money == comboBoxMoney->currentText()) &&
            (comboBoxTime->currentText().isEmpty() || timeLoan == comboBoxTime->currentText()) &&
            (comboBoxPercent->currentText().isEmpty() || percentLoan == comboBoxPercent->currentText()) &&
            (comboBoxPenalty->currentText().isEmpty() || latePaymentPenaltyLoan == comboBoxPenalty->currentText())) {
                matchingMicroloan.append(microloan);
            }
    }

    file.close();
    return matchingMicroloan;
}
