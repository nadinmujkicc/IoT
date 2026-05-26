// #include <Arduino.h>
// #include <WiFi.h>
// #include <WebServer.h>

// const char *ssid = "nadin";
// const char *password = "12345678";

// WebServer server(80);

// void handle_root()
// {
//     server.send(200, "text/html", "Pozdravljen svet iz esp32!");
// }

// void handle_abeceda()
// {
//     server.send(200, "text/html; charset=UTF-8", "abcčdefghijklmnoprsštuvzž");
// }

// void handle_cifre()
// {
//     server.send(200, "text/html", "0123456789");
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
//     server.on("/abeceda", handle_abeceda);
//     server.on("/cifre", handle_cifre);
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