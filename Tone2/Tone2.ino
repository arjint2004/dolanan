// DTMF (Dual Tone Multiple Frequency) Demonstration

// http://en.wikipedia.org/wiki/Dual-tone_multi-frequency

// To mix the output of the signals to output to a small speaker (i.e. 8 Ohms or higher),
// simply use 1K Ohm resistors from each output pin and tie them together at the speaker.
// Don't forget to connect the other side of the speaker to ground!

#include <Tone.h>

int ptt=13;
int buttonPin = 7;
boolean currentState = LOW;//stroage for current button state
boolean lastState = LOW;//storage for last button state

Tone freq1;
Tone freq2;

const int DTMF_freq1[] = { 1336, 1209, 1336, 1477, 1209, 1336, 1477, 1209, 1336, 1477, 1633 };
const int DTMF_freq2[] = {  941,  697,  697,  697,  770,  770,  770,  852,  852,  852, 941 };

void setup()
{
  pinMode(buttonPin, INPUT);//this time we will set the pin as INPUT
  pinMode(ptt, OUTPUT);
  Serial.begin(9600);
  freq1.begin(11);
  freq2.begin(12);
}

void playDTMF(uint8_t number, long duration)
{
  freq1.play(DTMF_freq1[number], duration);
  freq2.play(DTMF_freq2[number], duration);
}


void loop()
{
    currentState = digitalRead(buttonPin);
    if (currentState == HIGH && lastState == LOW){//if button has just been pressed
        digitalWrite(ptt, HIGH);
        delay(800); 
        int i;
        uint8_t phone_number[] = { 1,1,1,10 };
      
        for(i = 0; i < sizeof(phone_number); i ++)
        {
         // Serial.print(phone_number[i], 10);
          //Serial.print(' ');
          playDTMF(phone_number[i], 900);
          delay(1000);
        }
        delay(1500);
        digitalWrite(ptt, LOW);
       // Serial.println();
        //delay(6000);      
      delay(1);//crude form of button debouncing
    } else if(currentState == LOW && lastState == HIGH){
        digitalWrite(ptt, HIGH);
        delay(800); 
        int i;
        uint8_t phone_number[] = { 0,0,0,10 };
      
        for(i = 0; i < sizeof(phone_number); i ++)
        {
          //Serial.print(phone_number[i], 10);
          //Serial.print(' ');
          playDTMF(phone_number[i], 900);
          delay(1000);
        }
        delay(1500);
        digitalWrite(ptt, LOW);
        //Serial.println();
        //delay(6000);      
      delay(1);//crude form of button debouncing
    }
    lastState = currentState;
}

