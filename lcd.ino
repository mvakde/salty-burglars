#include <LiquidCrystal.h>
#include <TimerOne.h>
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
volatile uint8_t currentcount = 60;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Time Left:   s");
  lcd.setCursor(11,0);
  Timer1.attachInterrupt(check);
  Timer1.initialize(1000000);
}

void loop() {
  lcd.print(currentcount);
  lcd.setCursor(11,0);
  if(currentcount != 0) return;
  Timer1.detachInterrupt();
  lcd.setCursor(0,0);
  lcd.print("Game Over!    ");  
  while(true);

}

void check()
{
  currentcount--;
}
