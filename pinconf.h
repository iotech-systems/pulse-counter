

#ifndef PIN_CONF_H
#define PIN_CONF_H


class PinConf {

   public:

      uint8_t mcu_pin = 0;
      String pin_lbl;
      
      /* c-tors */
      PinConf(String, uint8_t);

      void Print();
      
   private:
      
};

#endif
