#define _AD5245_H

#include "Arduino.h"
#include <Wire.h>

#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>

#define AD5245_I2CADDR_DEFAULT 0x28 ///< AD5245 default I2C address

#define AD5245_WIPER 0x00 ///< Wiper value register
#define AD5245_MODE 0x02  ///< Mode selection register

class AD5245 {
public:
  AD5245();
  bool begin(uint8_t i2c_addr = AD5245_I2CADDR_DEFAULT, TwoWire *wire = &Wire);
  uint8_t getWiper(void);
  void setWiper(uint8_t new_wiper_value);
  void setWiperDefault(uint8_t new_wiper_default);

  Adafruit_BusIO_Register
      *mode_selector; ///< BusIO Register for selecting the write mode

private:
  Adafruit_I2CDevice *i2c_dev;
};

#endif
