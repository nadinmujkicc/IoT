// #include <Arduino.h>
// #include <WiFi.h>

// const char *ssid = "nadin";
// const char *password = "12345678";

// void setup()
// {

//   Serial.begin(115200);

//   WiFi.begin(ssid, password);

//   while (WiFi.status() != WL_CONNECTED)
//   {
//     delay(500);
//     Serial.println("Povezovanje na WiFi omrežje v teku...");
//   }

//   Serial.println("Povezava z WiFi omrežjem je vzpostavljena.");
//   Serial.print("IP naslov modula = ");
//   Serial.println(WiFi.localIP());

//   pinMode(2, OUTPUT);
//   digitalWrite(2, HIGH);
//   delay(750);
//   digitalWrite(2, LOW);
//   delay(750);
//   digitalWrite(2, HIGH);
//   delay(750);
//   digitalWrite(2, LOW);
//   delay(750);
// }

// void loop()
// {
// }