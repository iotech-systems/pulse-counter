
#include "global.h"


void processInBuff() {
   
   Serial.print(F(" + EXE: "));
   Serial.println(SERIAL_IN_BUFF);
   SERIAL_IN_BUFF.trim();
   
   /* update env & get debug */
   if (SERIAL_IN_BUFF.compareTo(F("MDELAY?")) == 0) {
      Serial.print("MAIN_DELAYus: ");
      Serial.println(MAIN_DELAYus);
   } else if (SERIAL_IN_BUFF.compareTo(F("DEBUG_ON")) == 0) {
      BLINKms = 333;
      Serial.println(F("DEBUG_ON_OK"));
   } else if (SERIAL_IN_BUFF.compareTo(F("DEBUG_OFF")) == 0) {
      BLINKms = 1000;
      Serial.println(F("DEBUG_OFF_OK"));
   } else if (SERIAL_IN_BUFF.startsWith(F("CNTX:"))) {
      /* set cntx */
      String cmdval = readCommandValue();
      uint32_t v = (uint32_t)cmdval.toInt();
      uint8_t rval = efs.saveUInt32(FILES::CntxId, v);
      serout.dumpCmdRval(rval, cmdval);
   } else if (SERIAL_IN_BUFF.compareTo(F("CNTX?")) == 0) {
      /* get cntx; print current report context id */
      Serial.print("CNTX: ");
      serout.dumpEpromUInt32(FILES::CntxId, true);
   } else if (SERIAL_IN_BUFF.compareTo(F("EEP?")) == 0) {
      serout.dumpEPROM();
   } else if (SERIAL_IN_BUFF.compareTo(F("EEP:CLR")) == 0) {
      /* clear eeprom */
      efs.clear();
      Serial.println(F("EEP:CLR -> OK"));
   } else if (SERIAL_IN_BUFF.compareTo(F("DEVINFO?")) == 0) {
      /* dumps device info */
      serout.devInfo();
   } else if (SERIAL_IN_BUFF.startsWith(F("HRDW:"))) {
      String cmdval = readCommandValue();
      int rval = efs.saveString(FILES::HStr, cmdval);
      serout.dumpCmdRval(rval, cmdval);
   } else if (SERIAL_IN_BUFF.startsWith(F("SFTW:"))) {
      /* safe software string */
      String cmdval = readCommandValue();
      int rval = efs.saveString(FILES::SStr, cmdval);
      serout.dumpCmdRval(rval, cmdval);
   } else if (SERIAL_IN_BUFF.startsWith(F("EDGE:"))) {
      String cmdval = readCommandValue();
      int rval = efs.saveString(FILES::Edge, cmdval);
      serout.dumpCmdRval(rval, cmdval);
   } else if (SERIAL_IN_BUFF.startsWith(F("GATE:"))) {
      String cmdval = readCommandValue();
      int rval = efs.saveString(FILES::Gate, cmdval);
      serout.dumpCmdRval(rval, cmdval);
   } else if (SERIAL_IN_BUFF.startsWith(F("INSDATE:"))) {
      String cmdval = readCommandValue();
      int rval = efs.saveString(FILES::InstallDate, cmdval);
      serout.dumpCmdRval(rval, cmdval); 
   } else if (SERIAL_IN_BUFF.startsWith(F("BADR:"))) {
      String cmdval = readCommandValue();
      int rval = efs.saveChar(FILES::BAdr, cmdval.c_str()[0]);
      serout.dumpCmdRval(rval, cmdval);
   } else if (SERIAL_IN_BUFF.startsWith(F("COLLINFO?"))) {
      /* print collector info */
      serout.collInfo();
   } else if (SERIAL_IN_BUFF.startsWith(F("FILES?"))) {
      /* dump all files */
      serout.dumpFiles();
   } else if(SERIAL_IN_BUFF.startsWith(F("RINTV:"))) {
      String s = readCommandValue();
      REPORT_INTERVAL_mn = (uint8_t)s.toInt();
      efs.saveUInt8(FILES::RIntv, REPORT_INTERVAL_mn);
      /* only from 1 to 59 */
      if (REPORT_INTERVAL_mn == 0 || REPORT_INTERVAL_mn > 59) {
          Serial.print(F("SET_RINT_VAL_ERR: [1-59] only!"));
      } else {
         /**/
      }
   } else if (SERIAL_IN_BUFF.compareTo(F("HELP")) == 0) {
      serout.printHelp();
   } else if (SERIAL_IN_BUFF.startsWith(F("PINS?"))) {
      /* dump pin nums */
      getPinsConf();
      /* print pins without clear */
      serout.dumpPeakPins();
   } else if (SERIAL_IN_BUFF.startsWith(F("PINS:"))) {
      String cmdval = readCommandValue();
      uint16_t v = (uint16_t)cmdval.toInt();
      setPins(v);
   } else {
      Serial.print(F("BAD_CMD: "));
      Serial.println(SERIAL_IN_BUFF);
   }
   
   /* reset */
   SERIAL_IN_BUFF = "";
   BUFF_IN_READY = false;

};
