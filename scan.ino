
#include "global.h"


void scanPins() {
   uint32_t start_scan = micros();
   for (uint8_t i = 0; i < PINCNT; i++)
      SYSPINS[i].Scan();
   PINS_SCAN_DURA += ((micros() - start_scan) + 30);
   /* every 1000 loops compute avr. loop time */
   if (PINS_SCAN_CNTR == 1000) {
      PINS_SCAN_AVG = (PINS_SCAN_DURA / PINS_SCAN_CNTR);
      PINS_SCAN_DURA = 0;
      PINS_SCAN_CNTR = 0;
      /* update main delay */
      MAIN_DELAYus = (HZ1K - PINS_SCAN_AVG);
   }
   /* incr loop counter */
   PINS_SCAN_CNTR++;
};
