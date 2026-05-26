// #include <Arduino.h>
// #include <WiFi.h>
// #include <WebServer.h>

// const char *ssid = "nadin";
// const char *password = "12345678";

// const uint8_t PIN_CRVENA = 5;
// const uint8_t PIN_ZELENA = 19;
// const uint8_t PIN_ONBOARD = 2;

// bool statusCrvena = LOW;
// bool statusZelena = LOW;
// bool statusOnboard = LOW;

// WebServer server(80);

// const char HTML_CRVENA_ON[] PROGMEM = R"rawliteral(
// <!DOCTYPE html>
// <html lang="sl"><head><meta charset="UTF-8"><title>esp32</title></head>
// <body><h1>Crvena LED (Pin 5) je UPALJENA</h1></body></html>
// )rawliteral";

// const char HTML_CRVENA_OFF[] PROGMEM = R"rawliteral(
// <!DOCTYPE html>
// <html lang="sl"><head><meta charset="UTF-8"><title>esp32</title></head>
// <body><h1>Crvena LED (Pin 5) je UGASENA</h1></body></html>
// )rawliteral";

// const char HTML_ZELENA_ON[] PROGMEM = R"rawliteral(
// <!DOCTYPE html>
// <html lang="sl"><head><meta charset="UTF-8"><title>esp32</title></head>
// <body><h1>Zelena LED (Pin 19) je UPALJENA</h1></body></html>
// )rawliteral";

// const char HTML_ZELENA_OFF[] PROGMEM = R"rawliteral(
// <!DOCTYPE html>
// <html lang="sl"><head><meta charset="UTF-8"><title>esp32</title></head>
// <body><h1>Zelena LED (Pin 19) je UGASENA</h1></body></html>
// )rawliteral";

// const char HTML_ONBOARD_ON[] PROGMEM = R"rawliteral(
// <!DOCTYPE html>
// <html lang="sl"><head><meta charset="UTF-8"><title>esp32</title></head>
// <body><h1>Onboard LED (l1) je UPALJENA</h1></body></html>
// )rawliteral";

// const char HTML_ONBOARD_OFF[] PROGMEM = R"rawliteral(
// <!DOCTYPE html>
// <html lang="sl"><head><meta charset="UTF-8"><title>esp32</title></head>
// <body><h1>Onboard LED (l0) je UGASENA</h1></body></html>
// )rawliteral";

// const char HTMLroot[] PROGMEM = R"rawliteral(
// <!DOCTYPE html>
// <html lang="sl"><head><meta charset="UTF-8"><title>esp32</title></head>
// <body><h1>HTTP Server aktivan. Koristite rute /3, /2, /5, /4, /l1, /l0</h1></body></html>
// )rawliteral";

// void handle_root()
// {
//     server.send(200, "text/html", HTMLroot);
// }

// void handle_crvena_on()
// {
//     statusCrvena = HIGH;
//     server.send(200, "text/html", HTML_CRVENA_ON);
// }

// void handle_crvena_off()
// {
//     statusCrvena = LOW;
//     server.send(200, "text/html", HTML_CRVENA_OFF);
// }

// void handle_zelena_on()
// {
//     statusZelena = HIGH;
//     server.send(200, "text/html", HTML_ZELENA_ON);
// }

// void handle_zelena_off()
// {
//     statusZelena = LOW;
//     server.send(200, "text/html", HTML_ZELENA_OFF);
// }

// void handle_onboard_on()
// {
//     statusOnboard = HIGH;
//     server.send(200, "text/html", HTML_ONBOARD_ON);
// }

// void handle_onboard_off()
// {
//     statusOnboard = LOW;
//     server.send(200, "text/html", HTML_ONBOARD_OFF);
// }

// void handle_NotFound()
// {
//     server.send(404, "text/plain", "Stranica ne postoji.");
// }

// void setup()
// {
//     Serial.begin(115200);
//     WiFi.begin(ssid, password);

//     while (WiFi.status() != WL_CONNECTED)
//     {
//         delay(500);
//         Serial.println("Povezovanje...");
//     }

//     Serial.print("IP naslov modula = ");
//     Serial.println(WiFi.localIP());

//     server.on("/", handle_root);
//     server.on("/3", handle_crvena_on);
//     server.on("/2", handle_crvena_off);
//     server.on("/5", handle_zelena_on);
//     server.on("/4", handle_zelena_off);
//     server.on("/l1", handle_onboard_on);
//     server.on("/l0", handle_onboard_off);
//     server.onNotFound(handle_NotFound);

//     server.begin();
//     Serial.println("HTTP strežnik je zagnan, vpišite: http://10.252.254.63/");

//     pinMode(PIN_CRVENA, OUTPUT);
//     pinMode(PIN_ZELENA, OUTPUT);
//     pinMode(PIN_ONBOARD, OUTPUT);

//     digitalWrite(PIN_ONBOARD, HIGH);
//     delay(750);
//     digitalWrite(PIN_ONBOARD, LOW);
//     delay(750);
//     digitalWrite(PIN_ONBOARD, HIGH);
//     delay(750);
//     digitalWrite(PIN_ONBOARD, LOW);
//     delay(750);
// }

// void loop()
// {
//     server.handleClient();

//     digitalWrite(PIN_CRVENA, statusCrvena);
//     digitalWrite(PIN_ZELENA, statusZelena);
//     digitalWrite(PIN_ONBOARD, statusOnboard);
// }