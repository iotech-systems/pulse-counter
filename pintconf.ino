
#include "pinconf.h"


PinConf::PinConf(String lbl, uint8_t pin) {
   this->mcu_pin = pin;
   this->pin_lbl = lbl;   
};


void PinConf::Print() {
   Serial.print(this->pin_lbl);
   Serial.print(": ");
   Serial.print(this->mcu_pin);
};
