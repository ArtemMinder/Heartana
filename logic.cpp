#include "logic.h"
#include "mainwindow.h"
#include "QFile"
#include "patient.h"
#include "QDebug"
#include <QTextCodec>
#include <QVector>
#include <QString>

Logic::Logic()
{}

QString Logic::getDFileInfo(QString fn){
    QFile inputFile(fn);
    if (inputFile.open(QIODevice::ReadOnly)){
        QTextStream in(&inputFile);
        in.setCodec(QTextCodec::codecForName("UTF-8"));
        QString str = in.readAll();
        QTextStream s(&str);
        QString name;
        name= s.readLine();
        inputFile.close();
        QFile inputFile(fn);
        if (inputFile.open(QIODevice::ReadOnly)){
            QTextStream in(&inputFile);
            in.setCodec(QTextCodec::codecForName("UTF-8"));
            QString str = in.readAll();
            QTextStream s(&str);
            QString surName;
            for (size_t i = 0; i < 2; i++)
                surName= s.readLine();
            inputFile.close();
            QFile inputFile(fn);
            if (inputFile.open(QIODevice::ReadOnly)){
                QTextStream in(&inputFile);
                in.setCodec(QTextCodec::codecForName("UTF-8"));
                QString str = in.readAll();
                QTextStream s(&str);
                QString fatherName;
                for (size_t i = 0; i < 3; i++)
                    fatherName= s.readLine();
                inputFile.close();
                QFile inputFile(fn);
                if (inputFile.open(QIODevice::ReadOnly)){
                    QTextStream in(&inputFile);
                    in.setCodec(QTextCodec::codecForName("UTF-8"));
                    QString str = in.readAll();
                    QTextStream s(&str);
                    QString age;
                    for (size_t i = 0; i < 4; i++)
                        age = s.readLine();
                    inputFile.close();
                    return name+" "+surName+" "+fatherName+" "+age;
}}}}return 0;}

void Logic::savePatient(const Patient& patient){ 
    /*QString filename = patient.name.toUtf8()+" "+
            patient.surName.toUtf8() +" "+ patient.fatherName.toUtf8();*/
    QString filename = "DATALOG";
    QString format = ".txt";
    QString fn = filename+format;
    fn = QFileDialog::getSaveFileName(0, "Сохранить файл", fn, "*.txt");
    QFile file (fn);
    QStringList strList;
 if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
 { while(!file.atEnd()){strList << file.readLine(); }
     file.close();
 }
 if (file.open(QIODevice::WriteOnly)){
     file.write(patient.name.toUtf8());
     file.write("\n");
     file.write(patient.surName.toUtf8());
     file.write("\n");
     file.write(patient.fatherName.toUtf8());
     file.write("\n");
     file.write(patient.age.toUtf8());
     file.write("\n");
     if(patient.sex==Sex::male){
          file.write("Мужской");
          file.write("\n");
      }
      else if(patient.sex==Sex::female){
         file.write("Женский");
         file.write("\n");
      }
      else if(patient.sex==Sex::unset){
         file.write("Пол не выбран");
         file.write("\n");
      }
     double startingTime = QDateTime::currentDateTime().toTime_t();
     file.write(QString::number(startingTime).toUtf8());
     file.write("\n");
     file.close();
}}

double Logic::getInitTime(QString filename){
    double dTime{};
    QFile inputFile(filename);
    if (inputFile.open(QIODevice::ReadOnly)){
       QTextStream in(&inputFile);
       in.setCodec(QTextCodec::codecForName("UTF-8"));
       QString str = in.readAll();
       QTextStream s(&str);
       QString init;
       for (size_t i = 0; i < 6; i++)
       init= s.readLine();
       dTime = init.toDouble();
       inputFile.close();
}
       return dTime;
}

QVector<double>Logic::getPulse(QString fn){
   QVector<QString> strList;
   QVector<double>pulse;
    QFile inputFile(fn);
    if ((inputFile.exists())&&(inputFile.open(QIODevice::ReadOnly)))
    {
        while(!inputFile.atEnd())
        {
        strList << inputFile.readLine();
        }
        inputFile.close();
         for(int i=6;i<strList.size();i+=3){
             pulse.push_back(strList[i].toDouble());
         }
    }
    return pulse;
}

QVector<double>Logic::getPosition(QString fn){
   QVector<QString> strList;
   QVector<double>position;
    QFile inputFile(fn);
    if ((inputFile.exists())&&(inputFile.open(QIODevice::ReadOnly)))
    {
        while(!inputFile.atEnd())
        {
        strList << inputFile.readLine();
        }
        inputFile.close();
         for(int i=7;i<strList.size();i+=3){
             position.push_back(strList[i].toDouble());
         }
    }
    return position;
}

QVector<double>Logic::getBreath(QString fn){
   QVector<QString> strList;
   QVector<double>breath;
    QFile inputFile(fn);
    if ((inputFile.exists())&&(inputFile.open(QIODevice::ReadOnly)))
    {
        while(!inputFile.atEnd())
        {
        strList << inputFile.readLine();
        }
        inputFile.close();
         for(int i=8;i<strList.size();i+=3){
             breath.push_back(strList[i].toDouble());
         }
    }
    return breath;
}

