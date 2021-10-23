/*
  LiquidCrystal Library - Hello World

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld
*/

// include the library code:
#include <LiquidCrystal.h>
#include <TimerOne.h>
const int rs = 12, en = 11, d4 = 13, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
volatile int8_t count = 5;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Time Left:   s");
  lcd.setCursor(11,0);
  Timer1.attachInterrupt(check);
  Timer1.initialize(1000000);
}

void loop() {
  lcd.print(count);
  lcd.setCursor(0,0);
  if(count != 0) return;
  Timer1.detachInterrupt();
  lcd.setCursor(0,0);
  lcd.print("Game Over!    ");

}

void check()
{
  count--;
}
