#include <Arduino.h>
#include "WiFi.h"
#include "WebSocketsClient.h"
#include <ArduinoJson.h>

const char *ssid = "nadin";
const char *password = "12345678";
const char *serverIP = "10.252.254.201";

const int pinPotenciometar = 34;
const int pinLedPWM = 2;

float Kp = 0.5;
float Ki = 0.05;

int zeljenaVrednost = 2048;
float integralVrednost = 0;

unsigned long prethodnoVreme = 0;
WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length)
{
    if (type == WStype_TEXT)
    {
        StaticJsonDocument<256> doc;
        DeserializationError error = deserializeJson(doc, payload, length);
        if (error)
            return;

        const char *tip = doc["tipSporočila"];
        if (tip != nullptr && strcmp(tip, "POSTAVI_ZELENO") == 0)
        {
            zeljenaVrednost = doc["vrednost"];
        }
    }
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
    }

    webSocket.begin(serverIP, 8811);
    webSocket.onEvent(webSocketEvent);

    pinMode(pinPotenciometar, INPUT);

    ledcSetup(0, 5000, 8);
    ledcAttachPin(pinLedPWM, 0);
}

void loop()
{
    webSocket.loop();

    digitalWrite(14, LOW);
    digitalWrite(5, LOW);

    int stvarnaVrednost = analogRead(pinPotenciometar);

    int greska = zeljenaVrednost - stvarnaVrednost;
    integralVrednost += greska * 0.05;

    if (integralVrednost > 255)
        integralVrednost = 255;
    if (integralVrednost < 0)
        integralVrednost = 0;

    float izlazPI = (Kp * greska) + (Ki * integralVrednost);

    int pwmVrednost = constrain((int)izlazPI, 0, 255);

    ledcWrite(0, pwmVrednost);

    if (millis() - prethodnoVreme > 50)
    {
        prethodnoVreme = millis();

        DynamicJsonDocument doc(256);
        doc["tipSporočila"] = "pi_podatki";
        doc["stvarna"] = stvarnaVrednost;
        doc["zeljena"] = zeljenaVrednost;
        doc["pwm"] = pwmVrednost;

        String izlaz;
        serializeJson(doc, izlaz);
        webSocket.sendTXT(izlaz);
    }

    delay(10);
}