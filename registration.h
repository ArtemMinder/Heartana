#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include "logic.h"
#include "patient.h"

namespace Ui {
class registration;
}

class registration : public QDialog
{
    Q_OBJECT

public:
    explicit registration(QWidget *parent = nullptr);
    ~registration();

private slots:

    void on_cancelButton_clicked();

    void on_confirmButton_clicked();

private:
    Ui::registration *ui;
    Patient *patient;
    Logic *logic;
};

#endif // REGISTRATION_H
