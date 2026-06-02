// #include <Arduino.h>
// #include <WiFi.h>
// #include <WebSocketsClient.h>
// #include <ArduinoJson.h>

// const char *ssid = "nadin";
// const char *password = "12345678";

// int portNumber = 8080;
// WebSocketsClient webSocket;

// int trenutnoStanje;
// String dataString;
// const int BUTTON_PIN = 18;

// void onWebSocketEvent(WStype_t type, uint8_t *payload, size_t length)
// {
//     switch (type)
//     {
//     case WStype_TEXT:
//         StaticJsonDocument<256> doc;
//         DeserializationError error = deserializeJson(doc, payload);

//         if (error)
//         {
//             Serial.print(F("deserializeJson() failed: "));
//             Serial.println(error.c_str());
//             return;
//         }

//         char tip[40];
//         memset(tip, 0, sizeof(tip));
//         strcpy(tip, doc["tipSporocila"]);

//         if (strcmp(tip, "LED") == 0)
//         {
//             int pin = doc["pin"];
//             int vrednost = doc["vrednost"];

//             if (pin == 2)
//             {
//                 digitalWrite(2, vrednost == 1 ? HIGH : LOW);
//             }
//             else
//             {
//                 Serial.println("Neprepoznata vrednost u JSON sporocilu!");
//             }
//             break;
//         }
//     }
// }

// void setup()
// {
//     Serial.begin(115200);

//     Serial.println("Povezovanje na WiFi omrezje...");
//     WiFi.begin(ssid, password);
//     while (WiFi.status() != WL_CONNECTED)
//     {
//         delay(500);
//         Serial.print(".");
//     }
//     Serial.println();
//     Serial.println("Povezano na WiFi omrezje!");
//     Serial.print("IP naslov naprave: ");
//     Serial.println(WiFi.localIP());
//     Serial.println("Stevilka porta: " + String(portNumber));
//     Serial.println("WiFi.macAddress: " + WiFi.macAddress());

//     pinMode(2, OUTPUT);

//     digitalWrite(2, 1);
//     delay(500);
//     digitalWrite(2, 0);
//     delay(500);
//     digitalWrite(2, 1);
//     delay(500);
//     digitalWrite(2, 0);

//     webSocket.begin("10.252.254.48", 8811);
//     delay(1000);
//     webSocket.onEvent(onWebSocketEvent);
// }

// void loop()
// {
//     webSocket.loop();

//     trenutnoStanje = digitalRead(BUTTON_PIN);
//     Serial.println(trenutnoStanje);

//     if (trenutnoStanje == HIGH)
//     {
//         dataString = R"({"tipSporocila":"tipka","pin":18,"vrednost":"1"})";
//         webSocket.sendTXT(dataString);
//     }
//     else
//     {
//         dataString = R"({"tipSporocila":"tipka","pin":18,"vrednost":"0"})";
//         webSocket.sendTXT(dataString);
//     }

//     delay(4);
// }