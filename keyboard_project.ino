#include "Keypad.h"
String entered = "";

const int rows = 3;
const int cols = 3;
char keymatrix[rows][cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'*','0','#'}
};
byte rowPins[rows] = {19,18,17}; //A0,A1,A2 as digital IO
byte colPins[cols] = {16,15,14}; //A3,A4,A5 as digital IO
Keypad keypad1 = Keypad( makeKeymap(keymatrix), rowPins, colPins, rows, cols ); 

void clearstring(){
  entered = "";
}

void enterpassword(){
  //I suppose Mahadevan has already implemented this
}

void forceappend(char character){
  entered.concat(character);
}

void tryappend(char character){
  if (character != entered[entered.length()-1]){
    entered.concat(character);
  }
}

void readKeypad(Keypad k){
  char key = k.getKey();
  switch(key){
    case '#':
      clearstring();
      break;
    case '*':
      enterpassword();
      break;
    case '\0': //Null character, no key was pressed
      break; //do nothing 
    default:
      tryappend(key);
  }
}

void setup() {
  Serial.begin(9600);  
}

void loop() {
  // put your main code here, to run repeatedly:
  readKeypad(keypad1);
  Serial.println(entered);
}
