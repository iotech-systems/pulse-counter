
#include "global.h"


/* init pins */
void initPins() {
   Serial.println("INITPINS");
   pinMode(LED_BUILTIN, OUTPUT);
   for (uint8_t idx = 0; idx < PINCNT; idx++) {
      SYSPINS[idx].pin = PINS[idx];
      SYSPINS[idx].lbl = PINLBLS[idx];
      SYSPINS[idx].Init();
   }
};


void setPins(uint16_t v) {
   for (uint8_t idx = 0; idx < PINCNT; idx++) {
      SYSPINS[idx].SetCount(v);
   }   
};


void getPinsConf() {
   Serial.println("--- PINS CONF ---");
   for (byte i = 0; i < sizeof(PINS); i++) {
      Serial.print(PINLBLS[i]);
      Serial.print(": ");
      Serial.print(PINS[i]);
      if (i < (sizeof(PINS) - 1))
         Serial.print(", ");
   }
   Serial.println("\n");
   /*Serial.println("--- PINS CONF 1 ---");
   uint8_t len = sizeof(PINCONF) / sizeof(PinConf);
   Serial.println(len);
   for (byte i = 0; i < len; i++) {
      PINCONF[i].Print();
      if (i < (len - 1))
         Serial.print(", ");
   }
   Serial.println("\n*");*/
};


void setReportContext() {
   /* read context id from eeprom */
   uint32_t v = efs.getUInt32(FILES::CntxId);
   efs.saveUInt32(FILES::CntxId, ++v);
};


void blinkLed() {
   static uint32_t LAST_CALLms = 0;
   if ((millis() - LAST_CALLms) > BLINKms) {
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      LAST_CALLms = millis();
   }
};


/* gets called by Serial on char in */
void serialEvent() {
   static char __chr__;
   while(Serial.available()) {
      __chr__ = (char)Serial.read();
      SERIAL_IN_BUFF += __chr__;
      /* test charin for \n */
      if (__chr__ == '\n')
         BUFF_IN_READY = true;
   }
};


void printPulseCounts(uint8_t mode) {
   bool islast = false;
   Serial.print("|");
   for (uint8_t i = 0; i < PINCNT; i++) {
      islast = (i == (PINCNT - 1));
      switch(mode) {
         case 0:
            SYSPINS[i].PrintTotal(islast);
            break;
         case 2:
            SYSPINS[i].Print(islast);
            break;
         default:
            break;
      }
   }
};


String readCommandValue() {
   uint8_t pos = SERIAL_IN_BUFF.indexOf(":");
   String __s__ = String(SERIAL_IN_BUFF.substring(++pos));
   __s__.trim();
   return __s__;
};
