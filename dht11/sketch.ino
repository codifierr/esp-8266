// Sketch to read humidity and temperature from a DHT11 sensor
//  Language: cpp
//  Path: dht11/sketch.ino
//  Same sketch will work for dht22 which is better and upgraded sensor for humidity and temperature.
//  Author : Satyendra Singh

#include <DHT.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define DHTPIN D5
#define DHTTYPE DHT11 // DHT 11 change to 22 for DHT 22
DHT dht(DHTPIN, DHTTYPE);

const char *ssid = "ssid";                  // WiFI Name
const char *password = "password";          // WiFi Password
const char *mqttServer = "server-ip";       // MQTT Server Address
const char *clientID = "clientid"; // client id
const char *topicR = "topic/r";         // topic for receiving commands
const char *topicP = "topic/p";         // topic for sending data

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
    Serial.begin(115200);
    pinMode(DHTPIN, INPUT_PULLUP); // set DHTPIN as an input with pullup enabled
    delay(500);
    Serial.println(F("DHT11 temperature and humidity!"));
    dht.begin();

    setup_wifi();
    client.setServer(mqttServer, 30426);
    client.setCallback(callback);
}

void loop()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        // reconnect wifi
        reconnectWifi();
    }
    else
    {
        // mqtt conditional reconnection
        if (!client.connected())
        {
            reconnectMqtt();
        }
        client.loop();
    }

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

    String temp = "{\"Humidity\":" + String(h) + ",\"HumidityUnit\":\"Percentage\",\"Temperature\":" + String(t) + ",\"TemperatureUnit\":\"Celsius\"}";
    Serial.println(temp);
    char tab2[1024];
    strncpy(tab2, temp.c_str(), sizeof(tab2));
    tab2[sizeof(tab2) - 1] = 0;
    client.publish(topicP, tab2);

    delay(3000);
}

void setup_wifi()
{
    delay(10);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void reconnectWifi()
{
    Serial.println("WiFi disconnected. reconnecting...");
    delay(10);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void reconnect()
{
    while (!client.connected())
    {
        if (client.connect(clientID))
        {
            Serial.println("MQTT connected");
            // ... and resubscribe
            client.subscribe(topicR);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void reconnectMqtt()
{
    while (!client.connected())
    {
        if (client.connect(clientID))
        {
            Serial.println("MQTT connected");
            // ... and resubscribe
            client.subscribe(topicR);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    String message;
    for (int i = 0; i < length; i++)
    {
        message = message + (char)payload[i];
    }
    Serial.println(message);
}