#ifndef LOGIC_H
#define LOGIC_H

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QVector>
#include "patient.h"
#include "QDebug"
#include <QTextCodec>
#include <QVector>
#include <QString>



class Logic
{
public:
    Logic();
    void savePatient(const Patient& user);
    QString getDFileInfo(QString fn);
    double getInitTime(QString fn);
    QVector<double>getPulse(QString fn);
    QVector<double>getBreath(QString fn);
    QVector<double>getPosition(QString fn);

};


#endif // LOGIC_H
