#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <registration.h>
#include "qcustomplot.h"
#include "patient.h"
#include "logic.h"
#include "settings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void startGraphicPreset();
    void setNorm(QString newYear);
    void setGraphicIntro();
    double breathDiviation(int const& low, int const& high, QVector <double> newBreath);
    double pulseDiviation(int const& low, int const& high, QVector <double> newPulse);
    ~MainWindow();

private slots:

    void on_addButton_clicked();
    void on_downloadButton_clicked();
    void on_aboutButton_clicked();
    void on_reZeroButton_clicked();
    void slotRangeChanged (const QCPRange &newRange);
    void on_settingButton_clicked();
    void on_SDButton_clicked();

private:

    Ui::MainWindow *ui;
    QString info = {};
    QVector <double> time{}, pulse{}, lowBreath{}, highBreath{}, lowPulse{}, highPulse{},
    breathing{}, position{}, position_up{}, position_down{}, position_right{},
    position_left{}, position_sit{}, position_bat{};
    double startTime, interval = {};
    int lowBr = 0;
    int highBr = 0;
    int lowPl = 0;
    int highPl = 0;
    QCustomPlot *customPlot;
    QCPGraph *graphic;
    QCPGraph *lowBreathNorm;
    QCPGraph *highBreathNorm;
    QCPGraph *lowPulseNorm;
    QCPGraph *highPulseNorm;
    QCPGraph *graphic_up;
    QCPGraph *graphic_down;
    QCPGraph *graphic_right;
    QCPGraph *graphic_left;
    QCPGraph *graphic_sit;
    QCPGraph *graphic_bat;
    QCPGraph *graphic_two;
    QCPGraph *graphic_breath;
    Patient *patient;
    Settings  *settings;
    registration *form;
    Logic *logic;
};
#endif // MAINWINDOW_H
