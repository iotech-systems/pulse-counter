
#include "eepfs_map.h"


EEPFSv1::EEPFSv1() {};


int EEPFSv1::saveString(FILES F, String s) {
   /* - - */
   uint16_t sidx = FAT[F][0];
   uint16_t eidx = FAT[F][1];
   uint16_t max_space = eidx - sidx;
   /* - - */
   if (s.length() > max_space) {
      Serial.println(max_space);
      return -1;
   }
   /* write string to eeprom */
   for (uint16_t idx = 0; idx < s.length(); idx++)
      EEPROM[sidx++] = s.c_str()[idx];
   /* write rest of string space with \0 */
   for (sidx; sidx < eidx; sidx++)
      EEPROM[sidx] = '\0';   
   /* - - */
   return 0;
};


bool EEPFSv1::saveUInt8(FILES F, uint8_t v) {
   if (!this->checkSpace(F, sizeof(v)))
      return false;
   EEPROM.put(FAT[F][0], v);
   return (v == (uint8_t)EEPROM[FAT[F][0]]);
};


bool EEPFSv1::saveUInt16(FILES F, uint16_t v) {
   if (!this->checkSpace(F, sizeof(v)))
      return false;
   int16_t* vref = EEPROM.put(FAT[F][0], v);
   return true;
};


bool EEPFSv1::saveUInt32(FILES F, uint32_t v) {
   if (!this->checkSpace(F, sizeof(v)))
      return false;
   int32_t* vref = EEPROM.put(FAT[F][0], v);
   return true;
};


bool EEPFSv1::saveChar(FILES F, char c) {
   EEPROM[FAT[F][0]] = c;
   return (c ==  EEPROM[FAT[F][0]]);
};


String EEPFSv1::getString(FILES F) {
      
};


uint8_t EEPFSv1::getUInt8(FILES F) {
   return (uint8_t)EEPROM[FAT[F][0]];   
};


uint16_t EEPFSv1::getUInt16(FILES F) {
};


uint32_t EEPFSv1::getUInt32(FILES F) {
   uint32_t v = 0;
   EEPROM.get(FAT[F][0], v);
   return v;   
};


char EEPFSv1::getChar(FILES F) {
   return (char)EEPROM[FAT[F][0]]; 
};


void EEPFSv1::clear() {
   for(uint16_t i = 0; i < EEPROM.length(); i++)
      EEPROM[i] = 0;
};


/* max size is 256 bytes */
bool EEPFSv1::checkSpace(FILES F, uint8_t len) {
   uint8_t width = ((FAT[F][1] - FAT[F][0]) + 1);
   return (width == len);
};
