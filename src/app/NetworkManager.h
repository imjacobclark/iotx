#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

class NetworkManager {
  public:
      void connect(const char* ssid, const char* password);

  private: 
    IPAddress local_IP;
    IPAddress gateway;
    IPAddress subnet;
    IPAddress primaryDNS;
    IPAddress secondaryDNS;
};

extern NetworkManager networkManager;

#endif
