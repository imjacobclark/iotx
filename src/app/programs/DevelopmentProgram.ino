#include <Arduino.h>

#include "NetworkManager.h"
#include "FileManager.h"
#include "ButtonInput.h"
#include "HueManager.h"
#include "DHTAM2302Manager.h"

#include <stdio.h>
#include <string.h>

NetworkManager networkManager;
FileManager fileManager;
ButtonInput buttonInput;
HueManager hueManager;
DHTAM2302Manager dhtAM2302Manager;

String hueBridgeIP = "192.168.1.82";
String officeLightId = "12";
String bedroomLightId = "6";
String livingRoomLamp1Id = "2";
String bridgeAPIKey = "";

int button0ToggleState = 0;

unsigned long buttonsLastRunTime;
unsigned long officeLightUptimeLastRunTime;
unsigned long temperatureReadLastRunTime;

void handleButtonEvent() {
    if (millis() - buttonsLastRunTime >= 100) {
        wifi_set_sleep_type(NONE_SLEEP_T);

        if(buttonInput.read(D0) == 1){
            if(button0ToggleState == 0) {
                hueManager.light_on(bridgeAPIKey, hueBridgeIP, officeLightId);
                button0ToggleState = 1;
            }else if(button0ToggleState == 1) {
                hueManager.light_off(bridgeAPIKey, hueBridgeIP, officeLightId);
                button0ToggleState = 0;
            }
        }

        buttonsLastRunTime = millis();
        wifi_set_sleep_type(LIGHT_SLEEP_T);
    }
}

void readTemp() {
  Serial.print("Humidity: ");
  Serial.println(dhtAM2302Manager.get_humidity());
  Serial.print("Temperature: ");
  Serial.println(dhtAM2302Manager.get_temperature());
  Serial.println("");
}

void setup() {
    Serial.begin(9600);

    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D5, INPUT_PULLUP);

    Serial.println("");

    Serial.println("Welcome to iotx... booting...");

    digitalWrite(D1, HIGH);

    buttonInput.setup(D0);

    fileManager.begin();

    digitalWrite(D2, HIGH);

    String credentials = fileManager.read_file("/wifi_credentials.txt");
    bridgeAPIKey = fileManager.read_file("/hue_credentials.txt");

    char buf[credentials.length() + 1];
    credentials.toCharArray(buf, sizeof(buf));
    char *x = buf;
    char *ssid = strtok_r(x, ",", &x);
    char *password = strtok_r(x, ",", &x);

    networkManager.connect(ssid, password);

    digitalWrite(D3, HIGH);
    
    Serial.println("System setup OK!");

    Serial.println("");

    delay(1000);
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
    delay(1000);
    digitalWrite(D1, HIGH);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, HIGH);
    delay(1000);
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
    delay(1000);
    digitalWrite(D1, HIGH);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, HIGH);
    delay(1000);
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D3, LOW);
    delay(1000);
}

void loop() {
    // Non blocking (no delay)
    handleButtonEvent();

    if (millis() - temperatureReadLastRunTime >= 60000) {
      readTemp();
      temperatureReadLastRunTime = millis();
    }

    if (millis() - officeLightUptimeLastRunTime >= 1000) {
        // This needs an abstraction. GPIOManager.toggle(light_status())?
        if(hueManager.light_status(bridgeAPIKey, hueBridgeIP, officeLightId) == 1){
            digitalWrite(D1, HIGH);
        }else{
            digitalWrite(D1, LOW);
        }

        if(hueManager.light_status(bridgeAPIKey, hueBridgeIP, bedroomLightId) == 1){
            digitalWrite(D2, HIGH);
        }else{
            digitalWrite(D2, LOW);
        }

        if(hueManager.light_status(bridgeAPIKey, hueBridgeIP, livingRoomLamp1Id) == 1){
            digitalWrite(D3, HIGH);
        }else{
            digitalWrite(D3, LOW);
        }

        officeLightUptimeLastRunTime = millis();

        // Blocking (delay)
    }
}
