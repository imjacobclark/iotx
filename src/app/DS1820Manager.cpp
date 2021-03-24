#include "DS1820Manager.h"

float DS1820Manager::get_temperature(){
  OneWire oneWire(D5);
  DallasTemperature sensors(&oneWire);

  sensors.begin();
  sensors.requestTemperatures(); 
  return sensors.getTempCByIndex(0);
}