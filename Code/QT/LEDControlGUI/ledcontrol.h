#ifndef LEDCONTROL_H
#define LEDCONTROL_H

#include <QWidget>

namespace Ui {
class LEDControl;
}

class LEDControl : public QWidget
{
    Q_OBJECT

public:
    explicit LEDControl(QWidget *parent = nullptr);
    ~LEDControl();

    const char DEFAULT_LED_VALUE = 10;

    enum LEDColor : char {
        Red = 101,
        Green = 102,
        Blue = 103
    };

private:
    Ui::LEDControl *ui;

    void onSliderMoved(LEDColor sliderColor, int value);
    void setSlidersEnabled(bool bEnabled);
    void sendAllColors(char redValue, char greenValue, char blueValue);
    void reset();

signals:
    void sendColor(char colorIdentifier, char colorValue);
private slots:
    void on_hsRed_valueChanged(int value);
    void on_hsBlue_valueChanged(int value);
    void on_hsGreen_valueChanged(int value);
    void on_pbClose_clicked();
    void on_pbOnOff_clicked();
    void on_pbReset_clicked();
};

#endif // LEDCONTROL_H
