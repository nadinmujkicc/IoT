// #include <Arduino.h>
// #include "WiFi.h"
// #include "WebSocketsClient.h"
// #include <ArduinoJson.h>

// const char *ssid = "nadin";
// const char *password = "12345678";
// const char *serverIP = "10.252.254.201"; // Tvoja IP adresa (.201)
// // const char *serverIP = " 192.168.1.162";

// // --- JASNO DEFINIRANI PINOVI ---
// const int pinGlavnaLED = 4;        // Žuta LED (Radi stalno od početka)
// const int pinUgradjenaLED = 2;     // Ugrađena plava LED (Pali se samo za ALARM)
// const int nozicaFotoupornika = 36; // Fotootpornik (Prati svjetlo žute diode)

// int vrednostFotoupornika;
// int prethodnaVrednostFoto = 0;

// bool uAlarmu = false;
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

//         // Gumbi na webu ti sada služe za RUČNI RESET ALARMA ako zatreba
//         if (tip != nullptr && strcmp(tip, "LED") == 0)
//         {
//             int vrednost = doc["vrednost"];
//             if (vrednost == 0) // Ako klikneš IZKLOP / RESET na webu
//             {
//                 uAlarmu = false;
//                 digitalWrite(pinGlavnaLED, HIGH);   // Ponovno upali glavnu diodu
//                 digitalWrite(pinUgradjenaLED, LOW); // Ugasi alarmnu plavu

//                 // Javi webu da je sustav ponovno u redu
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

//     pinMode(pinGlavnaLED, OUTPUT);
//     pinMode(pinUgradjenaLED, OUTPUT);

//     // --- KLJUČNA IZMJENA ---
//     // Žuta dioda se pali ODMAH na startu i sustav radi normalno
//     digitalWrite(pinGlavnaLED, HIGH);
//     digitalWrite(pinUgradjenaLED, LOW);
// }

// void loop()
// {
//     webSocket.loop();

//     // Stalno čitamo vrijednost fotootpornika
//     vrednostFotoupornika = analogRead(nozicaFotoupornika);

//     // --- LOGIKA NADZORA ---
//     // Ako je sustav u redu (nije već u alarmu), pratimo pad svjetla
//     if (!uAlarmu)
//     {
//         // Ako vrijednost padne ispod 2000 (prekrio si prstom ili ugasio diodu)
//         if (vrednostFotoupornika < 2000)
//         {
//             uAlarmu = true; // Aktiviraj alarmno stanje

//             digitalWrite(pinGlavnaLED, LOW); // Možemo je ugasiti jer simuliramo da je pala/crkla

//             // Odmah šaljemo webu poruku o kvaru da pocrveni ekran
//             DynamicJsonDocument statusDoc(128);
//             statusDoc["tipSporočila"] = "status";
//             statusDoc["stanje"] = "ALARM";
//             String statusStr;
//             serializeJson(statusDoc, statusStr);
//             webSocket.sendTXT(statusStr);
//         }
//     }

//     // Ako se aktivirao alarm, plava ugrađena LED počinje bljeskati
//     if (uAlarmu)
//     {
//         if (millis() - prethodnoVremeTreptanja > 150)
//         {
//             prethodnoVremeTreptanja = millis();
//             stanjeUgradjeneLED = !stanjeUgradjeneLED;
//             digitalWrite(pinUgradjenaLED, stanjeUgradjeneLED ? HIGH : LOW);
//         }
//     }

//     // Slanje vrijednosti na grafikon radi vizualizacije
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

//     delay(100);
// }