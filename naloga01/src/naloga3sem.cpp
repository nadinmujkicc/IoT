// #include <Arduino.h>
// #include "WiFi.h"
// #include "WebSocketsClient.h"
// #include <ArduinoJson.h>

// const char *ssid = "nadin";
// const char *password = "12345678";
// const char *serverIP = "10.252.254.201";

// const int pinLED1 = 5;
// const int pinLED2 = 14;
// const int pinLED3 = 2;

// const int tPin1 = 32;
// const int tPin2 = 15;
// const int tPin3 = 13;

// const int pinTaster = 12;

// int tVal1, tVal2, tVal3;
// int pVal1 = 0, pVal2 = 0, pVal3 = 0;

// bool stanjeLED1 = false;
// bool stanjeLED2 = false;
// bool stanjeLED3 = false;

// int korakGrafona = 0;
// bool prethodnoStanjeTastera = HIGH;

// unsigned long prethodnoVreme = 0;

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
//         if (tip != nullptr && strcmp(tip, "KONTROLA_LED") == 0)
//         {
//             int indeks = doc["indeks"];
//             int stanje = doc["stanje"];

//             if (indeks == 1)
//             {
//                 stanjeLED1 = stanje;
//                 digitalWrite(pinLED1, stanjeLED1 ? HIGH : LOW);
//             }
//             else if (indeks == 2)
//             {
//                 stanjeLED2 = stanje;
//                 digitalWrite(pinLED2, stanjeLED2 ? HIGH : LOW);
//             }
//             else if (indeks == 3)
//             {
//                 stanjeLED3 = stanje;
//                 digitalWrite(pinLED3, stanjeLED3 ? HIGH : LOW);
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

//     pinMode(pinLED1, OUTPUT);
//     pinMode(pinLED2, OUTPUT);
//     pinMode(pinLED3, OUTPUT);

//     digitalWrite(pinLED1, LOW);
//     digitalWrite(pinLED2, LOW);
//     digitalWrite(pinLED3, LOW);

//     pinMode(pinTaster, INPUT_PULLUP);
// }

// void loop()
// {
//     webSocket.loop();

//     bool trenutnoStanjeTastera = digitalRead(pinTaster);
//     if (trenutnoStanjeTastera == LOW && prethodnoStanjeTastera == HIGH)
//     {
//         delay(50);
//         korakGrafona++;
//         if (korakGrafona > 4)
//             korakGrafona = 1;

//         DynamicJsonDocument tasterDoc(128);
//         tasterDoc["tipSporočila"] = "korak_grafika";
//         tasterDoc["korak"] = korakGrafona;
//         String tasterStr;
//         serializeJson(tasterDoc, tasterStr);
//         webSocket.sendTXT(tasterStr);
//     }
//     prethodnoStanjeTastera = trenutnoStanjeTastera;

//     tVal1 = touchRead(tPin1);
//     tVal2 = touchRead(tPin2);
//     tVal3 = touchRead(tPin3);

//     if (tVal1 < 30 && pVal1 >= 30)
//     {
//         stanjeLED1 = !stanjeLED1;
//         digitalWrite(pinLED1, stanjeLED1 ? HIGH : LOW);
//     }
//     if (tVal2 < 30 && pVal2 >= 30)
//     {
//         stanjeLED2 = !stanjeLED2;
//         digitalWrite(pinLED2, stanjeLED2 ? HIGH : LOW);
//     }
//     if (tVal3 < 30 && pVal3 >= 30)
//     {
//         stanjeLED3 = !stanjeLED3;
//         digitalWrite(pinLED3, stanjeLED3 ? HIGH : LOW);
//     }

//     pVal1 = tVal1;
//     pVal2 = tVal2;
//     pVal3 = tVal3;

//     if (millis() - prethodnoVreme > 50)
//     {
//         prethodnoVreme = millis();

//         DynamicJsonDocument doc(256);
//         doc["tipSporočila"] = "touch";
//         doc["t1"] = tVal1;
//         doc["t2"] = tVal2;
//         doc["t3"] = tVal3;
//         doc["led1"] = stanjeLED1 ? 1 : 0;
//         doc["led2"] = stanjeLED2 ? 1 : 0;
//         doc["led3"] = stanjeLED3 ? 1 : 0;

//         String izlaz;
//         serializeJson(doc, izlaz);
//         webSocket.sendTXT(izlaz);
//     }

//     delay(10);
// }