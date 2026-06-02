// #include <Arduino.h>
// #include "WiFi.h"
// #include "WebServer.h"
// #include <WiFiAP.h>

// const char *ssid = "nadin";
// const char *password = "12345678";

// WebServer server(80);

// uint8_t LED1pin = 2;
// bool LED1status = LOW;

// String HTML0 = "<!DOCTYPE html>\n\
// <html>\n\
//     <head>\n\
//         <meta charset='UTF-8'>\n\
//     </head>\n\
//     <body>\n\
//         <h2>Prejet ukaz za izklop LED diode.</h2>\n\
//     </body>\n\
// </html>";

// String HTML1 =
//     "<!DOCTYPE html>\n\
// <html>\n\
//     <head>\n\
//         <meta charset='UTF-8'>\n\
//     </head>\n\
//     <body>\n\
//         <h2>Prejet ukaz za vklop LED diode.</h2>\n\
//     </body>\n\
// </html>";

// String HTML3 =
//     "<!DOCTYPE html>\n\
// <html>\n\
//     <head>\n\
//         <meta charset='UTF-8'>\n\
//     </head>\n\
//     <body>\n\
//         <h2>HTTP strežnik je zagnan. V brskalnik vpišete http:</h2>\n\
//     </body>\n\
// </html>";

// void handle_root()
// {
//     server.send(200, "text/html", HTML3);
// }

// void handle_led1on()
// {
//     LED1status = HIGH;
//     Serial.println("GPIO2 Statuts: ON");
//     server.send(200, "text/html", HTML1);
// }

// void handle_led1off()
// {
//     LED1status = LOW;
//     Serial.println("GPIO2 Statuts: OFF");
//     server.send(200, "text/html", HTML0);
// }

// void handle_NotFound()
// {
//     server.send(200, "text/html", "Spletna stran ni bila najdena.");
// }

// void setup()
// {
//     pinMode(LED1pin, OUTPUT);
//     delay(100);

//     Serial.begin(115200);

//     WiFi.softAP(ssid, password);
//     delay(100);

//     Serial.println("Vspostavitev programske dostopne tocke na ESP32");
//     Serial.print("IP naslov esp32 dostopne tocke je: ");
//     Serial.println(WiFi.softAPIP());

//     server.on("/", handle_root);
//     server.on("/0", handle_led1off);
//     server.on("/1", handle_led1on);
//     server.onNotFound(handle_NotFound);
//     server.begin();
//     Serial.print("HTTP strežnik je zagnan, vpišite IP naslov v brskalnik");
//     delay(500);

//     pinMode(2, OUTPUT);
//     digitalWrite(2, HIGH);
//     delay(750);
//     digitalWrite(2, LOW);
//     delay(750);
//     digitalWrite(2, HIGH);
//     delay(750);
//     digitalWrite(2, LOW);
// }

// void loop()
// {
//     server.handleClient();

//     if (LED1status)
//     {
//         digitalWrite(LED1pin, HIGH);
//     }
//     else
//     {
//         digitalWrite(LED1pin, LOW);
//     }

//     delay(4);
// }