#include <Arduino.h>

const int PIN_RED = 5;
const int PIN_GREEN = 6;
const int PIN_BLUE = 3;

enum LEDColor : char {
    Red = 101,
    Green = 102,
    Blue = 103
};

int m_valueRed = 0;
int m_valueGreen = 0;
int m_valueBlue = 0;

char m_incomingByte = 0;
LEDColor m_activeColor;

int m_messageCounter = 0;

void setup() {
    // put your setup code here, to run once:

    pinMode(PIN_RED, OUTPUT);
    pinMode(PIN_GREEN, OUTPUT);
    pinMode(PIN_BLUE, OUTPUT);

    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
    while (Serial.available() > 0) {
        m_incomingByte = Serial.read();

        if (m_incomingByte > 100) {
            // color identifier
            m_activeColor = (LEDColor) m_incomingByte;

        } else {
            // color value
            int newColorValue = m_incomingByte / 100.0 * 255.0;

            switch (m_activeColor)
            {
            case LEDColor::Red:
                m_valueRed = newColorValue;
                break;
            case LEDColor::Green:
                m_valueGreen = newColorValue;
                break;
            case LEDColor::Blue:
                m_valueBlue = newColorValue;
                break;
            }

            // Message Counter
            m_messageCounter++;
            Serial.write((char*) &m_messageCounter, 2);
        }
    }

    analogWrite(PIN_RED, m_valueRed);
    analogWrite(PIN_GREEN, m_valueGreen);
    analogWrite(PIN_BLUE, m_valueBlue);
}