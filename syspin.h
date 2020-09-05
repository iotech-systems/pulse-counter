
#ifndef SYSPIN_H
#define SYSPIN_H


class SysPin {

   public:

      uint8_t pin = 0;
      String lbl;
      
      /* c-tors */
      SysPin();
      SysPin(uint8_t);
      
      /* methods */
      void Scan();
      void Init();
      void Print(bool);
      void PrintPeak(bool);
      void PrintTotal(bool);
      void SetCount(uint16_t);
      void PrintLbl();
      uint8_t PinVal();
      uint16_t PulseCount();

   private:
      
      uint8_t last_val = 0;
      uint8_t curr_val = 0;
      uint16_t pulse_count = 0;
      uint16_t pulse_width = 0;
      uint32_t low_to_high = 0;
      uint32_t high_to_low = 0;
      uint32_t total_pulse_count = 0;
      
};

#endif
