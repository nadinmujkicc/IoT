// #include <Arduino.h>
// #include "WiFi.h"
// #include "WebSocketsClient.h"
// #include <ArduinoJson.h>

// const char *ssid = "nadin";
// const char *password = "12345678";
// const char *serverIP = "10.252.254.201";

// const int pinPotenciometar = 34;

// const int pinZuta = 14;
// const int pinZelena = 5;
// const int pinPlava = 4;

// const int zelenaVrednost = 2048;
// const int toleranca = 102;

// unsigned long prethodnoVreme = 0;
// WebSocketsClient webSocket;

// void webSocketEvent(WStype_t type, uint8_t *payload, size_t length) {}

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

//     pinMode(pinZuta, OUTPUT);
//     pinMode(pinZelena, OUTPUT);
//     pinMode(pinPlava, OUTPUT);

//     digitalWrite(pinZuta, LOW);
//     digitalWrite(pinZelena, LOW);
//     digitalWrite(pinPlava, LOW);
// }

// void loop()
// {
//     webSocket.loop();

//     int potVrednost = analogRead(pinPotenciometar);

//     if (potVrednost < (zelenaVrednost - toleranca))
//     {
//         digitalWrite(pinZuta, HIGH);
//         digitalWrite(pinZelena, LOW);
//         digitalWrite(pinPlava, LOW);
//     }
//     else if (potVrednost > (zelenaVrednost + toleranca))
//     {
//         digitalWrite(pinZuta, LOW);
//         digitalWrite(pinZelena, LOW);
//         digitalWrite(pinPlava, HIGH);
//     }
//     else
//     {
//         digitalWrite(pinZuta, LOW);
//         digitalWrite(pinZelena, HIGH);
//         digitalWrite(pinPlava, LOW);
//     }

//     if (millis() - prethodnoVreme > 50)
//     {
//         prethodnoVreme = millis();

//         DynamicJsonDocument doc(256);
//         doc["tipSporočila"] = "potenciometer";
//         doc["vsebina"] = potVrednost;

//         String izlaz;
//         serializeJson(doc, izlaz);
//         webSocket.sendTXT(izlaz);
//     }

//     delay(10);
// }