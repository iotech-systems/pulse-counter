
#include "global.h"


/* this function ges called about at 1k Hz */
void __try_run_report__() {
   /* call counter */
   static uint32_t CC_1HRS = 0;
   static uint32_t CC_REPORT = 0;
   /* - - */
   if (CC_REPORT >= REPORT_COUNTER) {
      serout.runReport();
      CC_REPORT = 0;
   } else {
      CC_REPORT++;
   }
   /* do 1 hrs report */
   if (CC_1HRS == R1HR_REPORT) {
      /*doOneHourReport();*/
      CC_1HRS = 0;
   } else {
      CC_1HRS++;
   }
};
