#include "registration.h"
#include "ui_registration.h"
#include "logic.h"
#include "patient.h"
#include "mainwindow.h"
#include <QStyleFactory>
#include <QMessageBox>

registration::registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registration)
{
    ui->setupUi(this);
    logic = new Logic;
    patient = new Patient;
}

registration::~registration()
{
    delete ui;
}

void registration::on_cancelButton_clicked()
{
   this->close();
}

void registration::on_confirmButton_clicked()
{
    Patient patient;
    patient.name=ui->name->toPlainText();
    patient.surName=ui->surName->toPlainText();
    patient.fatherName=ui->fatherName->toPlainText();
    patient.age=ui->ageEdit->toPlainText();
    if(ui->fButton->isChecked()){ patient.sex=(Sex::female);}
    if(ui->mButton_3->isChecked()){ patient.sex=(Sex::male);}
    if(ui->name->toPlainText() == ""||ui->surName->toPlainText() == ""||
    ui->fatherName->toPlainText() == ""||ui->ageEdit->toPlainText() == ""||
    ui->mButton_3->isChecked() == false && ui->fButton->isChecked() == false)
    {
        QMessageBox msgBox;
        msgBox.setText("Необходимые данные отсутствуют");
        msgBox.exec();
    } else {
    logic->savePatient(patient);
    ui->name->clear();
    ui->surName->clear();
    ui->fatherName->clear();
    ui->ageEdit->clear();
    ui->mButton_3->setChecked(false);
    ui->fButton->setChecked(false);
    this->close();
    }
}
