// #include <Arduino.h>
// #include "WiFi.h"
// #include "WebServer.h"
// #include "WebSocketsClient.h"
// #include <ArduinoJson.h>

// const char *ssid = "nadin";
// const char *password = "12345678";

// int portNumber = 8811;
// const int nozicaFotoupornika = 32;

// int vrednostFotoupornika;
// int prethodnaVrednost = 0;
// String dataString;

// WebSocketsClient webSocket;

// void webSocketEvent(WStype_t type, uint8_t *payload, size_t length);

// void setup()
// {
//     Serial.begin(115200);

//     WiFi.begin(ssid, password);
//     while (WiFi.status() != WL_CONNECTED)
//     {
//         delay(500);
//         Serial.println("Povezovanje z WiFi omrežjem...");
//     }

//     Serial.println("Povezava z WiFi omrežjem je vzpostavljena");
//     Serial.print("IP naslov esp32 modula je: ");
//     Serial.println(WiFi.localIP());

//     webSocket.begin("10.252.254.48", 8811);
//     webSocket.onEvent(webSocketEvent);

//     pinMode(2, OUTPUT);
//     pinMode(4, OUTPUT);

//     digitalWrite(2, HIGH);
//     delay(300);
//     digitalWrite(2, LOW);
//     delay(300);
// }

// void webSocketEvent(WStype_t type, uint8_t *payload, size_t length)
// {
//     switch (type)
//     {
//     case WStype_TEXT:
//     {
//         StaticJsonDocument<256> doc;
//         DeserializationError error = deserializeJson(doc, payload, length);

//         if (error)
//         {
//             Serial.print(" Napaka pri deserializaciji JSON sporočila: ");
//             Serial.println(error.c_str());
//             return;
//         }

//         const char *tip = doc["tipSporočila"];

//         if (tip != nullptr && strcmp(tip, "LED") == 0)
//         {
//             int vrednost = doc["vrednost"];
//             int pin = doc["pin"];

//             if (pin == 2)
//             {
//                 if (vrednost == 0)
//                 {
//                     digitalWrite(2, LOW);
//                 }
//                 else if (vrednost == 1)
//                 {
//                     digitalWrite(2, HIGH);
//                 }
//             }
//         }

//         Serial.print("Prejeto sporočilo preko spletnega vtičnika: ");
//         Serial.println((char *)payload);
//         break;
//     }
//     default:
//         break;
//     }
// }

// void loop()
// {
//     webSocket.loop();

//     vrednostFotoupornika = analogRead(nozicaFotoupornika);
//     Serial.println(vrednostFotoupornika);

//     if (vrednostFotoupornika < 20)
//     {
//         digitalWrite(2, HIGH);
//     }
//     else
//     {
//         digitalWrite(2, LOW);
//     }

//     if (abs(vrednostFotoupornika - prethodnaVrednost) > 20)
//     {
//         dataString = R"({"tipSporočila":"fotoupornik","pin":32,"vrednost":)";
//         dataString = dataString + String(vrednostFotoupornika) + "}";

//         webSocket.sendTXT(dataString);
//         prethodnaVrednost = vrednostFotoupornika;
//     }

//     delay(100);
// }