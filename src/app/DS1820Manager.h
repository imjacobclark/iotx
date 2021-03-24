/*
 * Required libraries: 
 * OneWire - https://www.pjrc.com/teensy/td_libs_OneWire.html
 * DallasTemperature - https://github.com/milesburton/Arduino-Temperature-Control-Library
 */

#ifndef DS1820MANAGER_H
#define DS1820MANAGER_H

#include <OneWire.h>
#include <DallasTemperature.h>

class DS1820Manager {
  public:
      float get_temperature();
  private: 
};

extern DS1820Manager ds1820Manager;

#endif
