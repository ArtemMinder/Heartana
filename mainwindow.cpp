#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registration.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QMessageBox>
#include <QString>
#include "logic.h"
#include "patient.h"
#include "qcustomplot.h"
#include <QStyleFactory>

QT_CHARTS_USE_NAMESPACE
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow){
    logic = new Logic;
    form = new registration;
    settings = new Settings;
    ui->setupUi(this);
    this->showMaximized();
    customPlot = new QCustomPlot();
    startGraphicPreset();
    setGraphicIntro();
}

void MainWindow::startGraphicPreset(){
    ui->gridLayout->addWidget(customPlot,0,0,1,1);
    customPlot->setInteraction(QCP::iRangeZoom,true);
    customPlot->setInteraction(QCP::iRangeDrag, true);
    customPlot->axisRect()->setRangeDrag(Qt::Horizontal);
    customPlot->axisRect()->setRangeZoom(Qt::Horizontal);
    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
    customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 10));
    customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 10));
    customPlot->xAxis->setAutoTickStep(true);
    customPlot->xAxis2->setVisible(true);
    customPlot->yAxis2->setVisible(true);
    customPlot->xAxis2->setTicks(false);
    customPlot->yAxis2->setTicks(false);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setTickLabels(false);
    QPen pen;
    pen.setBrush(QColor(240,26,36));
    pen.setWidth(2);
    QPen pen2;
    pen2.setBrush(QColor(35,81,159));
    pen2.setWidth(2);
    QPen breath_norm;
    breath_norm.setStyle(Qt::DashLine);
    breath_norm.setBrush(QColor(35,81,159));
    breath_norm.setWidth(2);
    QPen pulse_norm;
    pulse_norm.setStyle(Qt::DashLine);
    pulse_norm.setBrush(QColor(240,26,36));
    pulse_norm.setWidth(2);
    QPen red;
    red.setBrush(QColor(217,49,40));
    red.setWidth(2);
    QPen black;
    black.setBrush(QColor(0,0,0));
    black.setWidth(1);
    QPen yellow;
    yellow.setBrush(QColor(253,226,59));
    yellow.setWidth(2);
    QPen green;
    green.setBrush(QColor(120,183,50));
    green.setWidth(2);
    QPen blue;
    blue.setBrush(QColor(95,199,228));
    blue.setWidth(2);
    QPen dark_blue;
    dark_blue.setBrush(QColor(67,100,169));
    dark_blue.setWidth(2);
    QPen purple;
    purple.setBrush(QColor(162,109,168));
    purple.setWidth(2);
    customPlot->yAxis->setTickLabelColor(QColor(240,26,36));

    customPlot->legend->setVisible(true);
    customPlot->legend->setBorderPen(pen);
    customPlot->legend->setFont(QFont(QFont().family(), 14));
    customPlot->legend->setIconSize(15,30);


    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignRight|Qt::AlignTop);
    graphic_up= new QCPGraph(customPlot->xAxis, customPlot->yAxis);
    graphic_down= new QCPGraph(customPlot->xAxis, customPlot->yAxis);
    graphic_right= new QCPGraph(customPlot->xAxis, customPlot->yAxis);
    graphic_left= new QCPGraph(customPlot->xAxis, customPlot->yAxis);
    graphic_sit= new QCPGraph(customPlot->xAxis, customPlot->yAxis);
    graphic_bat= new QCPGraph(customPlot->xAxis, customPlot->yAxis);
    graphic = new QCPGraph(customPlot->xAxis, customPlot->yAxis);
    lowPulseNorm = new QCPGraph(customPlot->xAxis, customPlot->yAxis);
    highPulseNorm = new QCPGraph(customPlot->xAxis, customPlot->yAxis);
    lowBreathNorm = new QCPGraph(customPlot->xAxis, customPlot->yAxis);
    highBreathNorm = new QCPGraph(customPlot->xAxis, customPlot->yAxis);
    graphic_breath = new QCPGraph(customPlot->xAxis, customPlot->yAxis);

    customPlot->addPlottable(graphic_breath);
    customPlot->addPlottable(graphic);
    customPlot->addPlottable(graphic_up);
    customPlot->addPlottable(graphic_down);
    customPlot->addPlottable(graphic_right);
    customPlot->addPlottable(graphic_left);
    customPlot->addPlottable(graphic_sit);
    customPlot->addPlottable(graphic_bat);

    graphic->setName(info);

    graphic_breath->setPen(pen2);
    graphic_breath->setAntialiased(false);
    graphic_breath->setLineStyle(QCPGraph::lsLine);

    lowPulseNorm->setPen(pulse_norm);
    lowPulseNorm->setAntialiased(false);
    lowPulseNorm->setLineStyle(QCPGraph::lsLine);
    highPulseNorm->setPen(pulse_norm);
    highPulseNorm->setAntialiased(false);
    highPulseNorm->setLineStyle(QCPGraph::lsLine);
    lowBreathNorm->setPen(breath_norm);
    lowBreathNorm->setAntialiased(false);
    lowBreathNorm->setLineStyle(QCPGraph::lsLine);
    highBreathNorm->setPen(breath_norm);
    highBreathNorm->setAntialiased(false);
    highBreathNorm->setLineStyle(QCPGraph::lsLine);
    graphic->setPen(pen);
    graphic->setAntialiased(false);
    graphic->setLineStyle(QCPGraph::lsLine);
    graphic_up->setPen(QPen(red));
    graphic_up->setAntialiased(false);
    graphic_up->setBrush(QBrush(QColor(217,49,40)));
    graphic_up->setLineStyle(QCPGraph::lsLine);
    graphic_down->setPen(QPen(yellow));
    graphic_down->setAntialiased(false);
    graphic_down->setBrush(QBrush(QColor(253,226,59)));
    graphic_down->setLineStyle(QCPGraph::lsLine);
    graphic_right->setPen(QPen(green));
    graphic_right->setAntialiased(false);
    graphic_right->setBrush(QBrush(QColor(120,183,50)));
    graphic_right->setLineStyle(QCPGraph::lsLine);
    graphic_left->setPen(QPen(blue));
    graphic_left->setAntialiased(false);
    graphic_left->setBrush(QBrush(QColor(95,199,228)));
    graphic_left->setLineStyle(QCPGraph::lsLine);
    graphic_sit->setPen(QPen(dark_blue));
    graphic_sit->setAntialiased(false);
    graphic_sit->setBrush(QBrush(QColor(67,100,169)));
    graphic_sit->setLineStyle(QCPGraph::lsLine);
    graphic_bat->setPen(QPen(purple));
    graphic_bat->setAntialiased(false);
    graphic_bat->setBrush(QBrush(QColor(162,109,168)));
    graphic_bat->setLineStyle(QCPGraph::lsLine);
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)),
            this, SLOT(slotRangeChanged(QCPRange)));
}

void MainWindow::setGraphicIntro(){
    double now = QDateTime::currentDateTime().toTime_t();
    startTime = now;
    interval = 1;
    for (int i=0; i<360; ++i){
        time.push_back(startTime + interval*i);
        lowBreath.push_back(12);
        highBreath.push_back(20);
        lowPulse.push_back(40);
        highPulse.push_back(218);
        pulse.push_back((qrand() % ((220 + 1) - 40) + 40));
        breathing.push_back((qrand() % ((20 + 1) - 12) + 12));
    }
    for (int i=0; i<60; ++i){
        position.push_back(1); }
    for (int i=60; i<120; ++i){
        position.push_back(2); }
    for (int i=120; i<180; ++i){
        position.push_back(3);}
    for (int i=180; i<240; ++i){
        position.push_back(4);}
    for (int i=240; i<300; ++i){
        position.push_back(5); }
    for (int i=300; i<360; ++i){
        position.push_back(6); }
    QVector<int> in;
    in.reserve(pulse.size());
    std::copy(position.cbegin(), position.cend(), std::back_inserter(in));
    for(int i=0;i<in.size();i++){
        if(in[i]==1){position_up.push_back(pulse[i]);}
        else{position_up.push_back(0);}}
    for(int i=0;i<in.size();i++){
        if(in[i]==2){position_down.push_back(pulse[i]);}
        else{position_down.push_back(0);} }
    for(int i=0;i<in.size();i++){
        if(in[i]==3){ position_right.push_back(pulse[i]);}
        else{position_right.push_back(0);}}
    for(int i=0;i<in.size();i++){
        if(in[i]==4){position_left.push_back(pulse[i]);}
        else{position_left.push_back(0);}}
    for(int i=0;i<in.size();i++){
        if(in[i]==5){position_sit.push_back(pulse[i]);}
        else{position_sit.push_back(0);}}
    for(int i=0;i<in.size();i++){
        if(in[i]==6){position_bat.push_back(pulse[i]);}
        else{position_bat.push_back(0);}}
    position_up.push_back(200);

    double all = pulse.size();
    int up_count=0;
    for (int i =0;i<pulse.size();i++){
        if(in[i]==1){ up_count+=1; }}
    int down_count=0;
    for (int i =0;i<pulse.size();i++){
        if(in[i]==2){down_count+=1;}}
    int right_count=0;
    for (int i =0;i<pulse.size();i++){
        if(in[i]==3){right_count+=1;}}
    int left_count=0;
    for (int i =0;i<pulse.size();i++){
        if(in[i]==4){left_count+=1;}}
    int sit_count=0;
    for (int i =0;i<pulse.size();i++){
        if(in[i]==5){sit_count+=1;}}
    int bat_count=0;
    for (int i =0;i<pulse.size();i++){
        if(in[i]==6){bat_count+=1;}}

     double up_percent  = (up_count*100)/all;
     double down_percent  = (down_count*100)/all;
     double right_percent  = (right_count*100)/all;
     double left_percent  = (left_count*100)/all;
     double sit_percent  = (sit_count*100)/all;
     double bat_percent  = (bat_count*100)/all;

    graphic->setData(time, pulse);
    graphic->setName("Пульс");
    graphic_breath->setData(time, breathing);
    graphic_breath->setName("Дыхание");
    graphic_up->setData(time, position_up);
    QString u = QString::number(up_percent,'f', 1);
    QString up_info = "На спине - "+u+"%";
    graphic_up->setName(up_info);
    graphic_down->setData(time, position_down);
    QString d = QString::number(down_percent,'f', 1);
    QString down_info = "На животе - "+d+"%";
    graphic_down->setName(down_info);
    graphic_right->setData(time, position_right);
    QString r = QString::number(right_percent,'f', 1);
    QString right_info = "На правом боку - "+r+"%";
    graphic_right->setName(right_info);
    graphic_left->setData(time, position_left);
    QString l = QString::number(left_percent,'f', 1);
    QString left_info = "На левом боку - "+l+"%";
    graphic_left->setName(left_info);
    graphic_sit->setData(time, position_sit);
    QString s = QString::number(sit_percent,'f', 1);
    QString sit_info = "Вертикально - "+s+"%";
    graphic_sit->setName(sit_info);
    graphic_bat->setData(time, position_bat);
    QString b = QString::number(bat_percent,'f', 1);
    QString bat_info = "Вверх ногами - "+b+"%";
    graphic_bat->setName(bat_info);
    lowBreathNorm->setData(time, lowBreath);
    highBreathNorm->setData(time, highBreath);
    lowPulseNorm->setData(time, lowPulse);
    highPulseNorm->setData(time, highPulse);
   // customPlot->addPlottable(highBreathNorm);
   // highBreathNorm->setName("Отклонение от нормы дыхания - 0%");
   // customPlot->addPlottable(highPulseNorm);
   // highPulseNorm->setName("Отклонение от нормы пульса - 0%");
    customPlot->legend->setVisible(true);
    customPlot->rescaleAxes();
    customPlot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::slotRangeChanged(const QCPRange &newRange)
{
   customPlot->xAxis->setDateTimeFormat((newRange.size() <= 86400)? "hh:mm:ss" : "dd MMM yy");
}
void MainWindow::on_addButton_clicked()
{
    form->show();
}

void MainWindow::on_downloadButton_clicked()
{
    double openStartTime{};
    QVector<double> openPulse{}, openBreath{}, openPosition{}, openTime{};
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Выберите файл"),
                QCoreApplication::applicationDirPath()+"/.../",
                "Text File (*.txt)"
                );
    if (!filename.isEmpty()){
        info = logic->getDFileInfo(filename);
        graphic->setName(info);
        openStartTime = logic->getInitTime(filename);
        openPulse = logic->getPulse(filename);
        openPosition = logic->getPosition(filename);
        openBreath = logic->getBreath(filename);
        for(int i=0;i<openPulse.size();i++){
            openTime.push_back(openStartTime+30*i);}
       QVector<double>  position_up{}, position_down{},
       position_right{}, position_left{},
       position_sit{}, position_bat{};
       setNorm(info);
       lowBreath.clear();
       highBreath.clear();
       lowPulse.clear();
       highPulse.clear();
       for(int i=0 ;i<openPulse.size();i++){
           lowBreath.push_back(lowBr);
           highBreath.push_back(highBr);
           lowPulse.push_back(lowPl);
           highPulse.push_back(highPl);
       }
       QVector<int> in;
       in.reserve(openPulse.size());
       std::copy(openPosition.cbegin(), openPosition.cend(), std::back_inserter(in));
       for(int i=0;i<in.size();i++){
           if(in[i]==1){position_up.push_back(openPulse[i]);}
           else{position_up.push_back(0);}}
       for(int i=0;i<in.size();i++){
           if(in[i]==2){position_down.push_back(openPulse[i]);}
           else{position_down.push_back(0);}}
       for(int i=0;i<in.size();i++){
           if(in[i]==3){position_right.push_back(openPulse[i]);}
           else{position_right.push_back(0);}}
       for(int i=0;i<in.size();i++){
           if(in[i]==4){position_left.push_back(openPulse[i]);}
           else{position_left.push_back(0);}}
       for(int i=0;i<in.size();i++){
           if(in[i]==5){position_sit.push_back(openPulse[i]);}
           else{position_sit.push_back(0);}}
       for(int i=0;i<in.size();i++){
           if(in[i]==6){ position_bat.push_back(openPulse[i]);}
           else{position_bat.push_back(0);}}

       double all = openPulse.size();
       int up_count=0;
       for (int i =0;i<openPulse.size();i++){
           if(in[i]==1){ up_count+=1;}}
       int down_count=0;
       for (int i =0;i<openPulse.size();i++){
           if(in[i]==2){down_count+=1;}}
       int right_count=0;
       for (int i =0;i<openPulse.size();i++){
           if(in[i]==3){right_count+=1;}}
       int left_count=0;
       for (int i =0;i<openPulse.size();i++){
           if(in[i]==4){left_count+=1;}}
       int sit_count=0;
       for (int i =0;i<openPulse.size();i++){
           if(in[i]==5){sit_count+=1;}}
       int bat_count=0;
       for (int i =0;i<openPulse.size();i++){
           if(in[i]==6){bat_count+=1;}}

        double up_percent  = (up_count*100)/all;
        double down_percent  = (down_count*100)/all;
        double right_percent  = (right_count*100)/all;
        double left_percent  = (left_count*100)/all;
        double sit_percent  = (sit_count*100)/all;
        double bat_percent  = (bat_count*100)/all;

        graphic->setLineStyle(QCPGraph::lsLine);
        graphic_up->setLineStyle(QCPGraph::lsLine);
        graphic_down->setLineStyle(QCPGraph::lsLine);
        graphic_right->setLineStyle(QCPGraph::lsLine);
        graphic_left->setLineStyle(QCPGraph::lsLine);
        graphic_sit->setLineStyle(QCPGraph::lsLine);
        graphic_bat->setLineStyle(QCPGraph::lsLine);
        graphic_breath->setLineStyle(QCPGraph::lsLine);
        lowBreathNorm->setLineStyle(QCPGraph::lsLine);
        highBreathNorm->setLineStyle(QCPGraph::lsLine);
        lowPulseNorm->setLineStyle(QCPGraph::lsLine);
        highPulseNorm->setLineStyle(QCPGraph::lsLine);

        graphic->setData(openTime, openPulse);
        graphic->setName(logic->getDFileInfo(filename));
        graphic_up->setData(openTime, position_up);
        QString u = QString::number(up_percent,'f', 1);
        QString up_info = "На спине - "+u+"%";
        graphic_up->setName(up_info);
        graphic_down->setData(openTime, position_down);
        QString d = QString::number(down_percent,'f', 1);
        QString down_info = "На животе - "+d+"%";
        graphic_down->setName(down_info);
        graphic_right->setData(openTime, position_right);
        QString r = QString::number(right_percent,'f', 1);
        QString right_info = "На правом боку - "+r+"%";
        graphic_right->setName(right_info);
        graphic_left->setData(openTime, position_left);
        QString l = QString::number(left_percent,'f', 1);
        QString left_info = "На левом боку - "+l+"%";
        graphic_left->setName(left_info);
        graphic_sit->setData(openTime, position_sit);
        QString s = QString::number(sit_percent,'f', 1);
        QString sit_info = "Вертикально - "+s+"%";
        graphic_sit->setName(sit_info);
        graphic_bat->setData(openTime, position_bat);
        QString b = QString::number(bat_percent,'f', 1);
        QString bat_info = "Вверх ногами - "+b+"%";
        graphic_bat->setName(bat_info);
        graphic_breath->setData(openTime, openBreath);
        graphic_breath->setName("Дыхание");
        lowBreathNorm->setData(openTime, lowBreath);
        highBreathNorm->setData(openTime, highBreath);
        lowPulseNorm->setData(openTime, lowPulse);
        highPulseNorm->setData(openTime, highPulse);
       // customPlot->addPlottable(highBreathNorm);
        QString brd = QString::number(breathDiviation(lowBr,highBr, openBreath));
        QString pld = QString::number(breathDiviation(lowPl,highPl, openPulse));
      //  highBreathNorm->setName("Отклонение от нормы дыхания - " + brd + "%");
      //  customPlot->addPlottable(highPulseNorm);
      //  highPulseNorm->setName("Отклонение от нормы пульса - " + pld + "%");
        customPlot->legend->setVisible(true);
        customPlot->rescaleAxes();
        customPlot->replot();
   }
}

void MainWindow::on_aboutButton_clicked()
{

}
void MainWindow::on_reZeroButton_clicked()
{
    graphic->setLineStyle(QCPGraph::lsNone);
    graphic_up->setLineStyle(QCPGraph::lsNone);
    graphic_down->setLineStyle(QCPGraph::lsNone);
    graphic_right->setLineStyle(QCPGraph::lsNone);
    graphic_left->setLineStyle(QCPGraph::lsNone);
    graphic_sit->setLineStyle(QCPGraph::lsNone);
    graphic_bat->setLineStyle(QCPGraph::lsNone);
    lowBreathNorm->setLineStyle(QCPGraph::lsNone);
    highBreathNorm->setLineStyle(QCPGraph::lsNone);
    lowPulseNorm->setLineStyle(QCPGraph::lsNone);
    highPulseNorm->setLineStyle(QCPGraph::lsNone);
    graphic_breath->setLineStyle(QCPGraph::lsNone);
    customPlot->legend->setVisible(false);
    customPlot->replot();
}

void MainWindow::on_settingButton_clicked()
{
    Settings setting;
        setting.exec();
        setting.getPulseOverlay();
        overlays(setting.getPulseOverlay(), setting.getBreathOverlay(), setting.getPositionOverlay(),
                 setting.getPulseNormOverlay(), setting.getBreathNormOverlay(), setting.getLegendOverlay());
}

void MainWindow::on_SDButton_clicked(){
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Выберите файл"),
                QCoreApplication::applicationDirPath()+"/.../",
                "Text File (*.txt)"
                );
    if (!filename.isEmpty()){
        QString file = QFileDialog::getSaveFileName(
                    this,
                    tr("Выберитe папку для записи файла"),
                    filename,
                    "Text File (*.txt)"
                    );
        QFile::copy(filename,file);
        QString mod = file;
        QString path = mod.remove(mod.size() - 11, mod.size());
        QString newName = path + logic->getDFileInfo(file) + ".txt";
        QFile::rename(file, newName);
    }
}

void MainWindow::setNorm(QString newYear){
    QDate current_date = QDate::currentDate();
    int current_year = current_date.year();
    int size = newYear.size()-4;
    newYear.remove(0,size);
    int patientYear = current_year - newYear.toInt();
    if(patientYear > 7 && patientYear < 11){
         lowBr = 18;
         highBr = 20;
         lowPl = 68;
         highPl = 108;
    }
    else if(patientYear > 9 && patientYear < 13){
        lowBr = 16;
        highBr = 20;
        lowPl = 60;
        highPl = 100;}
    else if(patientYear > 11 && patientYear < 16){
        lowBr = 16;
        highBr = 20;
        lowPl = 55;
        highPl = 95;}
    else if(patientYear > 14 && patientYear < 51){
        lowBr = 16;
        highBr = 20;
        lowPl = 60;
        highPl = 80;
    }
    else if(patientYear > 49 && patientYear < 61){
        lowBr = 16;
        highBr = 20;
        lowPl = 64;
        highPl = 84;
    }
    else if(patientYear > 59 && patientYear < 81){
        lowBr = 16;
        highBr = 20;
        lowPl = 69;
        highPl = 80;
    }
}

double MainWindow::breathDiviation(int const& low, int const& high, QVector <double> newBreath){
    int count = 0;
    for(int i =0 ;i < newBreath.size(); i++){
        if(newBreath[i] < low || newBreath[i] > high){
            count +=1; }
        else{}
    }
     double breathDiviationPercent  = (count*100)/newBreath.size();
     return breathDiviationPercent;
}
double MainWindow::pulseDiviation(int const& low, int const& high, QVector <double> newPulse){
    int count = 0;
    for(int i =0 ;i < newPulse.size(); i++){
        if(newPulse[i] < low || newPulse[i] > high){ count +=1; }
        else{}
    }
     double pulseDiviationPercent  = (count*100)/newPulse.size();
     return pulseDiviationPercent;
}

void MainWindow::overlays(bool const& pulse, bool const& breath, bool const& position,
                          bool const& pulseNorm, bool const& breathNorm, bool const& legend){
    if(pulse == true){graphic->setLineStyle(QCPGraph::lsLine);
    } else {graphic->setLineStyle(QCPGraph::lsNone);}
    if(breath == true){graphic_breath->setLineStyle(QCPGraph::lsLine);
    } else {graphic_breath->setLineStyle(QCPGraph::lsNone);}
    if(position == true){graphic_up->setLineStyle(QCPGraph::lsLine);
        graphic_down->setLineStyle(QCPGraph::lsLine);
        graphic_right->setLineStyle(QCPGraph::lsLine);
        graphic_left->setLineStyle(QCPGraph::lsLine);
        graphic_sit->setLineStyle(QCPGraph::lsLine);
        graphic_bat->setLineStyle(QCPGraph::lsLine);
    } else { graphic_up->setLineStyle(QCPGraph::lsNone);
        graphic_down->setLineStyle(QCPGraph::lsNone);
        graphic_right->setLineStyle(QCPGraph::lsNone);
        graphic_left->setLineStyle(QCPGraph::lsNone);
        graphic_sit->setLineStyle(QCPGraph::lsNone);
        graphic_bat->setLineStyle(QCPGraph::lsNone);}
    if(pulseNorm == true){lowPulseNorm->setLineStyle(QCPGraph::lsLine);
        highPulseNorm->setLineStyle(QCPGraph::lsLine);
    } else {lowPulseNorm->setLineStyle(QCPGraph::lsNone);
        highPulseNorm->setLineStyle(QCPGraph::lsNone);}
    if(breathNorm == true){lowBreathNorm->setLineStyle(QCPGraph::lsLine);
        highBreathNorm->setLineStyle(QCPGraph::lsLine);
    } else {lowBreathNorm->setLineStyle(QCPGraph::lsNone);
        highBreathNorm->setLineStyle(QCPGraph::lsNone);}
    if(legend == true){customPlot->legend->setVisible(true);;
    } else {customPlot->legend->setVisible(false);}
    customPlot->replot();
}
