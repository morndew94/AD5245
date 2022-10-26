#include "Arduino.h"
#include <Wire.h>

#include "AD5245.h"

AD5245::AD5245(void) {}

bool AD5245::begin(uint8_t i2c_address, TwoWire *wire) {
  i2c_dev = new Adafruit_I2CDevice(i2c_address, wire);

  if (!i2c_dev->begin()) {
    return false;
  }

  mode_selector = new Adafruit_BusIO_Register(i2c_dev, DS3502_MODE, 1);
  mode_selector->write(0x80);
  return true;
}


uint8_t AD5245::getWiper(void) {
  Adafruit_BusIO_Register wiper =
      Adafruit_BusIO_Register(i2c_dev, DS3502_WIPER, 1);
  return wiper.read();
}

void AD5245::setWiper(uint8_t new_wiper_value) {
  if ((new_wiper_value > 127) || (new_wiper_value < 0)) {
    return;
  }
  Adafruit_BusIO_Register wiper =
      Adafruit_BusIO_Register(i2c_dev, DS3502_WIPER, 1);
  wiper.write(new_wiper_value);
}

void AD5245::setWiperDefault(uint8_t new_wiper_default) {
  if ((new_wiper_default > 127) || (new_wiper_default < 0)) {
    return;
  }

  Adafruit_BusIO_Register wiper =
      Adafruit_BusIO_Register(i2c_dev, DS3502_WIPER, 1);

  mode_selector->write(0x00);     // set mode to write default on wiper write
  wiper.write(new_wiper_default); // write the new wiper value which carries
                                  // over to the IVR
  delay(100); // delay to allow EEPROM write to IVR to finish
  mode_selector->write(0x80);
}
