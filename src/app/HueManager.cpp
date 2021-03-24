#include "HueManager.h";

void HueManager::light_on(String bridgeAPIKey, String ip, String id){
  HTTPClient http;
  http.begin("http://" + ip + "/api/" + bridgeAPIKey + "/lights/" + id + "/state");
  http.PUT("{\"on\": true}");
}

void HueManager::light_off(String bridgeAPIKey, String ip, String id){
  HTTPClient http;
  http.begin("http://" + ip + "/api/" + bridgeAPIKey + "/lights/" + id + "/state");
  http.PUT("{\"on\": false}");
}

bool HueManager::light_status(String bridgeAPIKey, String ip, String id){
  HTTPClient http;
  
  http.begin("http://" + ip + "/api/" + bridgeAPIKey + "/lights/" + id);
  http.GET();
  
  DynamicJsonDocument doc(2048);
  deserializeJson(doc, http.getStream());
  
  http.end();

  return doc["state"]["on"].as<bool>();
}
