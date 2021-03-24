#include "ButtonInput.h"

void ButtonInput::setup(int pin){
  pinMode(pin, INPUT);
}

int ButtonInput::read(int pin){
  return digitalRead(pin);
}
