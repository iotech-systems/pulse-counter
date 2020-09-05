
#include "syspin.h"


SysPin::SysPin() {
   this->last_val = 0;
   this->curr_val = 0;
   this->pulse_count = 0;
   this->pulse_width = 0;
   this->low_to_high = 0;
   this->high_to_low = 0;
   this->total_pulse_count = 0;
};


SysPin::SysPin(uint8_t p) : SysPin() {
   this->pin = p;  
};


void SysPin::Init() {
   pinMode(this->pin, INPUT);
};


void SysPin::Scan() {
   /* read current state; NOT reset input_pullup */
   /* this->curr_val = digitalRead(this->pin);*/
   this->curr_val = this->PinVal();
   /* test state change */
   if ((this->last_val == LOW) && (this->curr_val == HIGH)) {
      this->low_to_high = millis();
      /*this->pulse_count++;*/
   } else if((this->last_val == HIGH) && (this->curr_val == HIGH)) {
      this->pulse_width++;
   } else if((this->last_val == HIGH) && (this->curr_val == LOW)) {
      this->high_to_low = millis();
   } else if((this->last_val == LOW) && (this->curr_val == LOW)) {
      /* on low test previous pulse; only once; incr count  */
      if ((this->high_to_low > this->low_to_high) && (this->pulse_width > MIN_PULSE_TIX)) {
         this->high_to_low = 0;
         this->low_to_high = 0;
         this->pulse_width = 0;
         this->pulse_count++;
      }
   } else {
      /* should never happen */
   }
   /* set current as last */
   this->last_val = this->curr_val;   
};


uint8_t SysPin::PinVal() {
   uint16_t adc = 0;
   if ((this->pin == A6) || (this->pin == A7)) {
      if (analogRead(this->pin) > 512)
         return HIGH;
      else
         return LOW;
   } else {
      return digitalRead(this->pin);
   }
};

uint16_t SysPin::PulseCount() {
   return this->pulse_count;
};


void SysPin::Print(bool islast) {
   this->PrintLbl();
   Serial.print(":");
   Serial.print(this->pulse_count);
   if(!islast)
      Serial.print(",");
   this->total_pulse_count += this->pulse_count;
   this->pulse_count = 0;
};


void SysPin::PrintPeak(bool islast) {
   this->PrintLbl();
   Serial.print(":");
   Serial.print(this->pulse_count);
   if(!islast)
      Serial.print(",");
};


void SysPin::SetCount(uint16_t v) {
   this->pulse_count = v;
};


void SysPin::PrintTotal(bool islast) {
   this->PrintLbl();
   Serial.print(":");
   Serial.print(this->total_pulse_count);
   if(!islast)
      Serial.print(";");
};


void SysPin::PrintLbl() {
   Serial.print("\"");
   Serial.print(this->lbl);
   Serial.print("\"");    
};
