/*
  RF_Sniffer
 
  Hacked from http://code.google.com/p/rc-switch/
 
  by @justy to provide a handy RF code sniffer
*/
 
#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
RCSwitch mySwitch = RCSwitch();
int led=13;
void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on inerrupt 0 =&gt; that is pin #2
  pinMode(led, OUTPUT);
}
 
void loop() {
  if (mySwitch.available()) {
 
    int value = mySwitch.getReceivedValue();
 
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
      if(mySwitch.getReceivedValue()==181804){
        digitalWrite(led, HIGH);
      }
      
      if(mySwitch.getReceivedValue()==181805){
        digitalWrite(led, LOW);
      }
      
      Serial.print("Received ");
      Serial.print( mySwitch.getReceivedValue() );
      Serial.print(" / ");
      Serial.print( mySwitch.getReceivedBitlength() );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( mySwitch.getReceivedProtocol() );
    }
 
    mySwitch.resetAvailable();
 
  }
}
