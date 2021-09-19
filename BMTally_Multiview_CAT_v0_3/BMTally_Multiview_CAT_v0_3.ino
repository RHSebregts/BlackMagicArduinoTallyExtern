/* Blackmagic Design Multiview Tally generator.
 Made for PolyCast Productions
 V 0.3 - 07-03-2019

 For use with the Blackmagic 3G‑SDI Shield for Arduino.
 Generate tally to Multiview from a CAT based tally patch.
 Cat cable configuration: Orange/White = 1, Orange = 2, Green/White = 3, Green = 4, Brown = Ground.
 Each tallyPin is to be connected to the Arduino 5v with a 10k resistor.
 Connect the Arduino to the 4th input of the Multiview for tally.
 */


// Initializing Blackmagic Tally Protocol
 #include <BMDSDIControl.h>

const int                shieldAddress = 0x6E;
BMD_SDITallyControl_I2C sdiTallyControl(shieldAddress);

// Init for tally inputs over Cat cable
const int tallyPin1 = 2;     // the number of the pin connected to the incoming tallypin
const int tallyPin2 = 3;     // the number of the pin connected to the incoming tallypin
const int tallyPin3 = 4;     // the number of the pin connected to the incoming tallypin
const int tallyPin4 = 5;     // the number of the pin connected to the incoming tallypin
const int ledPin = 13;       // the number of the pin connected to the LED on the arduino

// Creating variables for reading the tally state
int readTally1 = digitalRead(tallyPin1);             // int for reading out the pin
int readTally2 = digitalRead(tallyPin2);             // int for reading out the pin
int readTally3 = digitalRead(tallyPin3);             // int for reading out the pin
int readTally4 = digitalRead(tallyPin4);             // int for reading out the pin

void setup() {
// The setup function runs once when you press reset or power the board
// BLACKMAGIC CONTROL 
  sdiTallyControl.begin();               // Initialize cameracontrol
  sdiTallyControl.setOverride(true);     // Turn on control overrides
// TALLYPIN SETUP
pinMode(tallyPin1, INPUT_PULLUP);                            // initialize the tally pin as an input
pinMode(tallyPin2, INPUT_PULLUP);                            // initialize the tally pin as an input
pinMode(tallyPin3, INPUT_PULLUP);                            // initialize the tally pin as an input
pinMode(tallyPin4, INPUT_PULLUP);                            // initialize the tally pin as an input
pinMode(13, OUTPUT);                                         // initialize digital pin 13 as an monitoring output
}

void loop() {
// sdiTallyControl.setCameraTally(INT CAMERANUMBER,BOOLEAN PROGRAM,BOOLEAN PREVIEW)
// if readTally is HIGH, it will give Program tally to corresponding multiview window. Multiple tallyPins can be HIGH at the same time.

  if (readTally1 == HIGH){
    sdiTallyControl.setCameraTally(1,true, false);
  }
  else {sdiTallyControl.setCameraTally(1,false, false);
  }
    if (readTally2 == HIGH){
    sdiTallyControl.setCameraTally(2,true, false);
  }
  else {sdiTallyControl.setCameraTally(2,false, false);
  }
   if (readTally3 == HIGH){
    sdiTallyControl.setCameraTally(3,true, false);
  }
  else {sdiTallyControl.setCameraTally(3,false, false);
  }
  if (readTally4 == HIGH){
    sdiTallyControl.setCameraTally(4,true, false);
  }
  else {sdiTallyControl.setCameraTally(4,false, false);
  }

}
