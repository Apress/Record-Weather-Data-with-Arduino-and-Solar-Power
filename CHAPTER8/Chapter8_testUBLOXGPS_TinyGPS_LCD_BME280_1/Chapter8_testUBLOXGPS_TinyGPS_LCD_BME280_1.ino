// Chapter8-testUBLOXPGS_TinyGPS_LCD_BME280_1.ino
#include <TinyGPS.h>
#include <LiquidCrystal.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// DEFINE THE CONNECTION OF LCD PINS TO THE ARDUINO PINS
const int RS = 7, E = 8, D4 = 9, D5 = 6, D6 = 3, D7 = 2;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);  // DEFINE THE LiquidCrystal AS lcd
                            // ONLY 6 PINS NEED TO BE SPECIFIED
                            // (THE RS, E, D4, D5, D6, D7)

#define SEALEVELPRESSURE_HPA (1013.25)

TinyGPS gps;

Adafruit_BME280 bme; // I2C
unsigned long delayTime;

void setup() {
Serial.begin(9600); // GPS SERIAL COMMUNICATION THROUGH ARDUINO BOARD'S 
                    // DEFAULT SERIAL PINS 0 AND 1
                    // GPS TX --> ARDUINO PIN 0 (RX)
                    // GPS RX --> ARDUINO PIN 1 (TX) 
  lcd.begin(20, 4); // USE A 20X4 LCD
  lcd.setCursor(0,0); // CURSOR SET AT (0,0) - 1st column & 1st row
  lcd.print("Chapter8: GPS+BME280");
  lcd.setCursor(0,1); // CURSOR SET AT (0,1) - 1st column & 2nd row 
  lcd.print("Read GPS ...");
  delay(1000); // delay 1 seconds
}

// A function to get GPS data and print to LCD
void getgps(TinyGPS &gps)
{
      unsigned status;
    
    // default settings
    status = bme.begin();
        if (!status) {
        lcd.setCursor(0,0); // CURSOR SET AT (0,0) - 1st column & 1st row
        lcd.println("BME280 not found");
        lcd.setCursor(0,1); // CURSOR SET AT (0,1) - 1st column & 2nd row
        lcd.print("SensorID: 0x"); lcd.println(bme.sensorID(),16);
        lcd.setCursor(0,2); // CURSOR SET AT (0,2) - 1st column & 3rd row
        lcd.print("0xFF: bad address\n");
        lcd.setCursor(0,3); // CURSOR SET AT (0,2) - 1st column & 3rd row
        lcd.print("0x56-0x58: BMP 280\n");
        delay(1000);
        lcd.setCursor(0,0); // CURSOR SET AT (0,0) - 1st column & 1st row
        lcd.print("0x60: BME 280.\n");
        lcd.setCursor(0,1); // CURSOR SET AT (0,1) - 1st column & 2nd row
        lcd.print("0x61: BME 680.\n");
        while (1) delay(1000);
    }
    
    delayTime = 1000;

  float latitude, longitude; int year; byte month,day,hour,minute,second,hundredths;
  gps.f_get_position(&latitude,&longitude);
  gps.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths);
  // print GPS data to the LCD
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("Lat: "); lcd.print(latitude,5);
  lcd.setCursor(0,1); lcd.print("Lon: "); lcd.print(longitude,5);
  delay(3000); // delay 3 seconds
  lcd.clear();

  lcd.setCursor(0,0); lcd.print("Time:");
  if(hour<10)
  {
  lcd.print("0");
  }
  lcd.print(hour,DEC); lcd.print(":");
  if(minute<10)
  {
  lcd.print("0");
  }
  lcd.print(minute,DEC); lcd.print(":");
  if(second<10)
  {
  lcd.print("0");
  }
  lcd.print(second,DEC); lcd.print("UTC");
  
  lcd.setCursor(0,1);
  lcd.print("Date:"); lcd.print(year,DEC); lcd.print(".");
  lcd.print(month,DEC); lcd.print("."); lcd.print(day,DEC);

  delay(3000); // delay 3 seconds
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
  delay(3000); // delay 3 seconds
  lcd.clear();
}

void loop() {
  // repeating the following actions:
byte GPSdata;
if (Serial.available() > 0) 
{
// USE ARDUINO'S SERIAL COMM PINS TO GET GPS DATA
GPSdata = Serial.read();
 if(gps.encode(GPSdata))
 {
 getgps(gps);
 }
}
}

