/* Code for reading in input of button presses
 * Using 4 buttons generates  string using alphabet {0,1} 
 * Reading done via changes seen in PORTD variable
 * Modes to edit saved password on EEPROM
 */
#include <EEPROM.h>
#include <TimerOne.h>

const byte button_0in = 16;
const byte button_1in = 15;
const byte button_clr = 14;
const byte buzzer = 5;
const byte LCDpins[6] = {8,9,10,11,12,13};
const byte OR_buttons = 3;
const byte OR_sensors = 2;
volatile bool read_buttons = false;
volatile bool fire = false;
volatile bool burglar = false;
bool pwd_chng = false;
String input_string = "";
const int pwd_addr = 0;
String password = "";
int seconds_passed = 0;
unsigned long int button_time = 0;

void setup() {
  DDRC = DDRC & B00000000;//All analog pins set to input
  Timer1.initialize(1000000);//A second long timer
  Timer1.attachInterrupt(timerISR);
  Timer1.stop();
  attachInterrupt(digitalPinToInterrupt(OR_buttons), buttonISR, RISING);
  attachInterrupt(digitalPinToInterrupt(OR_sensors), sensorISR, RISING);
  EEPROM.get(0,password);
  Serial.begin(9600);
}

void timerISR(){
  seconds_passed++;
}

void buttonISR(){
  read_buttons = true;
}

void sensorISR(){
  //Stuff to be added here
}

void button_reading(){
  read_buttons = false;
  unsigned long int button_time_temp = millis();
  if(button_time_temp - button_time < 10){//Prevents debouncing effect of buttons
    return;
  }
  button_time = button_time_temp;
  if(digitalRead(button_0in)){
    input_string = input_string+"0";
    Serial.print("0");
  }
  else if(digitalRead(button_1in)){
    input_string = input_string+"1";
    Serial.print("1");
  }
  else if(digitalRead(button_clr) && input_string!=""){
    if(!pwd_chng){
      input_string = "";
      Serial.println(" cleared");
    }
    else{
      password = input_string;
      pwd_chng = false;
    }
  }
  else delay(10);
}

void burglar_here() {
  Timer1.resume();
  while(true){
    if(seconds_passed >= 60){
      Serial.println("\nCops called");
      break;
    }
    if(read_buttons){
      button_reading();
    }
    if(input_string == password){
      Serial.println("\nAll safe, have a nice day");
      burglar = false;
      break;
    }
  }
  seconds_passed = 0;
  Timer1.stop();
}

void change_password(){
  Serial.println("Enter new password");
  pwd_chng = true;
  while(true){
    if(read_buttons){
      button_reading();
    }
    if(!pwd_chng){
      EEPROM.put(0,password);
      Serial.print("\nNew password: ");
      Serial.println(password);
      input_string = "";
      break;
    }
  }
}

void loop(){
  if(burglar){
    burglar_here();
    if(burglar){
      while(true){
        digitalWrite(buzzer, HIGH);
      }
    }
  }
  if(read_buttons){
    read_buttons = false;
    if(digitalRead(button_clr)){
      change_password();
    }
   burglar = true;//introduced for testing purposes
  }
}
