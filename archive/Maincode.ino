#include <Key.h>
#include <Keypad.h>
#include <EEPROM.h>
#include <TimerOne.h>


//Pin allocation
  const byte LCDpins[6] = {8,9,10,11,12,13};//LCD module for display
  const byte PIRpin = 2; //burglar sensor PIR read
  const byte Firepin = 3; //temperature sensor read
  const byte buzzerpin = 5; //write to buzzerpin to play sound
  const byte armpin = 7; //push button to arm the burglar functionality
  const byte TX = 1;//Serial comm or bluetooth
  const byte RX = 0;//Serial comm or bluetooth
  byte keypadcols[3] = {16,15,14};
  byte keypadrows[3] = {19,18,17};

//global constants
  const byte timerperiod = 60; //We will sound alarm after these many Seconds

//global volatile variables
  String entpwd = ""; //User entered string
  char lastchar = '\0'; //Last character entered by user, default is \0 i.e. no character
  String correctpwd = "";//Correct password
  int currentcount = 0;//Current count of countdown timer in seconds

//global state variables (also volatile, but all booleans)
  bool fire = false;
  bool burglar = false;
  bool armed = false;


//ISRs
  void PIRisr(){
    armed = false;
    burglar = true;
  }
  
  void TEMPisr(){
    fire = true;
  }
  
  void TIMERONEisr(){
    
  }
//buzzer functions
  void burglaralarm(){
     tone(buzzerpin,1000);
  }

  void firealarm(){
     tone(buzzerpin,700,500);
     delay(1000);
  }
//Password functions

//LCD functions

//Keyboard functions
  char keymatrix[3][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'*','0','#'}
  };
  Keypad keypad1 = Keypad( makeKeymap(keymatrix), keypadrows, keypadcols, 3, 3 );

  void clearstring(){
    entpwd = "";
  }

  void forceappend(char character){
    entpwd.concat(character);
  }

  void readKeypad(Keypad k){
  char key = k.getKey();
  if (lastchar=='\0'){
    switch(key){
      case '#':
        clearstring();
        break;
      case '*':
        //enterpassword();
        break;
//      case '\0': //Null character, no key was pressed
//        break; //do nothing 
      default:
        forceappend(key);
    }
  }
  lastchar = key;
}
//Setup
  void setup() {
    
  }
//Main loop
  void loop() {
    
  }
