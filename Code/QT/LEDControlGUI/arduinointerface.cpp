#include "arduinointerface.h"

ArduinoInterface::ArduinoInterface(QObject *parent) : QObject(parent)
{
    for (int i = 0; i < 8; i++) {
        m_receiveBuf[i] = 0;
    }

    m_serialPort.setPortName("COM6");
    m_serialPort.setBaudRate(9600);
    m_serialPort.setParity(QSerialPort::Parity::NoParity);
    m_serialPort.setStopBits(QSerialPort::StopBits::OneStop);
    m_serialPort.setDataBits(QSerialPort::DataBits::Data8);
    m_serialPort.open(QIODevice::ReadWrite);

    // Diese Zeile hatte ich in der Übung vergessen.
    // -> Man muss seine Funktionen halt nicht nur schreiben, sondern auch
    //    sicherstellen dass sie aufgerufen werden... *facepalm*
    QObject::connect(&m_serialPort, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void ArduinoInterface::sendColorToArduino(char colorIdentifier, char colorValue)
{
    m_bytes2send[0] = colorIdentifier;
    m_bytes2send[1] = colorValue;

    if (m_serialPort.write(m_bytes2send, 2) > -1) {
        m_msgCounterSent++;
        emit updateCntSent(m_msgCounterSent);
    }
}

void ArduinoInterface::readyRead()
{
    while (m_serialPort.bytesAvailable() > 0) {
        m_serialPort.read(&m_receiveBuf[m_receiveIndex], 1);
        m_receiveIndex++;

        if (m_receiveIndex >= 2) {
            m_receiveIndex = 0;
            int msgCountReceivedByArduino = *((int*) m_receiveBuf);
            emit updateCntReceived(msgCountReceivedByArduino);
        }
    }
}
