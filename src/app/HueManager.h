#ifndef HUEMANAGER_H
#define HUEMANAGER_H

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

class HueManager {
  public:
      void light_on(String bridgeAPIKey, String ip, String id);
      void light_off(String bridgeAPIKey, String ip, String id);
      bool light_status(String bridgeAPIKey, String ip, String id);

  private: 
    String bridgeAPIKey;
};

extern HueManager hugeManager;

#endif
