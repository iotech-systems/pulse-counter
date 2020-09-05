
#include "serial_out.h"
#include "devinfo.h"


SerialOut::SerialOut() {};


void SerialOut::devInfo() { 
   this->flashStr(F("#|DEVINFO"));
   Serial.print("|H:");
   this->flashStrEx(__hrdw__);
   Serial.print("|S:");
   this->flashStrEx(__sftw__);
   this->endTail();
};


void SerialOut::collInfo() { 
   this->flashStr(F("#|COLLINFO"));
   this->collGate();
   this->collEdge();
   this->collBoardAdr();
   this->endTail();
};


void SerialOut::collGate() {
   Serial.print("|GATE:");
   this->dumpEpromStr(FILES::Gate, false);
};

   
void SerialOut::collEdge() {
   Serial.print("|EDGE:");
   this->dumpEpromStr(FILES::Edge, false);
};


void SerialOut::collBoardAdr() {
   Serial.print("|BADR:");
   this->dumpEpromChar(FILES::BAdr, false);  
};


void SerialOut::cntxID() {
   Serial.print("|CNTX:");
   Serial.print(CNTXID);
};

void SerialOut::collShortInfo() { 
   this->collEdge();
   this->collBoardAdr();
};


void SerialOut::flashStr(const __FlashStringHelper* fstr) {
   Serial.print(fstr);
};


void SerialOut::flashStrEx(const char* buff) {
   char chr;
   for (byte k = 0; k < strlen_P(buff); k++) {
      chr = pgm_read_byte_near(buff + k);
      Serial.print(chr);
   }
};


void SerialOut::runReport() {
   /* report print counter */
   static uint32_t PRINT_IDX = 0;
   /* report header */
   Serial.print(F("#|RPT:"));
   Serial.print(REPORT_INTERVAL_mn);
   Serial.print(F("M"));
   /* version */
   Serial.print("|V:001");
   /* shor dev info */
   this->collShortInfo();
   Serial.print("|CNTX:");
   this->dumpEpromUInt32(FILES::CntxId, false);
   Serial.print("|RIDX:");
   Serial.print(PRINT_IDX);
   /* pins */
   Serial.print("|JSN:");
   this->dumpPulseCounts(PRINT_MODE_SCAN);
   /* end of buffer */
   this->endTail();
   /* it can track for ~8171 years */
   PRINT_IDX++;
};


void SerialOut::ping() {
   static uint16_t ping_cnt = 0;
   if (ping_cnt == 60000) {
      this->flashStr(F("#|PING"));
      this->collShortInfo();
      this->printReportEnd();
      ping_cnt = 0;
   }
   /* - - */
   ping_cnt++;  
};


void SerialOut::dumpEpromStr(FILES F, bool withln) {
   uint16_t s = FAT[F][0];
   for (s; s < FAT[F][1];  s++) {
      if(EEPROM[s] != 0 && EEPROM[s] != '\0')
         Serial.print((char)EEPROM[s]);
   }
   /* - - */
   if (withln)
      Serial.print('\n');
};


void SerialOut::dumpEpromChar(FILES F, bool withln) {
   Serial.print((char)EEPROM[FAT[F][0]]);
   if (withln)
      Serial.print('\n');
};


void SerialOut::dumpEpromUInt8(FILES F, bool withln) {
   Serial.print((uint8_t)EEPROM[FAT[F][0]]);
   if (withln)
      Serial.print('\n');  
};


void SerialOut::dumpEpromUInt32(FILES F, bool withln) {
   uint32_t v = 0;
   uint32_t vref = EEPROM.get(FAT[F][0], v);
   Serial.print(v);
   /* - - */
   if (withln)
      Serial.print('\n');  
};


void SerialOut::dumpEPROM() {
   Serial.println(F("---EEPROM---"));
   for (uint16_t i = 0; i < EEPROM.length(); i++) {
      Serial.print((char)EEPROM[i]);
      if ((i != 0) && ((i + 1) % 64) == 0) {
         Serial.print(" - ");
         Serial.print(i);
         Serial.println(" -");
      }
   }
   Serial.println(F("--- EEPROM ---"));
};


void SerialOut::dumpCmdRval(int rv, String cmdval) {
   Serial.print("rval: ");
   Serial.println(rv);
   Serial.println(cmdval);   
};


void SerialOut::dumpFiles() {
   Serial.print(F("#|FILES"));
   /* eeprom size */
   Serial.print(F("|EEPROM_SIZE: "));
   Serial.print(EEPROM.length());
   /*  files */
   Serial.print(F("|HStr: "));
   this->dumpEpromStr(FILES::HStr, false);
   Serial.print(F("|SStr: "));
   this->dumpEpromStr(FILES::SStr, false);
   Serial.print(F("|BAdr: "));
   this->dumpEpromChar(FILES::BAdr, false);
   Serial.print(F("|RIntv: "));
   this->dumpEpromUInt8(FILES::RIntv, false);
   Serial.print(F("|CntxID: "));
   this->dumpEpromUInt32(FILES::CntxId, false);
   Serial.print(F("|Edge: "));
   this->dumpEpromStr(FILES::Edge, false);
   Serial.print(F("|Gate: "));
   this->dumpEpromStr(FILES::Gate, false);
   /* mark end of buffer */
   this->endTail();
};


void SerialOut::dumpPulseCounts(uint8_t mode) {
   bool islast = false;
   Serial.print("{");
   /* - - */
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
   /* - - */
   Serial.print("}");
};


void SerialOut::dumpPeakPins() {
   bool islast = false;
   Serial.print("-- PINS PEAK --\n{");
   for (uint8_t i = 0; i < PINCNT; i++) {
      islast = (i == (PINCNT - 1));
      SYSPINS[i].PrintPeak(islast);
   }
   Serial.print("}\n\n");
};


void SerialOut::printReportEnd() {
   Serial.println(F("|##"));
};


void SerialOut::printHelp() {
   this->flashStrEx(__helpHdr__);
   this->flashStrEx(__help0__);
   this->flashStrEx(__help1__);
   this->flashStrEx(__help2__);
   Serial.println("\n");
};


void SerialOut::endTail() {
   Serial.println(F("|##"));
};
