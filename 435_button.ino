/* Code for reading in input of button presses
 * Using 4 buttons generates  string using alphabet {0,1} 
 * Reading done via changes seen in PORTD variable
 * Modes to edit saved password on EEPROM (gotta brainstorm)
 */
#include <EEPROM.h>
#include <TimerOne.h>

byte button_reads[4] = {B10000000, B00100000, B00010000, B00001000};
byte prev = 0;
byte current = 0;
volatile bool input_mode = false;
String input_string = "";
const int pwd_addr = 0;
String password = "";

void setup() {
  DDRD = B00000000;
  Timer1.initialize(60000000);//A minute long timer
  Timer1.attachInterrupt(timer_isr);
  Timer1.stop();
  EEPROM.get(0,password);
  Serial.begin(9600);
}

void timer_isr(){
  input_mode = false;
  Timer1.stop();//Is this valid??
}

void loop() {
  if(input_mode){
    Timer1.resume();
  }
  while(input_mode){
    prev = PIND;
    current = PIND;
    if(current > prev && current^prev == button_reads[0]){ 
      input_mode = false;
      break;
    }
    if(current > prev && current^prev == button_reads[1]) input_string = input_string + "0";
    if(current > prev && current^prev == button_reads[2]) input_string = input_string + "1"; 
  }
  if (input_string != password) PORTD = PORTD | B00000100;//Buzzer turns on
}
