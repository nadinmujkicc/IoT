// #include <Arduino.h>
// #include "WiFi.h"
// #include "WebSocketsClient.h"
// #include <ArduinoJson.h>

// // --- TVOJI PODACI ZA WIFI I LINUX SERVER ---
// const char *ssid = "nadin";
// const char *password = "12345678";
// const char *serverIP = "10.252.254.48"; // Tvoj Linux IP (.48)

// // --- JASNO DEFINIRANI PINOVI ---
// const int pinGlavnaLED = 4;        // Žuta LED je na PINU 4
// const int pinUgradjenaLED = 2;     // Ugrađena plava LED na ESP32 (Služi samo za alarm)
// const int nozicaFotoupornika = 36; // Fotootpornik je siguran na VP (36)

// int vrednostFotoupornika;
// int prethodnaVrednostFoto = 0;

// bool glavnaLEDMoraSvetleti = false;
// bool uAlarmu = false;
// unsigned long vremeNaredbe = 0;
// unsigned long prethodnoVremeTreptanja = 0;
// bool stanjeUgradjeneLED = false;

// WebSocketsClient webSocket;

// void webSocketEvent(WStype_t type, uint8_t *payload, size_t length)
// {
//     if (type == WStype_TEXT)
//     {
//         StaticJsonDocument<256> doc;
//         DeserializationError error = deserializeJson(doc, payload, length);
//         if (error)
//             return;

//         const char *tip = doc["tipSporočila"];
//         if (tip != nullptr && strcmp(tip, "LED") == 0)
//         {
//             int vrednost = doc["vrednost"];
//             if (vrednost == 1) // Kliknuto VKLOP
//             {
//                 glavnaLEDMoraSvetleti = true;
//                 vremeNaredbe = millis(); // Počinje odbrojavanje od 3 sekunde
//                 uAlarmu = false;
//                 digitalWrite(pinGlavnaLED, HIGH);   // Pali žutu na pinu 4
//                 digitalWrite(pinUgradjenaLED, LOW); // Gasi plavu alarmnu
//             }
//             else // Kliknuto IZKLOP
//             {
//                 glavnaLEDMoraSvetleti = false;
//                 uAlarmu = false;
//                 digitalWrite(pinGlavnaLED, LOW);
//                 digitalWrite(pinUgradjenaLED, LOW);

//                 // Reset statusa na Linux webu
//                 DynamicJsonDocument statusDoc(128);
//                 statusDoc["tipSporočila"] = "status";
//                 statusDoc["stanje"] = "OK";
//                 String statusStr;
//                 serializeJson(statusDoc, statusStr);
//                 webSocket.sendTXT(statusStr);
//             }
//         }
//     }
// }

// void setup()
// {
//     Serial.begin(115200);
//     delay(1000);

//     WiFi.begin(ssid, password);
//     while (WiFi.status() != WL_CONNECTED)
//     {
//         delay(500);
//     }

//     webSocket.begin(serverIP, 8811);
//     webSocket.onEvent(webSocketEvent);

//     // KLJUČNI DIO: Postavljamo pin 4 kao IZLAZ da može dati struju diodi!
//     pinMode(pinGlavnaLED, OUTPUT);
//     pinMode(pinUgradjenaLED, OUTPUT);

//     digitalWrite(pinGlavnaLED, LOW);
//     digitalWrite(pinUgradjenaLED, LOW);
// }

// void loop()
// {
//     webSocket.loop();

//     // Čitanje fotootpornika s VP pina
//     vrednostFotoupornika = analogRead(nozicaFotoupornika);

//     // --- LOGIKA: PREGOREVANJE NAKON TOČNO 3 SEKUNDE ---
//     if (glavnaLEDMoraSvetleti && !uAlarmu)
//     {
//         if (millis() - vremeNaredbe > 3000)
//         {
//             uAlarmu = true;
//             glavnaLEDMoraSvetleti = false;

//             digitalWrite(pinGlavnaLED, LOW); // Žuta se gasi na pinu 4 (pregori)

//             // Javljamo Linux serveru kvar
//             DynamicJsonDocument statusDoc(128);
//             statusDoc["tipSporočila"] = "status";
//             statusDoc["stanje"] = "ALARM";
//             String statusStr;
//             serializeJson(statusDoc, statusStr);
//             webSocket.sendTXT(statusStr);
//         }
//     }

//     // Dok traje alarm, ugrađena plava LED na pločici (pin 2) bljeska
//     if (uAlarmu)
//     {
//         if (millis() - prethodnoVremeTreptanja > 150)
//         {
//             prethodnoVremeTreptanja = millis();
//             stanjeUgradjeneLED = !stanjeUgradjeneLED;
//             digitalWrite(pinUgradjenaLED, stanjeUgradjeneLED ? HIGH : LOW);
//         }
//     }

//     // Slanje vrijednosti fotootpornika na Linux grafikon
//     if (abs(vrednostFotoupornika - prethodnaVrednostFoto) > 20)
//     {
//         DynamicJsonDocument fotoDoc(128);
//         fotoDoc["tipSporočila"] = "fotoupornik";
//         fotoDoc["vrednost"] = vrednostFotoupornika;
//         String fotoStr;
//         serializeJson(fotoDoc, fotoStr);
//         webSocket.sendTXT(fotoStr);
//         prethodnaVrednostFoto = vrednostFotoupornika;
//     }

//     delay(10);
// }