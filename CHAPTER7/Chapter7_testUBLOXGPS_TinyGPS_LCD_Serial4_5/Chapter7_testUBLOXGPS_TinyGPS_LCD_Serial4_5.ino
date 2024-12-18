// Chapter7-testUBLOXPGS_TinyGPS_LCD_Serial4_5.ino
#include <TinyGPS.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>


// DEFINE THE CONNECTION OF LCD PINS TO THE ARDUINO PINS
const int RS = 7, E = 8, D4 = 9, D5 = 6, D6 = 3, D7 = 2;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);  // DEFINE THE LiquidCrystal AS lcd
                            // ONLY 6 PINS NEED TO BE SPECIFIED
                            // (THE RS, E, D4, D5, D6, D7)

// GPS RX connects to Arduino UNO pin 4
// GPS TX connects to Arduino UNO pin 5
SoftwareSerial mySerial(5, 4);  

TinyGPS gps;

void setup() {
  lcd.begin(16, 2); // USE A 16X2 LCD
  lcd.setCursor(0,0); // CURSOR SET AT (0,0) - 1st column & 1st row
  lcd.print("Chapter 7: GPS");
  lcd.setCursor(0,1); // CURSOR SET AT (0,1) - 1st column & 2nd row 
  lcd.print("Read GPS .....");
  delay(1000); // delay 5 seconds
}

// A function to get GPS data and print to LCD
void getgps(TinyGPS &gps)
{
  float latitude, longitude; int year; byte month,day,hour,minute,second,hundredths;
  gps.f_get_position(&latitude,&longitude);
  gps.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths);
  // print GPS data to the LCD
  lcd.setCursor(0,0); lcd.print("Lat: "); lcd.print(latitude,5); lcd.print("    ");
  lcd.setCursor(0,1); lcd.print("Lon: "); lcd.print(longitude,5);lcd.print(" ");
  delay(1000); // delay 3 seconds
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

  delay(1000); // delay 1 seconds
  lcd.clear();

}

void loop() {
  // repeating the following actions:
   byte GPSdata;
   mySerial.begin(9600);
    if (mySerial.available() > 0)
     {
     GPSdata = mySerial.read();
      if(gps.encode(GPSdata))
       {
         getgps(gps);
       }
     }
}

