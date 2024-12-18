// Chapter9_GPS_LCD20X4_SDCard_BME280_1.ino
#include <TinyGPS.h>
#include <LiquidCrystal.h>
#include <SD.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SoftwareSerial.h>

const int chipSelect = 10;
LiquidCrystal lcd(7, 8, 9, 6, 3, 2); // DEFINE THE WIRING OF LCD
// GPS RX connects to Arduino UNO pin 4
// GPS TX connects to Arduino UNO pin 5
SoftwareSerial mySerial(5, 4);  

#define SEALEVELPRESSURE_HPA (1013.25)

TinyGPS gps; // DEFINE THE NAME OF GPS

Adafruit_BME280 bme; // I2C
unsigned long delayTime;

void setup() {
  lcd.begin(20, 4); // DEFINE THE DIMENSION OF LCD
  lcd.setCursor(0,0); // PUT CURSOR AT ORIGIN
  lcd.print("Getting ready..."); // PRINT A MESSAGE
  //delay(1000); // delay 1 seconds

  bme.begin();  
  
  if (!SD.begin(chipSelect)) {
  lcd.setCursor(0,1);
    lcd.print("Card failed   "); // PRINT A MESSAGE
     return;
  }
  lcd.setCursor(0,1); // PUT CURSOR AT 2ND ROW
  lcd.print("card OK..."); // PRINT A MESSAGE
  delay(1000); // delay 1 seconds
  File dataFile = SD.open("GPSData7.txt", FILE_WRITE); // OPEN DATA FILE TO WRITE
                                                      // TO SD CARD
    dataFile.println("NaN, NaN, NaN, NaN, NaN, NaN, NaN, NaN, NaN, NaN, NaN, NaN"); // PRINT A LINE
      // THE ABOVE LINE IS INSERTED INTO THE DATA FILE EVERY TIME THE 
      // ARDUINO IS RESTARTED. THIS WILL MAKE IT CONVENIENT TO READ IN
      // MATLAB TO AVOID PROBLEM WITH PLOTTING THE DATA WITH LARGE GAPS. 
    dataFile.close();
}

// A FUNCTION TO BE USED REPEATEDLY TO GET GPS DATA
void getgps(TinyGPS &gps)
{
  File dataFile = SD.open("GPSData7.txt", FILE_WRITE);  // OPEN DATA FILE TO WRITE
                                                      // TO SD CARD
  // DEFINE THE DATA TYPES AND NAMES
  float latitude, longitude; int year;
  byte month,day,hour,minute,second,hundredths;
  // GET THE DATA FROM GPS
  gps.f_get_position(&latitude,&longitude);
  gps.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths);
  // PRINT THE LAT & LON ON THE LCD
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("Lat: "); lcd.print(latitude,5);
  lcd.print("    ");
  lcd.setCursor(0,1); lcd.print("Lon: "); lcd.print(longitude,5);
  lcd.print(" "); // delay(1000); lcd.clear();
  // PRINT TIME ON THE LCD
  lcd.setCursor(0,2); lcd.print("Time:");
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
  // PRINT THE DATE ON THE LCD  
  lcd.setCursor(0,3); lcd.print("Date:"); lcd.print(year,DEC);
  lcd.print("."); lcd.print(month,DEC); lcd.print(".");
  lcd.print(day,DEC);
  delay(2000);

     lcd.setCursor(0,0); lcd.print("Temp. = ");
     lcd.print(bme.readTemperature());
     lcd.print(" C     ");
     lcd.setCursor(0,1); lcd.print("Press = ");
     lcd.print(bme.readPressure() / 100.0F); 
     lcd.print(" hPa");
     lcd.setCursor(0,2); lcd.print("Humidity = ");
     lcd.print(bme.readHumidity()); 
     lcd.print(" %");
     lcd.setCursor(0,3); lcd.print("Altitude = ");
     lcd.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
     lcd.print(" m");
  delay(2000);
//  lcd.clear();

  // SAVE THE GPS DATA ON THE SD CARD 
    dataFile.print(year,DEC); dataFile.print(", ");
    dataFile.print(month,DEC); dataFile.print(", ");
    dataFile.print(day,DEC); dataFile.print(", ");
    dataFile.print(hour,DEC); dataFile.print(", ");
    dataFile.print(minute,DEC); dataFile.print(", ");
    dataFile.print(second,DEC); dataFile.print(", ");
    dataFile.print(latitude,5); dataFile.print(", ");
    dataFile.print(longitude,5); dataFile.print(" ");
    dataFile.print(bme.readTemperature()); dataFile.print(", ");
    dataFile.print(bme.readPressure() / 100.0F); dataFile.print(", ");
    dataFile.print(bme.readHumidity()); dataFile.print(", ");
    dataFile.print(bme.readAltitude(SEALEVELPRESSURE_HPA)); dataFile.println("");
    dataFile.close();
  }

void loop() {
  // REPEATEDLY DO THE FOLLOWING TO GET THE GPS DATA,
  // DISPLAY ON THE LCD, AND SAVE ON THE SD CARD
byte GPSData;
mySerial.begin(9600);
   if (mySerial.available() > 0)
    {
      GPSData = mySerial.read();
      if(gps.encode(GPSData))
       {
        getgps(gps);
       }
    }
}