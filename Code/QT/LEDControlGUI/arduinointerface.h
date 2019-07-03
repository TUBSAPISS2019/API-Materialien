#ifndef ARDUINOINTERFACE_H
#define ARDUINOINTERFACE_H

#include <QObject>
#include <QSerialPort>

class ArduinoInterface : public QObject
{
    Q_OBJECT
public:
    explicit ArduinoInterface(QObject *parent = nullptr);

private:
    QSerialPort m_serialPort;
    char m_bytes2send[2];

    char m_receiveBuf[8];
    int m_receiveIndex = 0;

    int m_msgCounterSent = 0;

signals:
    void updateCntSent(int iCount);
    void updateCntReceived(int iCount);

public slots:
    void sendColorToArduino(char colorIdentifier, char colorValue);

    void readyRead();
};

#endif // ARDUINOINTERFACE_H
