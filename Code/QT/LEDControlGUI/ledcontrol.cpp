#include "ledcontrol.h"
#include "ui_ledcontrol.h"

LEDControl::LEDControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LEDControl)
{
    ui->setupUi(this);
    QObject::connect(this, SIGNAL(sendColor(char, char)),
                     &m_arduinoInterface, SLOT(sendColorToArduino(char, char)));

    QObject::connect(&m_arduinoInterface, SIGNAL(updateCntSent(int)),
                     this, SLOT(updateCntSent(int)));
    QObject::connect(&m_arduinoInterface, SIGNAL(updateCntReceived(int)),
                     this, SLOT(updateCntReceived(int)));

    updateCntSent(0);
    updateCntReceived(0);
    reset();
}

LEDControl::~LEDControl()
{
    delete ui;
}

void LEDControl::on_hsRed_valueChanged(int value)
{
    onSliderMoved(LEDColor::Red, value);
}

void LEDControl::on_hsBlue_valueChanged(int value)
{
    onSliderMoved(LEDColor::Blue, value);
}

void LEDControl::on_hsGreen_valueChanged(int value)
{
    onSliderMoved(LEDColor::Green, value);
}

void LEDControl::onSliderMoved(LEDColor sliderColor, int value)
{
    QLineEdit* txtValue;

    switch(sliderColor) {
    case LEDColor::Red:
        txtValue = ui->txtRed;
        break;
    case LEDColor::Green:
        txtValue = ui->txtGreen;
        break;
    case LEDColor::Blue:
        txtValue = ui->txtBlue;
        break;
    }

    txtValue->setText(QString::number(value) + "%");

    emit sendColor(sliderColor, static_cast<char>(value));
}

void LEDControl::on_pbClose_clicked()
{
    close();
}

void LEDControl::on_pbOnOff_clicked()
{
    bool bNewValue = !ui->hsRed->isEnabled();
    setSlidersEnabled(bNewValue);

    if (bNewValue) {
        sendAllColors(static_cast<char>(ui->hsRed->value()),
                      static_cast<char>(ui->hsGreen->value()),
                      static_cast<char>(ui->hsBlue->value()));
    } else
    {
        sendAllColors(0, 0, 0);
    }
}

void LEDControl::sendAllColors(char redValue, char greenValue, char blueValue)
{
    emit sendColor(LEDColor::Red, redValue);
    emit sendColor(LEDColor::Green, greenValue);
    emit sendColor(LEDColor::Blue, blueValue);
}

void LEDControl::on_pbReset_clicked()
{
    reset();
}

void LEDControl::reset()
{
    ui->hsRed->setValue(DEFAULT_LED_VALUE);
    ui->hsGreen->setValue(DEFAULT_LED_VALUE);
    ui->hsBlue->setValue(DEFAULT_LED_VALUE);

    setSlidersEnabled(true);
}

void LEDControl::setSlidersEnabled(bool bEnabled)
{
    ui->hsRed->setEnabled(bEnabled);
    ui->hsGreen->setEnabled(bEnabled);
    ui->hsBlue->setEnabled(bEnabled);
}

void LEDControl::updateCntSent(int iCount)
{
    ui->lbl_cntSent->setText("Gesendet: " + QString::number(iCount));
}

void LEDControl::updateCntReceived(int iCount)
{
    ui->lbl_cntReceived->setText("Empfangen: " + QString::number(iCount));
}
