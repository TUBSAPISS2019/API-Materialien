#include <iostream>
#include <fstream>
#include <string>

int main()
{
    // Standardwerte
    // -> Sollten immer in Variablen definiert werden um sie bei Bedarf nur an einer Stelle
    //    im Programmcode ändern zu müssen.
    std::string sWelcomeMsgFileName = "welcome.conf";
    std::string sDefaultMsg = "Hello World!";

    // Begrüßungstext aus Datei laden
    std::string sWelcome = sDefaultMsg;
    std::ifstream readFile;
    readFile.open(sWelcomeMsgFileName);
    if (readFile.is_open())
    {
        // Datei ist vorhanden und konnte geöffnet werden
        std::string sLine;
        std::getline(readFile, sLine);  // Lese die erste Zeile der Datei aus (eine Begrüßung ist ja kein Roman...)
        readFile.close();   // WICHTIG!!! Datei so schnell wie möglich wieder schließen

        if (sLine.length() > 0)
            sWelcome = sLine;   // In der Datei stand auch tatsächlich ein Text...
    }

    // Begrüßung anzeigen
    std::cout << sWelcome << std::endl;

    // Nutzer über seine Eingabemöglichkeiten informieren und Nutzereingabe abwarten.
    std::cout << "I am sure you would like to edit the welcome message..." << std::endl;
    std::cout << "Or type..." << std::endl
                 << "   ... 'exit' to leave without changing the message" << std::endl
                 << "   ... 'reset' to reset the message to the default value." << std::endl;
    std::cout << "Enter new welcome message: ";
    std::string sUserInput;
    std::getline(std::cin, sUserInput); // std::cin kann genauso ausgelesen werden wie eine Datei...

    if (sUserInput == "exit")
    {
        // Programm beenden
        // -> Return verlässt eine Funktion sofort. Der Wert dahinter wird als Ergebnis der Funktion
        //    zurück gegeben.
        //    -> Hier sind wir gerade in der Funktion main(). D. h. Hauptroutine des Programmes.
        //       Sobald main() beendet wird, beendet sich das Programm.
        //    -> Der Rückgabewert von main() wird vom Betriebssystem folgendermaßen interpretiert:
        //          0 : Programm wurde planmäßig beendet.
        //       != 0 : Programm wurde aufgrund eines Fehlers beendet.
        return 0;
    }
    else if (sUserInput == "reset")
    {
        // Wir setzten sUserInput auf den Wert der Standardbegrüßung und lassen
        // ansonsten das Programm weiterlaufen als ob der Nutzer eine neue Nachricht eingegeben hat.
        // Alternative wäre hier ebenfalls die Dateien zu aktualisieren, aber wir wollen ja keinen Code
        // doppelt schreiben!
        // -> Tipp: Immer versuchen soviel Code wie möglich mehrfach zu verwenden.
        //    -> Durch logischen Programmablauf (wie hier) oder durch das schreiben eigener Funktionen.
        //    -> Copy-And-Paste sollte an vielen Stellen als Tabu betrachtet werden ;-)
        std::cout << "Resetting message to default value." << std::endl;
        sUserInput = sDefaultMsg;
    }

    if (sUserInput.length() > 0)
    {
        // Es ist eine neue Nachricht vorhanden
        // -> In welcome.conf aktualisieren und in log.txt protokollieren.
        std::cout << "New message is: " << sUserInput << std::endl;

        std::ofstream writeFile;
        writeFile.open(sWelcomeMsgFileName);    // Standardmäßig wird die Datei (falls vorhanden) überschrieben.
        writeFile << sUserInput << std::endl;
        writeFile.close();                      // WICHTIG: Datei so schnell wie möglich wieder schließen.

        std::ofstream logFile;
        logFile.open("log.txt", std::ios::app); // Option std::ios::app -> Neuer Inhalt wird an die Datei angehängt.
        logFile << sUserInput << std::endl;
        logFile.close();                        // WICHTIG: Datei so schnell wie möglich wieder schließen.
    }
    else
    {
        // Nutzer hat Quatsch gemacht und nichts eingegeben.
        // -> Kein Problem: Wir informieren ihn einfach darüber und sagen was wir daher tun
        //    -> Tipp: Gute Programme sollten den Nutzer immer auf dem laufenden halten darüber was gerade passiert.
        //       Insbesondere bei länger laufenden Operationen.
        std::cout << "No message entered. Keeping the current one." << std::endl;
    }

    // Programm nicht gleich beenden, sondern auf Return warten um dem Nutzer Zeit zu geben unsere Nachrichten
    // in Ruhe lesen zu können.
    std::cout << "Press Return to continue...";
    std::cin.get();
    return 0;
}
