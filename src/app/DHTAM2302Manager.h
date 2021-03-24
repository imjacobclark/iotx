/*
 * Required libraries: 
 * DHTesp - https://github.com/beegee-tokyo/DHTesp
 */

#ifndef DHTAM2302MANAGER_H
#define DHTAM2302MANAGER_H

#include <Arduino.h>
#include "DHTesp.h"

class DHTAM2302Manager {
  public:
      float get_temperature();
      float get_humidity();
  private: 
};

extern DHTAM2302Manager dhtAM2303Manager;

#endif
