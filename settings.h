#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QDialog *parent = nullptr);
    bool getPulseOverlay();
    bool getBreathOverlay();
    bool getPositionOverlay();
    bool getPulseNormOverlay();
    bool getBreathNormOverlay();
    bool getLegendOverlay();
    void setTheme();
    ~Settings();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
