// #include <Arduino.h>
// #include <WiFi.h>
// #include <WebServer.h>

// const char *ssid = "nadin";
// const char *password = "12345678";

// WebServer server(80);

// const char HTML[] PROGMEM = R"rawliteral(
// <!DOCTYPE html>
// <html lang="sl">
// <head>
//     <meta charset="UTF-8">
//     <meta name="viewport" content="width=device-width, initial-scale=1.0">
//     <title>esp32</title>
// </head>
// <body>
//     <h1>Pozdravljen svet iz modula esp32! Tokrat modul vrne spletno stran.</h1>
// </body>
// </html>
// )rawliteral";

// void handle_root()
// {
//     server.send(200, "text/html", HTML);
// }

// void setup()
// {
//     Serial.begin(115200);

//     WiFi.begin(ssid, password);

//     while (WiFi.status() != WL_CONNECTED)
//     {
//         delay(500);
//         Serial.println("Povezovanje na WiFi omrežje v teku...");
//     }

//     Serial.println("Povezava z WiFi omrežjem je vzpostavljena.");
//     Serial.print("IP naslov modula = ");
//     Serial.println(WiFi.localIP());

//     server.on("/", handle_root);
//     server.begin();

//     Serial.println("HTTP strežnik je zagnan, vpišite IP naslov v brskalnik, npr. http://10.252.254.63/ http in ne https.");

//     pinMode(2, OUTPUT);
//     digitalWrite(2, HIGH);
//     delay(750);
//     digitalWrite(2, LOW);
//     delay(750);
//     digitalWrite(2, HIGH);
//     delay(750);
//     digitalWrite(2, LOW);
//     delay(750);
// }

// void loop()
// {
//     server.handleClient();
// }