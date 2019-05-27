#include <Arduino.h>

const int PIN_LED = 12;                         // Arduino Pin an dem die LED angeschlossen ist
const String MSG = "Willkommen zu API 2019";    // Zu sendende Nachricht - ändert sich während der Programmlaufzeit nicht
String m_MsgMorse = "";                         // Variable zur Speicherung der in Morse-Code konvertierten Nachricht

const int DIT = 100;                            // Dauer eines Dit (.) in Millisekunden
const int DAH = 3 * DIT;                        // Dauer eines Dah (-) in Millisekunden

/** \brief Konvertiert einen Buchstaben (A-Z), eine Zahl (0-9) oder ein Satzzeichen in Morsecode.
 *  \param sChar Zu konvertierender Buchstabe / Zahl / Satzzeichen als String
 *  \return Morsecode als String. "." = Dit; "-" = Dah
 */
String charToMorse(String sChar) {
    sChar.toUpperCase();

    if (sChar.equals("A")) {
        return ".-";
    } else if (sChar.equals("B")) {
        return "-...";
    } else if (sChar.equals("C")) {
        return "-.-.";
    } else if (sChar.equals("D")) {
        return "-..";
    } else if (sChar.equals("E")) {
        return ".";
    } else if (sChar.equals("F")) {
        return "..-.";
    } else if (sChar.equals("G")) {
        return "--.";
    } else if (sChar.equals("H")) {
        return "....";
    } else if (sChar.equals("I")) {
        return "..";
    } else if (sChar.equals("J")) {
        return ".---";
    } else if (sChar.equals("K")) {
        return "-.-";
    } else if (sChar.equals("L")) {
        return ".-..";
    } else if (sChar.equals("M")) {
        return "--";
    } else if (sChar.equals("N")) {
        return "-.";
    } else if (sChar.equals("O")) {
        return "---";
    } else if (sChar.equals("P")) {
        return ".--.";
    } else if (sChar.equals("Q")) {
        return "--.-";
    } else if (sChar.equals("R")) {
        return ".-.";
    } else if (sChar.equals("S")) {
        return "...";
    } else if (sChar.equals("T")) {
        return "-";
    } else if (sChar.equals("U")) {
        return "..-";
    } else if (sChar.equals("V")) {
        return "...-";
    } else if (sChar.equals("W")) {
        return ".--";
    } else if (sChar.equals("X")) {
        return "-..-";
    } else if (sChar.equals("Y")) {
        return "-.--";
    } else if (sChar.equals("Z")) {
        return "--..";
    } else if (sChar.equals("1")) {
        return ".----";
    } else if (sChar.equals("2")) {
        return "..---";
    } else if (sChar.equals("3")) {
        return "...--";
    } else if (sChar.equals("4")) {
        return "....-";
    } else if (sChar.equals("5")) {
        return ".....";
    } else if (sChar.equals("6")) {
        return "-....";
    } else if (sChar.equals("7")) {
        return "--...";
    } else if (sChar.equals("8")) {
        return "---..";
    } else if (sChar.equals("9")) {
        return "----.";
    } else if (sChar.equals("0")) {
        return "-----";
    } else if (sChar.equals(".")) {
        return ".-.-.-";
    } else if (sChar.equals(",")) {
        return "--..--";
    } else if (sChar.equals(":")) {
        return "---...";
    } else if (sChar.equals(";")) {
        return "-.-.-.";
    } else if (sChar.equals("?")) {
        return "..--..";
    } else if (sChar.equals("-")) {
        return "-....-";
    } else if (sChar.equals("_")) {
        return "..--.-";
    } else if (sChar.equals("(")) {
        return "-.--.";
    } else if (sChar.equals(")")) {
        return "-.--.-";
    } else if (sChar.equals("'")) {
        return ".----.";
    } else if (sChar.equals("=")) {
        return "-...-";
    } else if (sChar.equals("+")) {
        return ".-.-.";
    } else if (sChar.equals("/")) {
        return "-..-.";
    } else if (sChar.equals("@")) {
        return ".--.-.";
    } else {
        return "";
    }
}

/** \brief Konvertiert eine gesamte Text-Nachricht in Morsecode.
 *  \param sMsg Zu konvertierende Nachricht als String
 *  \return Morsecode als String. "." = Dit; "-" = Dah; "#" Pause zwischen Buchstaben; "/" Pause zwischen Wörtern
 */
String messageToMorse(String sMsg) {
    String sRes = "";
    for (unsigned int i = 0; i < sMsg.length(); i++) {
        String sChar = sMsg.substring(i, i + 1);

        if (sChar.equals(" ")) {
            // Pause zwischen Wörtern einfügen
            // -> Pause zwischen Buchstaben entfernen
            if (sRes.endsWith("#"))
                sRes = sRes.substring(0, sRes.length() - 1);
            sRes += "/";

        } else {
            // Pause zwischen Buchstaben einfügen
            sRes += charToMorse(sChar) + "#";
        }
    }

    // Nachricht nicht mit Pause enden lassen
    // -> Pause-Zeichen entfernen
    if (sRes.endsWith("#") || sRes.endsWith("/"))
        sRes = sRes.substring(0, sRes.length() - 1);
    
    return sRes;
}

/** \brief Sendet einen Morse-Code durch entsprechende Steuerung einer an PIN_LED angeschlossenen LED.
 *  \param sMorse Zu sendender Morse-Code as String. Formatierung entsprechend Ausgabe von messageToMorse()
 */
void sendMorse(String sMorse) {
    // LED ausschalten
    digitalWrite(PIN_LED, LOW);

    String sSymbol = "";
    for (unsigned int i = 0; i < sMorse.length(); i++) {
        sSymbol = sMorse.substring(i, i + 1);
        if (sSymbol.equals(".")) {
            // Dit
            digitalWrite(PIN_LED, HIGH);
            delay(DIT);
            digitalWrite(PIN_LED, LOW);
            delay(DIT);
        } else if (sSymbol.equals("-")) {
            // DAH
            digitalWrite(PIN_LED, HIGH);
            delay(DAH);
            digitalWrite(PIN_LED, LOW);
            delay(DIT);
        } else if (sSymbol.equals("#")) {
            // Buchstabenabstand = DAH
            // Jedem Symbol folgte bereits ein DIT
            // -> Warte 1 DAH - 1 DIT = 2 DIT
            delay(2 * DIT);
        } else if (sSymbol.equals("/")) {
            // Wortabstand = 7 DIT
            // Jedem Symbol folgte bereits ein DIT
            // -> Warte 7 DIT - 1 DIT = 6 DIT
            delay(6 * DIT);
        }
    }

    // Beende Nachricht mit 10 DIT
    delay(9 * DIT);
}

void setup() {
    // put your setup code here, to run once:

    // Serielle Kommunikation mit PC starten.
    Serial.begin(9800);

    // Anfangszustand herstellen
    // -> LED ausschalten
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, LOW);

    // Nachricht einmalig in Morse-Code konvertieren und Nachricht anzeigen.
    // Nachricht und Morse-Code ändern sich während Programmlaufzeit nicht
    // -> Konvertierung erfolt in setup() und NICHT in loop()
    m_MsgMorse = messageToMorse(MSG);
    Serial.println("Nachricht: " + MSG);
}

void loop() {
    // put your main code here, to run repeatedly:

    // In setup() bereits als Morse-Code konvertierte Nachricht fortlaufend senden.
    // -> Konvertierung erfolgt NICHT hier, da dies unnötigen Rechenaufwand darstellen würde (Nachricht ändert sich bei Schleifendurchlauf ja nicht).
    sendMorse(m_MsgMorse);
}