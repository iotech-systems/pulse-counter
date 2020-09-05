
#ifndef EEPFS_MAP_H
#define EEPFS_MAP_H


const uint16_t FAT[][2] = 
   {{0, 31},       /* 0, Hrdwstr: hardware string */ 
   {32, 63},       /* 1, Sftwstr: software string */
   {64, 64},       /* 2, Badr: board address */
   {65, 65},       /* 3, Rintv: report interval # of minutes */
   {66, 69},       /* 4, 32 bit uint mcu boot counter; gives report index context */
   {200, 195},     /* 5, */
   {196, 196},     /* 6, */
   {197, 229},     /* 7, */
   {230, 261},     /* 8, */
   {512, 767},     /* 9, */
   {768, 1024}};   /* 10, */


enum FILES : uint8_t {
   HStr = 0,            /* 32 bytes */
   SStr = 1,            /* 32 bytes */
   BAdr = 2,             /* 1 byte */
   RIntv = 3,            /* 1 byte */
   CntxId = 4,           /* 4 byte */
   Hellointv = 5,        /* 1 byte */
   Debugflag = 6,        /* 1 byte */
   Edge = 7,             /* 32 bytes */
   Gate = 8,             /* 32 bytes */
   BigBuff1 = 9,         /* 256 */
   BigBuff2 = 10         /* 256 */
};

#endif
