
#include "pinconf.h"
#include "syspin.h"
#include "eepfs.h"
#include "serial_out.h"

#ifndef CORE_H
#define CORE_H

/* system will push out cnts every REPORT_INTERVAL_MINS mintues or so
 *  based on loop count; system will run at ~1kHz
 *  every PRINT_LOOP_CNT system will print pin counts
 */

#define HZ1K 1000
/* 5 minute default */
#define DEFAULT_REPORT_INTERVAL 5
#define R1HR_REPORT 3600000
/* number of millis in 5 minutes */
#define R5MIN_LOOP_CNT 300000
/* millis in 1 minute */
#define MIN_TO_MILLIS 60000
#define BAUDRATE 57600
#define PINCNT 16
#define MIN_PULSE_TIX 20
#define PRINT_MODE_TOTAL 0
#define PRINT_MODE_SCAN 2
/* 128 chars + \n */
#define MAX_INBUFF_LEN 129


SysPin SYSPINS[PINCNT];
EEPFSv1 efs = EEPFSv1();
SerialOut serout = SerialOut();


uint8_t REPORT_INTERVAL_mn = 5;

/* report will run every this interval */
uint32_t REPORT_COUNTER = (REPORT_INTERVAL_mn * MIN_TO_MILLIS);
PinConf PINCONF[] = {{"A0", A0}, {"A1", A1}, {"A2", A2}, {"A3", A3}, {"A4", A4}, {"A5", A5}, {"A6", A6}, {"A7", A7},
   {"D2", 2}, {"D3", 3}, {"D4", 4}, {"D5", 5}, {"D6", 6}, {"D7", 7}, {"D8", 8}, {"D9", 9}};
    
uint8_t PINS[] = {A0, A1, A2, A3, A4, A5, A6, A7, 2, 3, 4, 5, 6, 7, 8, 9};
String PINLBLS[] = {"A0", "A1", "A2", "A3", "A4", "A5", "A6", "A7", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9"};

uint16_t BLINKms = 1000;
uint16_t MAIN_DELAYus = 620;
uint32_t PINS_SCAN_CNTR = 0;
uint32_t PINS_SCAN_DURA = 0;
uint32_t PINS_SCAN_AVG = 0;
uint32_t LAST_PINS_SCANus = 0;
uint32_t LAST_TSus = 0;
uint32_t CNTXID = 0;
bool BUFF_IN_READY = false;
String SERIAL_IN_BUFF;


void scanPin(uint8_t);
void scanPins();
void initPins();
void setPins(uint16_t);
void getPinsConf();
void setReportContext();
void printHello();
void printPing();
void __try_run_report__();
void blinkLed();
void processInBuff();
void printHeader(const __FlashStringHelper*);
void printPulseCounts();
void printReportEnd();
void dumpEeprom();
void clearEeprom();
uint8_t eepromWrite(uint16_t, uint16_t, String);
void PrintCharPnt(char*, uint8_t);
String readCommandValue();
void pmemToEeprom(const __FlashStringHelper*);

#endif
