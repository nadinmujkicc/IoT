// #include <Arduino.h>
// #include "WiFi.h"
// #include "WebServer.h"
// #include <WiFiAP.h>

// const char *ssid = "T-2_WiFi";
// const char *password = "12345678";

// WebServer server(80);

// uint8_t LED1pin = 2;
// bool LED1status = LOW;

// String HTML0 = "<!DOCTYPE html>\
// <html>\
//     <head>\
//         <meta charset='UTF-8'>\
//         <meta name='viewport' content='width=device-width, initial-scale=1.0, user-scalable=no'>\
//         <style>\
//             html {font-family: Helvetica; text-align: center;}\
//             body {margin-top: 50px;}\
//             h1 {color: #444444; margin: 50px auto 30px; }\
//             h3 {color: #444444; margin-bottom: 50px;}\
//             .gumb{background-color:blue; display: block; width: 200px; color: white; padding: 13px 30px; text-decoration: none; font-size: 25px; margin: 0px auto 35px; cursor: pointer; border-radius: 4px; border: none;}\
//             p {font-size: 16px; color: #222222; margin-bottom: 10px;}\
//         </style>\
//     </head>\
//     <body>\
//         <h1>ESP32 spletni streznik</h1>\
//         <h3>Priklop na WiFi usmerjevalnik.</h3>\
//         <a class='gumb' href='/1'>Prizgi LED</a>\
//         <a class='gumb' href='/0'>Ugasni LED</a>\
//         <p>Prejet ukaz za vklop LED diode.</p>\
//     </body>\
// </html>";

// String HTML1 = "<!DOCTYPE html>\
// <html>\
//     <head>\
//         <meta charset='UTF-8'>\
//         <meta name='viewport' content='width=device-width, initial-scale=1.0, user-scalable=no'>\
//         <style>\
//             html {font-family: Helvetica; text-align: center;}\
//             body {margin-top: 50px;}\
//             h1 {color: #444444; margin: 50px auto 30px; }\
//             h3 {color: #444444; margin-bottom: 50px;}\
//             .gumb{background-color:blue; display: block; width: 200px; color: white; padding: 13px 30px; text-decoration: none; font-size: 25px; margin: 0px auto 35px; cursor: pointer; border-radius: 4px; border: none;}\
//             p {font-size: 16px; color: #222222; margin-bottom: 10px;}\
//         </style>\
//     </head>\
//     <body>\
//         <h1>ESP32 spletni streznik</h1>\
//         <h3>Priklop na WiFi usmerjevalnik.</h3>\
//         <a class='gumb' href='/1'>Prizgi LED</a>\
//         <a class='gumb' href='/0'>Ugasni LED</a>\
//         <p>Prejet ukaz za vklop LED diode.</p>\
//     </body>\
// </html>";

// String HTML3 = "<!DOCTYPE html>\
// <html>\
//     <head>\
//         <meta charset='UTF-8'>\
//         <meta name='viewport' content='width=device-width, initial-scale=1.0, user-scalable=no'>\
//         <style>\
//             html {font-family: Helvetica; text-align: center;}\
//             body {margin-top: 50px;}\
//             h1 {color: #444444; margin: 50px auto 30px; }\
//             h3 {color: #444444; margin-bottom: 50px;}\
//             .gumb{background-color:blue; display: block; width: 200px; color: white; padding: 13px 30px; text-decoration: none; font-size: 25px; margin: 0px auto 35px; cursor: pointer; border-radius: 4px; border: none;}\
//             p {font-size: 16px; color: #222222; margin-bottom: 10px;}\
//         </style>\
//     </head>\
//     <body>\
//         <h1>ESP32 spletni streznik</h1>\
//         <h3>Priklop na WiFi usmerjevalnik.</h3>\
//         <a class='gumb' href='/1'>Prizgi LED</a>\
//         <a class='gumb' href='/0'>Ugasni LED</a>\
//         <p>HTTP streznik je zagnan.</p>\
//     </body>\
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