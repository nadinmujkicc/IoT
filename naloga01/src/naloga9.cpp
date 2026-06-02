// #include <Arduino.h>
// #include <WiFi.h>
// #include <WebSocketsClient.h>
// #include <ArduinoJson.h>

// const char *ssid = "nadin";
// const char *password = "12345678";

// int portNumber = 8811;
// WebSocketsClient webSocket;

// String dataString;
// const int nozicaPotenciometra = 34;
// int vrednostPotenciometra = 0;
// int prethodnaVrednost = 0;

// void onWebSocketEvent(WStype_t type, uint8_t *payload, size_t length)
// {
//     switch (type)
//     {
//     case WStype_TEXT:
//         JsonDocument doc;
//         DeserializationError error = deserializeJson(doc, payload);

//         if (error)
//         {
//             Serial.print(F("deserializeJson() failed: "));
//             Serial.println(error.c_str());
//             return;
//         }

//         const char *tip = doc["tipSporocila"];

//         if (strcmp(tip, "LED") == 0)
//         {
//             int pin = doc["pin"];
//             int vrednost = doc["vrednost"];

//             if (pin == 2)
//             {
//                 digitalWrite(2, vrednost == 1 ? HIGH : LOW);
//                 Serial.print("LED na pin 2 ");
//                 Serial.println(vrednost == 1 ? "UKLJUCEN" : "ISKLJUCEN");
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

//     vrednostPotenciometra = analogRead(nozicaPotenciometra);

//     if (abs(vrednostPotenciometra - prethodnaVrednost) > 10)
//     {
//         Serial.println(vrednostPotenciometra);
//         dataString = R"({"tipSporocila":"potenciometar","pin":34,"vrednost":)";
//         dataString = dataString + String(vrednostPotenciometra) + "}";
//         webSocket.sendTXT(dataString);
//         prethodnaVrednost = vrednostPotenciometra;
//     }

//     delay(50);
// }