
#ifndef SERIALOUT_H 
#define SERIALOUT_H

class SerialOut {

   public:
   
      /* c-tor */
      SerialOut();

      /* dev info methods */
      void devInfo();
      void collInfo();
      void collGate();
      void collEdge();
      void boardAddress();
      void collBoardAdr();
      void collShortInfo();

      /* report methods */
      void ping();
      void cntxID();
      void endTail();
      void runReport();
      void printReportEnd();
      void dumpPulseCounts(uint8_t);
      void dumpPeakPins();
      
      /* eprom */
      void dumpEPROM();
      void dumpFiles();
      void dumpEpromStr(FILES, bool);
      void dumpEpromChar(FILES, bool);
      void dumpEpromUInt8(FILES, bool);
      void dumpEpromUInt16(FILES, bool);
      void dumpEpromUInt32(FILES, bool);

      /* system prints */
      void dumpCmdRval(int, String);
      void flashStr(const __FlashStringHelper*);
      void flashStrEx(const char*);
      void printHelp();
      
};

#endif
