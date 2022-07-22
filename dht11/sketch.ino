// Sketch to read humidity and temperature from a DHT11 sensor
//  Language: cpp
//  Path: dht11/sketch.ino
//  Same sketch will work for dht22 which is better and upgraded sensor for humidity and temperature.
//  Author : Satyendra Singh

#include <DHT.h>

#define DHTPIN D5
#define DHTTYPE DHT11 // DHT 11 change to 22 for DHT 22
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(115200);
    pinMode(DHTPIN, INPUT_PULLUP); // set DHTPIN as an input with pullup enabled
    delay(500);
    Serial.println(F("DHT11 temperature and humidity!"));
    dht.begin();
}

void loop()
{
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F(" %\t"));
    Serial.print(F("Temperature: "));
    Serial.print(t);
    Serial.print(F(" *C\t"));
    Serial.println(F(""));

    delay(3000);
}