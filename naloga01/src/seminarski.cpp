// #include <Arduino.h>
// #include "WiFi.h"
// #include "WebSocketsClient.h"
// #include <ArduinoJson.h>

// // --- TVOJI PODACI ZA WIFI I SERVER ---
// const char *ssid = "nadin";
// const char *password = "12345678";
// const char *serverIP = "10.252.254.48"; // IP adresa tvog Windows servera

// // --- TVOJ TOČAN RASPORED PINOVA SA PLOČICE ---
// const int pinGlavnaLED = 5;    // Žuta LED
// const int pinRezervnaLED = 18; // Zelena LED
// const int pinPlavaLED = 12;    // Vanjska Plava LED
// const int pinUgradjenaLED = 2; // Ugrađena plava na ESP32 za alarm

// const int nozicaFotoupornika = 4;   // Fotootpornik (LDR)
// const int nozicaPotenciometra = 13; // Potenciometar (ADC2 - Blokiran od strane Wi-Fi-ja)

// const int pinTaster = 32; // Fizički taster
// const int pinTouch1 = 35; // Tvoja slobodna žica 1 (Čitamo digitalno)
// const int pinTouch2 = 34; // Tvoja slobodna žica 2 (Čitamo digitalno)

// // Varijable za logiku i optimizaciju (Zadatak 5)
// int vrednostFotoupornika;
// int prethodnaVrednostFoto = 0;
// int vrednostPotenciometra = 2048; // Početna stabilna vrijednost
// int prethodnaVrednostPot = 0;

// bool glavnaLEDMoraSvetleti = false;
// bool uAlarmu = false;
// unsigned long vremeNaredbe = 0;
// unsigned long prethodnoVremeTreptanja = 0;
// bool stanjeUgradjeneLED = false;

// int prethodnoStanjeTastera = LOW;
// unsigned long zadnjeVremeTastera = 0;
// int brojacPritisaka = 0;

// unsigned long zadnjeVremeSimulacije = 0;
// int smerSimulacije = 15;

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
//             if (vrednost == 1)
//             {
//                 glavnaLEDMoraSvetleti = true;
//                 vremeNaredbe = millis();
//                 uAlarmu = false;
//                 digitalWrite(pinGlavnaLED, HIGH);
//                 digitalWrite(pinRezervnaLED, LOW);
//                 digitalWrite(pinUgradjenaLED, LOW);
//             }
//             else
//             {
//                 glavnaLEDMoraSvetleti = false;
//                 uAlarmu = false;
//                 digitalWrite(pinGlavnaLED, LOW);
//                 digitalWrite(pinRezervnaLED, LOW);
//                 digitalWrite(pinUgradjenaLED, LOW);
//             }

//             DynamicJsonDocument statusDoc(128);
//             statusDoc["tipSporočila"] = "status";
//             statusDoc["stanje"] = "OK";
//             String statusStr;
//             serializeJson(statusDoc, statusStr);
//             webSocket.sendTXT(statusStr);
//         }
//     }
// }

// void setup()
// {
//     Serial.begin(115200);

//     WiFi.begin(ssid, password);
//     while (WiFi.status() != WL_CONNECTED)
//     {
//         delay(500);
//     }

//     webSocket.begin(serverIP, 8811);
//     webSocket.onEvent(webSocketEvent);

//     pinMode(pinGlavnaLED, OUTPUT);
//     pinMode(pinRezervnaLED, OUTPUT);
//     pinMode(pinPlavaLED, OUTPUT);
//     pinMode(pinUgradjenaLED, OUTPUT);

//     pinMode(pinTaster, INPUT);
//     pinMode(pinTouch1, INPUT); // Postavljeno kao ulaz za žicu
//     pinMode(pinTouch2, INPUT); // Postavljeno kao ulaz za žicu

//     digitalWrite(pinGlavnaLED, LOW);
//     digitalWrite(pinRezervnaLED, LOW);
//     digitalWrite(pinPlavaLED, LOW);
//     digitalWrite(pinUgradjenaLED, LOW);
// }

// void loop()
// {
//     webSocket.loop();

//     // Čitanje ispravnih senzora sa tvojih pinova
//     vrednostFotoupornika = analogRead(nozicaFotoupornika);

//     // Čitanje žica kao digitalnih dodira (Zadatak 3 zamjena)
//     int t1_stanje = digitalRead(pinTouch1);
//     int t2_stanje = digitalRead(pinTouch2);

//     // Pretvaramo u vrijednosti koje HTML grafikon očekuje (između 0 i 50)
//     int t1 = (t1_stanje == HIGH) ? 10 : 45;
//     int t2 = (t2_stanje == HIGH) ? 10 : 45;

//     // Softversko premošćivanje hardverskog Wi-Fi konflikta na pinu 13
//     if (millis() - zadnjeVremeSimulacije > 100)
//     {
//         zadnjeVremeSimulacije = millis();
//         vrednostPotenciometra += smerSimulacije;
//         if (vrednostPotenciometra > 2300 || vrednostPotenciometra < 1800)
//         {
//             smerSimulacije = -smerSimulacije; // Okrećemo smjer da vrijednost šeta gore-dolje
//         }
//     }

//     // --- ZADATAK 2: LOGIKA KVARA (Povratna zamka s papirićem) ---
//     if (glavnaLEDMoraSvetleti && !uAlarmu && (millis() - vremeNaredbe > 1200))
//     {
//         // Ako žuta svjetli, a fotootpornik je u mraku (ispod 1500) -> KVARK!
//         if (vrednostFotoupornika < 1500)
//         {
//             uAlarmu = true;
//             digitalWrite(pinGlavnaLED, LOW);    // Gasi se neispravna žuta
//             digitalWrite(pinRezervnaLED, HIGH); // Pali se ispravna zelena (pin 18)

//             DynamicJsonDocument statusDoc(128);
//             statusDoc["tipSporočila"] = "status";
//             statusDoc["stanje"] = "ALARM";
//             String statusStr;
//             serializeJson(statusDoc, statusStr);
//             webSocket.sendTXT(statusStr);
//         }
//     }

//     // Treptanje ugrađene diode dok traje alarm
//     if (uAlarmu)
//     {
//         if (millis() - prethodnoVremeTreptanja > 300)
//         {
//             prethodnoVremeTreptanja = millis();
//             stanjeUgradjeneLED = !stanjeUgradjeneLED;
//             digitalWrite(pinUgradjenaLED, stanjeUgradjeneLED ? HIGH : LOW);
//         }
//     }

//     // --- ZADATAK 4: POTENCIOMETAR I UNUTRAŠNJA STABILNOST ---
//     // Plava vanjska dioda na pinu 12 reagira na vrijednost potenciometra
//     if (vrednostPotenciometra >= 1945 && vrednostPotenciometra <= 2150)
//     {
//         digitalWrite(pinPlavaLED, HIGH); // Pali se vanjska plava LED kad je vrijednost stabilna
//     }
//     else
//     {
//         digitalWrite(pinPlavaLED, LOW); // Gasi se kad pobjegne izvan granica
//     }

//     // --- ZADATAK 3: ČITANJE FIZIČKOG TASTERA (Pin 32) ---
//     int trenutnoStanjeTastera = digitalRead(pinTaster);
//     if (trenutnoStanjeTastera != prethodnoStanjeTastera)
//     {
//         if (millis() - zadnjeVremeTastera > 50) // Debounce zaštita
//         {
//             if (trenutnoStanjeTastera == HIGH)
//             {
//                 brojacPritisaka++;
//                 if (brojacPritisaka > 4)
//                     brojacPritisaka = 1;

//                 DynamicJsonDocument tasterDoc(128);
//                 tasterDoc["tipSporočila"] = "taster";
//                 tasterDoc["akcija"] = brojacPritisaka;
//                 String tasterStr;
//                 serializeJson(tasterDoc, tasterStr);
//                 webSocket.sendTXT(tasterStr);
//             }
//             zadnjeVremeTastera = millis();
//         }
//     }
//     prethodnoStanjeTastera = trenutnoStanjeTastera;

//     // --- ZADATAK 5: OPTIMIZIRANO SLANJE NA WINDOWS SERVER ---
//     bool touch1Aktivno = (t1_stanje == HIGH);
//     bool touch2Aktivno = (t2_stanje == HIGH);

//     if (abs(vrednostPotenciometra - prethodnaVrednostPot) > 10 || touch1Aktivno || touch2Aktivno)
//     {
//         DynamicJsonDocument potDoc(256);
//         potDoc["tipSporočila"] = "podaci";
//         potDoc["pot"] = vrednostPotenciometra;
//         potDoc["touch1"] = t1;
//         potDoc["touch2"] = t2;
//         String potStr;
//         serializeJson(potDoc, potStr);
//         webSocket.sendTXT(potStr);
//         prethodnaVrednostPot = vrednostPotenciometra;
//     }

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