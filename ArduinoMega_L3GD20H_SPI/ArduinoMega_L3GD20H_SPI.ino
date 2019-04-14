/***************************************************
  This is an example for the Adafruit Triple-Axis Gyro sensor

  Designed specifically to work with the Adafruit L3GD20 Breakout
  ----> https://www.adafruit.com/products/1032

  These sensors use I2C or SPI to communicate, 2 pins (I2C)
  or 4 pins (SPI) are required to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Kevin "KTOWN" Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#include <FlexiTimer2.h>
#include <Wire.h>
#include <Adafruit_L3GD20.h>

// Comment this next line to use SPI
//#define USE_I2C

#ifdef USE_I2C
// The default constructor uses I2C
Adafruit_L3GD20 gyro;
#else
// To use SPI, you have to define the pins
#define GYRO_CS 49 // labeled CS   ----> mega CS
#define GYRO_DO 50 // labeled SA0  ----> mega MISO
#define GYRO_DI 51  // labeled SDA ----> mega MOSI
#define GYRO_CLK 52 // labeled SCL ----> mega SCK
Adafruit_L3GD20 gyro(GYRO_CS, GYRO_DO, GYRO_DI, GYRO_CLK);
#endif

const int DT = 15;
double deg_x = 0;
double deg_y = 0;
double deg_z = 0;


void flash() {
  gyro.read();
  deg_x += gyro.data.x * DT / 1000;
  deg_y += gyro.data.y * DT / 1000;
  deg_z += gyro.data.z * DT / 1000;
}
void setup()
{
  Serial.begin(9600);
  FlexiTimer2::set(DT, 1.0 / 1000, flash); // DT * 1ms ごとにタイマー割込み
  FlexiTimer2::start();

  // Try to initialise and warn if we couldn't detect the chip
  if (!gyro.begin(gyro.L3DS20_RANGE_250DPS))
    //if (!gyro.begin(gyro.L3DS20_RANGE_500DPS))
    //if (!gyro.begin(gyro.L3DS20_RANGE_2000DPS))
  {
    Serial.println("Oops ... unable to initialize the L3GD20. Check your wiring!");
    while (1);
  }
}

void loop()
{


  Serial.print("X: "); Serial.print((int)deg_x);   Serial.print(" ");
  Serial.print("Y: "); Serial.print((int)deg_y);   Serial.print(" ");
  Serial.print("Z: "); Serial.println((int)deg_z); Serial.print(" ");
  delay(100);
}
