// #include <Arduino.h>
// #include <WiFi.h>
// #include <WebServer.h>
// #include <WebSocketsServer.h>

// const char *ssid = "nadin";
// const char *password = "12345678";

// WebServer server(80);
// WebSocketsServer webSocket = WebSocketsServer(81);

// const char HTML[] PROGMEM = R"rawliteral(
// <!DOCTYPE html>
// <html lang="sl">
// <head>
//     <meta charset="UTF-8">
//     <meta name="viewport" content="width=device-width, initial-scale=1.0">
//     <title>WebSocket</title>
// </head>
// <body>
// <h2>Primer s spletnim vtičnikom WebSocket</h2>
// <input type="text" id="sporočilo" placeholder="Vnesite sporočilo">
// <button onclick="pošljiSporočilo()">pošljiSporočilo</button>
// <script>
// let povezava = new WebSocket("ws://10.252.254.63:81/");
// function pošljiSporočilo(){
//     let sporočilo = document.getElementById("sporočilo").value;
//     povezava.send(sporočilo);
// }
// </script>
// </body>
// </html>
// )rawliteral";

// void handle_root()
// {
//     server.send(200, "text/html", HTML);
// }

// void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
// {
//     switch (type)
//     {
//     case WStype_DISCONNECTED:
//     {
//         Serial.printf("[%u] Klient odklopljen!\n", num);
//     }
//     break;

//     case WStype_CONNECTED:
//     {
//         IPAddress ip = webSocket.remoteIP(num);
//         Serial.printf("[%u] Vzpostavljena WebSocket povezava iz IP naslova!\n", num);
//         Serial.println(ip.toString());
//     }
//     break;

//     case WStype_TEXT:
//     {
//         Serial.printf("[%u] Besedilo sporočila: %s\n", num, payload);
//     }
//     break;

//     default:
//         break;
//     }
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

//     webSocket.begin();
//     webSocket.onEvent(onWebSocketEvent);

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
//     webSocket.loop();
// }