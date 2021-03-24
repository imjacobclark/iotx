#ifndef BUTTONINPUT_H
#define BUTTONINPUT_H

#include <Arduino.h>

class ButtonInput {
  public:
      void setup(int pin);
      int read(int pin);
  private: 
};

extern ButtonInput buttonInput;

#endif
