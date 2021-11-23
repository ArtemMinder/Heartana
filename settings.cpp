#include "settings.h"
#include "ui_settings.h"
#include <QtCharts>

Settings::Settings(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    setTheme();
}

bool Settings::getPulseOverlay(){
    if(ui->pulseBox->isChecked() == true){ return true;
    }else{return false;}
}
bool Settings::getBreathOverlay(){
    if(ui->breathBox->isChecked() == true){ return true;
    }else{return false;}
}
bool Settings::getPositionOverlay(){
    if(ui->positionBox->isChecked() == true){ return true;
    }else{return false;}
}
bool Settings::getPulseNormOverlay(){
    if(ui->pulseNorm->isChecked() == true){ return true;
    }else{return false;}
}
bool Settings::getBreathNormOverlay(){
    if(ui->breathNorm->isChecked() == true){ return true;
    }else{return false;}
}
bool Settings::getLegendOverlay(){
    if(ui->LegendBox->isChecked() == true){ return true;
    }else{return false;}
}
void Settings::setTheme(){
    ui->themeComboBox->addItem("Light", QChart::ChartThemeLight);
    ui->themeComboBox->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
    ui->themeComboBox->addItem("Dark", QChart::ChartThemeDark);
    ui->themeComboBox->addItem("Brown Sand", QChart::ChartThemeBrownSand);
    ui->themeComboBox->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
    ui->themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
    ui->themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
    ui->themeComboBox->addItem("Qt", QChart::ChartThemeQt);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_pushButton_clicked()
{
    this->close();
}
