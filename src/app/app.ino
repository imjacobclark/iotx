#include <Arduino.h>

const uint8_t fingerprint[20] = {0x88, 0xB6, 0xC1, 0x14, 0xF7, 0x29, 0x5C, 0x63, 0x71, 0x06, 0xF4, 0xA5, 0x5A, 0xD0, 0x1F, 0x35, 0x57, 0x94, 0x9B, 0x7C};

#include "NetworkManager.h"
#include "FileManager.h"
#include "ButtonInput.h"
#include "HttpsClient.h"
#include "DHTAM2302Manager.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <NTPClient.h>
#include <WiFiUdp.h>

#include <stdio.h>
#include <string.h>

NetworkManager networkManager;
FileManager fileManager;
DHTAM2302Manager dhtAM2302Manager;
HttpsClient httpClient;

const long utcOffsetInSeconds = 0;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

unsigned long temperatureReadLastRunTime;
String temperatureData;

String room = "office";

void writeToDisplay(String str) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.clearDisplay();
  display.println(str);
  display.display(); 
}

void setup() {
    Serial.begin(9600);
    
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3D for 128x64

    fileManager.begin();

    String credentials = fileManager.read_file("/wifi_credentials.txt");

    writeToDisplay("Connecting to Wifi...");
    
    char buf[credentials.length() + 1];
    credentials.toCharArray(buf, sizeof(buf));
    char *x = buf;
    char *ssid = strtok_r(x, ",", &x);
    char *password = strtok_r(x, ",", &x);

    networkManager.connect(ssid, password);

    timeClient.begin();
    
    writeToDisplay("Connected to:\n" + String(ssid) + "\n\nBooted OK"); 
}

void loop() {
  timeClient.update();

  httpClient.GET("https://p1ndfl7h7h.execute-api.eu-west-1.amazonaws.com/Prod/nodePing?room=" + room, fingerprint);
  
  if (millis() - temperatureReadLastRunTime >= 10000) {
    writeToDisplay("Updating...");
    temperatureData = "";
    
    String temp = String(dhtAM2302Manager.get_temperature());
    String humidity = String(dhtAM2302Manager.get_humidity());
    
    httpClient.GET("https://p1ndfl7h7h.execute-api.eu-west-1.amazonaws.com/Prod?temp=" + temp + "&humidity=" + humidity + "&room=" + room, fingerprint);
    
    temperatureData = temperatureData + "Temperature: " + temp + "oC\nHumidity: " + humidity + "%\n";
  
    temperatureReadLastRunTime = millis();
  }

  writeToDisplay(temperatureData + "Uptime: " + String((millis()/1000)/60/60/24) + " Days\nDay:" + daysOfTheWeek[timeClient.getDay()] + "\nTime:" + timeClient.getHours() + ":" + timeClient.getMinutes() + ":" + timeClient.getSeconds() + "\nRoom:" + room);
}
