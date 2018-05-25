/*************************************************
 initialisation des composante
 ******************************************************/
#include <Wire.h>
#include <DS3231.h>
DS3231 clock;
RTCDateTime dt;

#include <EEPROM.h>
#include <SPI.h>  // not used here, but needed to prevent a RTClib compile error
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include "Adafruit_Sensor.h"
#define DHTPIN 6
#define DHTTYPE DHT22   // DHT 11
LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
DHT dht(DHTPIN, DHTTYPE);
//DS3231  rtc(SDA, SCL);
