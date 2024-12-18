/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
  See the LICENSE file for details.
 ***************************************************************************/

// Chapter8_test_bme280_lcd2.ino
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 6, 3, 2); // DEFINE THE WIRING OF LCD

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
unsigned long delayTime;

void setup() {
  Serial.begin(9600);
  lcd.begin(20, 4); // DEFINE THE DIMENSION OF LCD
  lcd.setCursor(0,0); // PUT CURSOR AT ORIGIN
  lcd.print("Getting ready..."); // PRINT A MESSAGE
  delay(3000); // delay 3 seconds

    while(!Serial);    // time to get serial running
    Serial.println(F("BME280 test"));

    unsigned status;
    
    // default settings
    status = bme.begin();  
    // You can also pass in a Wire library object like &Wire2
    // status = bme.begin(0x76, &Wire2)
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
        while (1) delay(10);
    }
    
    Serial.println("-- Default Test --");
    delayTime = 1000;

    Serial.println();
}


void loop() { 
    printValues2SMLCD();
    delay(delayTime);
}


void printValues2SMLCD() {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" °C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();

     lcd.setCursor(0,0); lcd.print("Data Adafruit BME280");
     lcd.setCursor(0,1); lcd.print("Temp. = ");
     lcd.print(bme.readTemperature());
     lcd.print(" C     ");
     lcd.setCursor(0,2); lcd.print("Press = ");
     lcd.print(bme.readPressure() / 100.0F);
     lcd.print(" hPa");
     lcd.setCursor(0,3); lcd.print("Altitude = ");
     lcd.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
     lcd.print(" m");
}
