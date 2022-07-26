#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
    Serial.begin(115200);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }

    // Clear the buffer
    display.clearDisplay();
    display.display();

    testDrawInfo();         // Draw 'stylized' characters

    display.clearDisplay(); // Clear the buffer
}

void loop()
{
    // Do nothing
}

void testDrawInfo(void)
{
    display.clearDisplay();
    displayWaterLevel(100);
    delay(2000);

    // setting size to 1
    display.setTextSize(1);

    displayWifiStatus(0);
    delayMicroseconds(50);

    displayPumpStatus(1);
    delayMicroseconds(2000);

    displayWaterLevel(50);
    delayMicroseconds(2000);

    displayWifiStatus(2);
    delayMicroseconds(2000);

    displayMqttStatus(0);
    delayMicroseconds(2000);

    displayPumpStatus(2);
    delayMicroseconds(2000);

    displayWaterLevel(10);
    delayMicroseconds(2000);

    displayMqttStatus(1);
    delayMicroseconds(2000);

    displayPumpStatus(0);
    delayMicroseconds(2000);

    displayWaterLevel(56);
    delayMicroseconds(2000);

    displayWifiStatus(1);
    delayMicroseconds(2000);

    displayMqttStatus(2);
    delayMicroseconds(2000);

    displayWaterLevel(80);
    delayMicroseconds(1000);
}

void fillRectangle(int x, int y, int width, int height, int color)
{
    display.fillRect(x, y, width, height, color);
}

void displayWaterLevel(int level)
{
    int x = 0;
    int y = 0;
    int width = 128;
    int height = 15;
    fillRectangle(x, y, width, height, SSD1306_BLACK);
    display.setCursor(1, 0);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.println("Level " + String(level) + "%");
    display.display();
}

void displayWifiStatus(int status)
{
    int x = 0;
    int y = 16;
    int width = 64;
    int height = 8;
    display.setTextSize(1);
    fillRectangle(x, y, width, height, SSD1306_BLACK);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    if (status == 1)
    {
        display.println("Wifi On");
        
    }
    else if (status == 0)
    {
        
        display.println("Wifi Off");
    } else {

        display.println("Wifi Error");
    }
    display.display();
}

void displayMqttStatus(int status)
{
    int x = 64;
    int y = 16;
    int width = 64;
    int height = 8;
    display.setTextSize(1);
    fillRectangle(x, y, width, 8, SSD1306_BLACK);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    if (status == 1)
    {
        display.println("Mqtt On");
    }
    else if (status == 0)
    {
        display.println("Mqtt Off");
    }
    else
    {
        display.println("Mqtt Error");
    }
    display.display();
}

void displayPumpStatus(int status){
    int x = 0;
    int y = 24;
    int width = 80;
    int height = 8;
    display.setTextSize(1);
    fillRectangle(x, y, width, height, SSD1306_BLACK);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    if (status==1){
        
        display.println("Pump Running");
       
    }
    else if (status == 0)
    {

        display.println("Pump Stopped");

    }
    else if (status == 2)
    {

        display.println("Pump Paused");
    } else
    {

        display.println("Pump Error");
    }
    display.display();
}