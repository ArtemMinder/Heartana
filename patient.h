#ifndef USER_H
#define USER_H
#include <QString>
#include <QVector>


enum class Sex
{
    male,
    female,
    unset
};

struct Patient
{
    QString name = {};
    QString surName = {};
    QString fatherName = {};
    QString age = {};
    Sex sex=Sex::unset;
    QVector<double>pulse{};
    QVector<double>breath{};
    QVector<double>position{};
    double startTime{};
    double interval{};
    void setPulse(const QVector<double>&newPulse){
        this->pulse=newPulse;
    }
    void setPosition(const QVector<double>&newPosition){
         this->position=newPosition;
    }
    void setBreath(const QVector<double>&newBreath){
        this->breath = newBreath;
    }
};

#endif // USER_H
