// COMP-10184 – Mohawk College 
// PIR Sensor Test Application 
// Turn on the blue LED with motion is detected.

// "StAuth10184-01: I Kevin Sar, 000390567 certify that this material is my original work. 
// No other person's work has been used without due acknowledgement. 
// I have not made my work available to anyone else."
 
#include <Arduino.h> 
 
// digital input pin definitions 
#define PIN_PIR D5 
#define PIN_BUTTON D6 
int ALARM_STATE = LOW;             
bool bALARM_STAYON = false;
bool bALARM_DISABLE = false;
int BUTTON_DELAY = 200;
int BLINK_DELAY = 125;
// ************************************************************* 
void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // configure the LED output 
  pinMode(LED_BUILTIN, OUTPUT); 
 
  // PIR sensor is an INPUT 
  pinMode(PIN_PIR, INPUT); 
 
  // Button is an INPUT 
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  digitalWrite(D4, HIGH);             // Starts with LED OFF
} 
 
// ************************************************************* 
void loop() { 
  bool bPIR;
  int iPB; 

  // COMPLETED STAGE 5
  // -If motion detected start blinking
  // -If user pushes button while blinking within the 10s disable alarm and no more detection
  // -If user pushes button when alarm is disabled, re-enable alarm
  // -If motion is detected start blinking again
  // -If user does not push button when blinking, leave solid light on after 10s
  // -User must now reset alarm.
  bPIR = digitalRead(PIN_PIR);    // read sensor value
  
  iPB = digitalRead(D6);          // read push button value
  
  if (bPIR == HIGH && !bALARM_DISABLE && !bALARM_STAYON) {             // check if the sensor is HIGH
    
    int counter = 0;
    while(counter < 40){  // 4 Blinks per second, for 10 seconds is 40 blinks
      iPB = digitalRead(D6);
      digitalWrite(D4, LOW);
      delay(BLINK_DELAY);
      digitalWrite(D4, HIGH);
      delay(BLINK_DELAY);
      if(iPB == 0){
        digitalWrite(D4, HIGH);
        ALARM_STATE = LOW;
        counter = 100;
        bALARM_DISABLE = true;                    //Disable Alarm
        //Serial.print("Pressed!");           //For Testing
        delay(BUTTON_DELAY);
        break;
      } else {
        counter++;
      }

      if (ALARM_STATE == LOW && counter == 40) {
     // Serial.println("Motion detected!");   //For Testing to see if Motion is detected
      ALARM_STATE = HIGH;                         //change the ALARM_STATE to HIGH
      bALARM_STAYON = true;
      }
    }
  }  else if(bALARM_STAYON){
    digitalWrite(D4, LOW);
  } else if(iPB == LOW && bALARM_DISABLE){
    Serial.println("Enabling Alarm");
    bALARM_DISABLE = false;                       //Enable Alarm
    delay(BUTTON_DELAY);
  }
} 