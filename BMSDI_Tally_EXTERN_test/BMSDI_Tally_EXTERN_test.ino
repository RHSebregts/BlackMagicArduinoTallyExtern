/*
  External tally trigger for Blackmagic Design Studio Viewfinder.
  Trigger sdiTallyControl through external tally.
  Connect tally wire to pin 2 and gnd.
  If tally is recieved, tally will be generated for Camera 1.
  The LED conencted to Digital pin 13 will also light up upon recieving tally. 
*/

#include <BMDSDIControl.h>                                // need to include the library

const int                shieldAddress = 0x6E;
BMD_SDICameraControl_I2C sdiCameraControl(shieldAddress);        // define the Tally object using I2C using the default shield address

// Declaring constants and bytes for interfacing
const byte connected  = 1 << 0;           // 1 shifted left 0 times, equivalent to 1 in decimal
const byte preview    = 1 << 1;           // 1 shifted left 1 times, equivalent to 2 in decimal
const byte program    = 1 << 2;           // 1 shifted left 2 times, equivalent to 4 in decimal
int tallyState;         // variable for reading the external tally status
int incomingTally;      // variable for storing incoming information over serialbus
byte newTally[3] = {program, preview, 0};
//END SETUP FOR BLACKMAGIC PROTOCOL

// Constants assigning pin numbers for tally and LED:

const int tallyPin = 2;     // the number of the pin connected to the incoming tallypin
const int ledPin = 13;      // the number of the pin connected to the LED on the arduino


// the setup function runs once when you press reset or power the board
void setup()
{
  // BLACKMAGIC CONTROL 
sdiCameraControl.begin();               // Initialize cameracontrol
sdiCameraControl.setOverride(true);     // Turn on control overrides

  pinMode(tallyPin, INPUT_PULLUP);                            // initialize the tally pin as an input:
  pinMode(13, OUTPUT);                                     // initialize digital pin 13 as an output
}

// the loop function runs over and over again forever
void loop()
{
  // read the state of the pushbutton value:
  tallyState = digitalRead(tallyPin);
  if (tallyState == LOW) {
    // turn LED on:
      digitalWrite(ledPin, HIGH);
  // BLACKMAGIC SEND TALLY PROGRAM
  sdiCameraControl.writeCommandInt8(
      2,                                  // Destination:    doesn't care any number between 1 and 99
      9,                                  // Category:       Switcher Status
      6,                                  // Param:          Tally
      0,                                  // Operation:      Absolute
      newTally[0]                         // Tally Status    Program -> Preview -> OFF
    );
    }
  else {
  // turn LED off
  digitalWrite(ledPin, LOW);
 // BLACKMAGIC SEND TALLY PROGRAM
  sdiCameraControl.writeCommandInt8(2,9,6,0, newTally[2]);
    }
   
  }

 
