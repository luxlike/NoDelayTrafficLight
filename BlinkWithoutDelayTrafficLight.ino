#include <TembooSSL.h>
#include <TembooYunShield.h>
#include <TembooMQTTEdgeDevice.h>
#include <Temboo.h>
#include <TembooMonitoring.h>
#include <TembooCoAPEdgeDevice.h>

/*
  Blink without Delay

  Turns on and off a light emitting diode (LED) connected to a digital pin,
  without using the delay() function. This means that other code can run at the
  same time without being interrupted by the LED code.

  The circuit:
  - Use the onboard LED.
  - Note: Most Arduinos have an on-board LED you can control. On the UNO, MEGA
    and ZERO it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN
    is set to the correct LED pin independent of which board is used.
    If you want to know what pin the on-board LED is connected to on your
    Arduino model, check the Technical Specs of your board at:
    https://www.arduino.cc/en/Main/Products

  created 2005
  by David A. Mellis
  modified 8 Feb 2010
  by Paul Stoffregen
  modified 11 Nov 2013
  by Scott Fitzgerald
  modified 9 Jan 2017
  by Arturo Guadalupi

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay

  ** No Delay Traffic Light Control **  
  Edited 2021/11/17
  by Steve Kim
   .
*/

// constants won't change. Used here to set a pin number:
const int ledPinG =  11;// the number of the LED pin
const int ledPinY =  12;// the number of the LED pin
const int ledPinR =  13;// the number of the LED pin

// Variables will change:
int ledStateG = LOW;             // ledState used to set the LED
int ledStateY = LOW;             // ledState used to set the LED
int ledStateR = LOW;             // ledState used to set the LED
int ledState = 0;


// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long intervalG = 5000;           // interval at which to blink (milliseconds)
const long intervalY = 2000;           // interval at which to blink (milliseconds)
const long intervalR = 5000;           // interval at which to blink (milliseconds)


void setup() {
  // set the digital pin as output:
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinY, OUTPUT);
  pinMode(ledPinR, OUTPUT);
  
  ledState = 1; // 1:G , 2:Y, 3:R

  Serial.begin(9600); // open the serial port at 9600 bps:
}

void ledGreen(unsigned long curr_time) {
    if (curr_time - previousMillis >= intervalG){
      if(previousMillis != 0){
        ledState = 2;
      }     
      previousMillis = curr_time;    
    }

    ledStateG = HIGH;
    ledStateY = LOW;
    ledStateR = LOW;
}

void ledYellow(unsigned long curr_time) {
    if (curr_time - previousMillis >= intervalY){
      if(previousMillis != 0){
        ledState = 3;
      }      
      previousMillis = curr_time;   
    }

    ledStateG = LOW;
    ledStateY = HIGH;
    ledStateR = LOW;
}

void ledRed(unsigned long curr_time) {
    if (curr_time - previousMillis >= intervalR){
      if(previousMillis != 0){
        ledState = 1;
      }
      previousMillis = curr_time;     
    }

    ledStateG = LOW;
    ledStateY = LOW;
    ledStateR = HIGH;
}


void loop() {
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();
  Serial.print("currentMillis:");
  Serial.println(currentMillis);  
  
  switch(ledState)
  {
      case 1:
            ledGreen(currentMillis);
            break;  
      case 2:
            ledYellow(currentMillis);
            break;
      case 3:
            ledRed(currentMillis);
            break;  
      default:
            break;      
    
  }

  Serial.print("ledState:");
  Serial.println(ledState);
  
  // set the LED with the ledState of the variable:
  digitalWrite(ledPinG, ledStateG);
  digitalWrite(ledPinY, ledStateY);
  digitalWrite(ledPinR, ledStateR);
}
