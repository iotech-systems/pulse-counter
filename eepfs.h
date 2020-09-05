
#ifndef EEPFS_H
#define EEPFS_H

#include "eepfs_map.h"
#include "eepfs.h"


class EEPFSv1 {

   public:

      EEPFSv1();

      /* writes */
      int saveString(FILES, String); 
      bool saveUInt8(FILES, uint8_t);
      bool saveUInt16(FILES, uint16_t);
      bool saveUInt32(FILES, uint32_t);
      bool saveChar(FILES, char);

      /* reads */
      String getString(FILES);
      uint8_t getUInt8(FILES);
      uint16_t getUInt16(FILES);
      uint32_t getUInt32(FILES);
      char getChar(FILES);

      void clear();

   private:

      bool checkSpace(FILES, uint8_t);

};

#endif
