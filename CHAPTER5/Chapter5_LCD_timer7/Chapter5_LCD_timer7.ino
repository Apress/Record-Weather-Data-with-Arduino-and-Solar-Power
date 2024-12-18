// Saved as Chapter5_LCD_timer7.ino, to display time lapsed in MM:SS format
#include <LiquidCrystal.h> // include the library for the LCD

// THE HD44780 LCD HAS 16 CONNECTIONS, THEY ARE NAMED AS:
//         MAMES   VSS, VDD, V0, RS, RW,  E, D0, D1, D2, D3, D4, D5, D6, D7, A,  K
// LCD PIN NUMBERS  1,   2,   3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16
// DEFINE THE CONNECTION OF LCD PINS TO THE ARDUINO PINS
const int RS = 7, E = 8, D4 = 9, D5 = 6, D6 = 3, D7 = 2;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);  // DEFINE THE LiquidCrystal AS lcd
                            // ONLY 6 PINS NEED TO BE SPECIFIED
                            // (THE RS, E, D4, D5, D6, D7)
void setup() {
  // WE ARE USING THE 16X2 LCD
  lcd.begin(16, 2);
  //  lcd.begin(20, 4);  // IF WE USE THE 20X4 LCD
}

void loop() {
  // THIS IS CODE FOR A TIMER DISPLAYED BY A 16X2 LCD IN hour:MINUTES:SECONDS 
  // SINCE THE LAST RESET OF THE ARDUINO 
    int t; int t1; // DEFINE AN INTEGER FOR TIME IN SECOND SINCE THE LAST MINUTE
  t = millis() / 1000 - (millis() / 1000/60)*60;    // SECOND SINCE LAST MINUTE
  t1= millis() / 1000 /60 - (millis() / 1000/60/60)*60; // MINUTE SINCE LAST HOUR
  lcd.setCursor(0, 0);
  // THE FOLLOWING PRINTS THE MINUTE SINCE THE RESET OF THE ARDUINO
  // IT IS FOLLOWED BY A COLUMN : AND THEN THE SECOND SINCE THE LAST REPORTED MINUTE
  lcd.print(millis() / 1000/60/60); lcd.print(":"); lcd.print(t1); lcd.print(":");
  if (t < 10 ) {  // IF ONE ONE DIGIT FOR THE SECOND SINCE LAST MINUTE
  lcd.print("0"); lcd.print(t); lcd.print(" ");// PRINT THE TIME IN SECOND
  }
  if (t >= 10) {
  lcd.print(t); lcd.print(" "); // PRINT SECONDS WITH TWO DIGITS
  }
}
