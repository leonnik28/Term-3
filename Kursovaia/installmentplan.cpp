#include "installmentplan.h"

InstallmentPlan::InstallmentPlan(){

}

InstallmentPlan::InstallmentPlan(bool isPercent){
    isWithPercent = isPercent;
}

InstallmentPlan::InstallmentPlan(int time, int percentInstallmentPlan){
    isWithPercent = true;
    timeOfCredit = time;
    percent = percentInstallmentPlan;
}

InstallmentPlan::~InstallmentPlan(){

}

void InstallmentPlan::FalsePercent(){
    isWithPercent = false;
}

void InstallmentPlan::CreateInstallmentPlan(QComboBox *comboBoxBank, QComboBox *comboBoxMoney){
    QJsonObject installmentPlan;
    installmentPlan["bank"] = comboBoxBank->currentText();
    installmentPlan["money"] = comboBoxMoney->currentText();
    if(isWithPercent == true){
        installmentPlan["percent"] = percent;
    }
    installmentPlan["time"] = timeOfCredit;
    installmentPlan["preferential"] = isPreferential;

    QFile file("C:/Users/leonnik/Desktop/Kursovaia/installmentPlan.json");
    if (!file.open(QIODevice::ReadWrite)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject mainObject = loadDoc.object();
    QJsonArray installmentPlanArray = mainObject["installmentPlans"].toArray();
    installmentPlanArray.append(installmentPlan);
    mainObject["installmentPlans"] = installmentPlanArray;

    file.seek(0);
    file.write(QJsonDocument(mainObject).toJson());
    file.close();
}

QList<QJsonObject> InstallmentPlan::LoadInstallmentPlan(QComboBox *comboBoxBank, QComboBox *comboBoxMoney, QComboBox *comboBoxTime,
                                                        QComboBox *comboBoxPercent) {
    QFile file("C:/Users/leonnik/Desktop/Kursovaia/installmentPlan.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open load file.");
        return QList<QJsonObject>();
    }

    QByteArray loadData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
    QJsonObject mainObject = loadDoc.object();
    QJsonArray installmentPlanArray = mainObject["installmentPlans"].toArray();

    QList<QJsonObject> matchingInstallmentPlan;

    for (int i = 0; i < installmentPlanArray.size(); ++i) {

        QJsonObject installmentPlan = installmentPlanArray[i].toObject();
        QString bank = installmentPlan["bank"].toString();
        QString money = installmentPlan["money"].toString();
        double percent = installmentPlan["percent"].toDouble();
        QString percentLoan = QString::number(percent);
        int time = installmentPlan["time"].toInt();
        QString timeLoan = QString::number(time);

        if ((comboBoxBank->currentText() == "Банк" || bank == comboBoxBank->currentText()) &&
            (comboBoxMoney->currentText().isEmpty() || money == comboBoxMoney->currentText()) &&
            (comboBoxTime->currentText().isEmpty() || timeLoan == comboBoxTime->currentText()) &&
            (comboBoxPercent->currentText().isEmpty() || percentLoan == comboBoxPercent->currentText())) {
                matchingInstallmentPlan.append(installmentPlan);
            }
    }

    file.close();
    return matchingInstallmentPlan;
}
