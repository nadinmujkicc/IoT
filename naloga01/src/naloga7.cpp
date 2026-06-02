// #include <Arduino.h>
// #include <ArduinoJson.h>

// const int LED_PIN = 2;

// void setup()
// {
//     Serial.begin(115200);
//     delay(1000);

//     pinMode(LED_PIN, OUTPUT);
//     digitalWrite(LED_PIN, LOW);

//     Serial.println("Ceka JSON poruke...");
//     Serial.println("Primer: {\"tipSporucila\":\"LED\",\"pin\":2,\"vrednost\":1}");
// }

// void loop()
// {
//     if (Serial.available() > 0)
//     {
//         String jsonString = Serial.readStringUntil('\n');
//         jsonString.trim();

//         Serial.print("Primljena poruka: ");
//         Serial.println(jsonString);

//         JsonDocument doc;
//         DeserializationError error = deserializeJson(doc, jsonString);

//         if (error)
//         {
//             Serial.print("Greska pri parsiranju JSON-a: ");
//             Serial.println(error.f_str());
//             return;
//         }

//         if (!doc["tipSporucila"].is<const char *>() ||
//             !doc["pin"].is<int>() ||
//             !doc["vrednost"].is<int>())
//         {
//             Serial.println("Nedostaju obavezna polja!");
//             return;
//         }

//         const char *tipSporucila = doc["tipSporucila"];
//         int pin = doc["pin"];
//         int vrednost = doc["vrednost"];

//         if (strcmp(tipSporucila, "LED") == 0)
//         {
//             digitalWrite(pin, vrednost);

//             if (vrednost == 1)
//             {
//                 Serial.print("OK - LED na pin ");
//                 Serial.print(pin);
//                 Serial.println(" je UKLJUCEN");
//             }
//             else
//             {
//                 Serial.print("OK - LED na pin ");
//                 Serial.print(pin);
//                 Serial.println(" je ISKLJUCEN");
//             }
//         }
//         else
//         {
//             Serial.println("Nepoznat tip poruke!");
//         }
//     }

//     delay(10);
// }