// #include <Arduino.h>
// #include "WiFi.h"
// #include "WebServer.h"
// #include <WiFiAP.h>

// const char *ssid = "nadin";
// const char *password = "12345678";

// WebServer server(80);

// String HTML = "<!DOCTYPE html>\n\
// <html>\n\
//     <head>\n\
//         <meta charset='UTF-8'>\n\
//     </head>\n\
//     <body>\n\
//         <h1>Pozdravljen svet na kriziscu tehnologij</h1>\n\
//     </body>\n\
// </html>";

// void handle_root()
// {
//     server.send(200, "text/html", HTML);
// }

// void setup()
// {
//     Serial.begin(115200);

//     WiFi.softAP(ssid, password);
//     delay(100);

//     Serial.println("Vspostavitev programske dostopne tocke na ESP32");
//     Serial.print("IP naslov esp32 dostopne tocke je: ");
//     Serial.println(WiFi.softAPIP());

//     server.on("/", handle_root);
//     server.begin();
//     Serial.print("HTTP streznik je zagnan, vpisite IP naslov v brskalnik ");
//     Serial.println(WiFi.softAPIP());
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
//     delay(4);
// }