
#include <EEPROM.h>
#include "devinfo.h"
#include "global.h"
#include "syspin.h"
#include "eepfs.h"


void setup() {
   
   Serial.begin(BAUDRATE);
   Serial.println(F("SETUP"));
   
   /* setup pins */
   initPins();

   /* on this mcu contxt will be number of reboots */
   setReportContext();
   
   /* buffer to read all incoming rxtx data */
   SERIAL_IN_BUFF.reserve(MAX_INBUFF_LEN);
   
   /* set report interval */
   uint8_t rint = efs.getUInt8(FILES::RIntv);
   if(rint > 0 && rint < 59) {
      REPORT_INTERVAL_mn = rint;
      Serial.print(F("REPORT_INTERVAL_mn(rint): "));
   } else {
      REPORT_INTERVAL_mn = DEFAULT_REPORT_INTERVAL;
      Serial.print(F("REPORT_INTERVAL_mn(DEFAULT_REPORT_INTERVAL): "));
   }

   /* print report intv */
   Serial.println(REPORT_INTERVAL_mn);
   
   /* set report interval */
   REPORT_COUNTER = (REPORT_INTERVAL_mn * MIN_TO_MILLIS);
   
   /* print ed setup */
   Serial.println(F("END SETUP")); 
   
};


/* main */
void loop() {
   
   /* check in buffer */
   if(BUFF_IN_READY)
      processInBuff();
   
   /* wait till MAIN_DELAYus */
   if((micros() - LAST_TSus) < MAIN_DELAYus)
      return;
   
   /* main system function scan pins */
   scanPins();

   /* try running pin report */
   __try_run_report__();
   
   /* blink led */
   blinkLed();

   /* ping edge */
   serout.ping();
   
   /* pins scan should take no more then 150us */
   /* forces main loop to run @ ~1kHz */
   LAST_TSus = micros();
   
};
