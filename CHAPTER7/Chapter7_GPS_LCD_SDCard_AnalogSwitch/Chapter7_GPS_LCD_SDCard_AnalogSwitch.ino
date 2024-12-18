// Chapter7_GPS_LCD_SDCard_AnalogSwitch.ino
#include <TinyGPS.h>
#include <LiquidCrystal.h>
#include <SD.h>
const int chipSelect = 10;
LiquidCrystal lcd(7, 8, 9, 6, 3, 2); // DEFINE THE WIRING OF LCD

TinyGPS gps; // DEFINE THE NAME OF GPS

void setup() {
Serial.begin(9600);
  lcd.begin(16, 2); // DEFINE THE DIMENSION OF LCD
  lcd.setCursor(0,0); // PUT CURSOR AT ORIGIN
  lcd.print("Getting ready..."); // PRINT A MESSAGE
  delay(3000); // delay 3 seconds

  if (!SD.begin(chipSelect)) {
  lcd.setCursor(0,1);
    lcd.print("Card failed   "); // PRINT A MESSAGE
     return;
  }
  lcd.setCursor(0,1); // PUT CURSOR AT 2ND ROW
  lcd.println("card OK...      "); // PRINT A MESSAGE
  delay(3000); // delay 3 seconds
  File dataFile = SD.open("GPSData.txt", FILE_WRITE); // OPEN DATA FILE TO WRITE
                                                      // TO SD CARD
    dataFile.println("NaN, NaN, NaN, NaN, NaN, NaN, NaN, NaN"); // PRINT A LINE
      // THE ABOVE LINE IS INSERTED INTO THE DATA FILE EVERY TIME THE 
      // ARDUINO IS RESTARTED. THIS WILL MAKE IT CONVENIENT TO READ IN
      // MATLAB TO AVOID PROBLEM WITH PLOTTING THE DATA WITH LARGE GAPS. 
    dataFile.close();
}

// A FUNCTION TO BE USED REPEATEDLY TO GET GPS DATA
void getgps(TinyGPS &gps)
{
  File dataFile = SD.open("GPSData.txt", FILE_WRITE);  // OPEN DATA FILE TO WRITE
                                                      // TO SD CARD
  // DEFINE THE DATA TYPES AND NAMES
  float latitude, longitude; int year;
  byte month,day,hour,minute,second,hundredths;
  // GET THE DATA FROM GPS
  gps.f_get_position(&latitude,&longitude);
  gps.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths);
  // PRINT THE LAT & LON ON THE LCD
  lcd.setCursor(0,0); lcd.print("Lat: "); lcd.print(latitude,5);
  lcd.print("    ");
  lcd.setCursor(0,1); lcd.print("Lon: "); lcd.print(longitude,5);
  lcd.print(" "); delay(3000); lcd.clear();
  // PRINT TIME ON THE LCD
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
  // PRINT THE DATE ON THE LCD  
  lcd.setCursor(0,1); lcd.print("Date:"); lcd.print(year,DEC);
  lcd.print("."); lcd.print(month,DEC); lcd.print(".");
  lcd.print(day,DEC);
  delay(3000);
  // SAVE THE GPS DATA ON THE SD CARD 
    dataFile.print(year,DEC); dataFile.print(", ");
    dataFile.print(month,DEC); dataFile.print(", ");
    dataFile.print(day,DEC); dataFile.print(", ");
    dataFile.print(hour,DEC); dataFile.print(", ");
    dataFile.print(minute,DEC); dataFile.print(", ");
    dataFile.print(second,DEC); dataFile.print(", ");
    dataFile.print(latitude,5); dataFile.print(", ");
    dataFile.print(longitude,5); dataFile.println(" ");
    dataFile.close();
  lcd.clear();
}

void loop() {
  // REPEATEDLY DO THE FOLLOWING TO GET THE GPS DATA,
  // DISPLAY ON THE LCD, AND SAVE ON THE SD CARD
byte GPSData;
  int test = analogRead(5); // IF THE ANALOG PIN A5 IS NOT GROUNDED
                            // READ GPS DATA, OTHERWISE 
                            // NO ACTION, ALLOWING STOP SAVING
                            // DATA TO SD CARD WHEN THE SWITCH 
                            // IS TURNED OFF
  if (test>0) {
   if (Serial.available() > 0)
    {
      GPSData = Serial.read();
      if(gps.encode(GPSData))
       {
        getgps(gps);
       }
    }
  }
}