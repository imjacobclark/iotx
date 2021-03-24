#include "DHTAM2302Manager.h"

float DHTAM2302Manager::get_temperature(){
  DHTesp dht;
  dht.setup(D5, DHTesp::DHT22);
  delay(dht.getMinimumSamplingPeriod());
  return dht.getTemperature();
}

float DHTAM2302Manager::get_humidity(){
  DHTesp dht;
  dht.setup(D5, DHTesp::DHT22);
  delay(dht.getMinimumSamplingPeriod());
  return dht.getHumidity();
}
