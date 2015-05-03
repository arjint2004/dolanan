// *******************************************************************************
//             CM8870 DTMF Decoder Using Arduino UNO
// Problem was decoder would repeat digits as long as a key was held 
// down. The "buttonState" code waits until key is released before 
// decoding and printing digits.  Note, will decode all 16 valid 
// DTMF digits including the letters A, B, C, and D. found on some 
// DTMF pads.  
// Also was used by the military for their "Autovon" phone system  
// but labeled as follows:
//     A (697/1633, FO): Flash Override
//     B (770/1633, F):  Flash
//     C (852/1633, I):  Immediate
//     D (941/1633, P):  Priority
// *******************************************************************************

// Include the library code:
#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 11, 9, 12, 10);

// Display wired as follows, pins out of order to to PCB trace layout
// Pin 1 = Gnd
// Pin 2 = + 5VDC
// Pin 3 = Contrast, OK to connect to Gnd as well
// Pin 4 = RS, connect to pin 2 of Arduino
// Pin 5 = R/W, OK to connect to Gnd as well
// Pin 6 = Enable, connect to pin 3 of Arduino
// Pin 11 = D4, connect to pin 11 of Arduino
// Pin 12 = D5, connect to pin 9 of Arduino
// Pin 13 = D6, connect to pin 12 of Arduino
// Pin 14 = D7, connect to pin 10 of Arduino

// Variables used
int dtmf;
int cntr;
int switchPin = 6;        // DTMF data valid if high from CM8870
int val;                  // Variable for reading the pin status
int buttonState;          // Variable to hold the last button state
String dial(16);	  // string to hold DTMF characters

void(* resetFunc) (void) = 0;   //Declare reset function @ address 0
void setup() {                  // used to clear display after 41 digits
Serial.begin(115200);
dial = "";
cntr = 0;

// CM8870 Outputs to Arduino inputs

pinMode(2, INPUT); // Significant bit 1, pin 11 on CM8870 
pinMode(3, INPUT); // Significant bit 2, pin 12 on CM8870
pinMode(4, INPUT); // Significant bit 4, pin 13 on CM8870
pinMode(5, INPUT); // Significant bit 8, pin 14 on CM8870

// CM8870 Data valid pin goes high when valid DTMF code is seen
buttonState = digitalRead(switchPin);   // read the initial state, pin 15 on CM8870

// set up the LCD's number of columns and rows and clear it
  lcd.begin(40,2);
  lcd.clear();

// Print the RESET Message
   lcd.setCursor(14, 0);       // Center Reset Message
   lcd.print("System Reset");
   delay(1000);
   lcd.clear();			
   lcd.setCursor(0,0);     // set cursor to column 0, row 0 
   lcd.print("Number of Digits Dialed = 0");
}

// Display data from DTMF decoder chip
// This part checks the DTMF output valid line and only 
// reads and prints it when the key is released. This 
// prevents it from printing multiple copies of same 
// digit while key on dial pad is held down.  

void loop() {
  val = digitalRead(switchPin);      // read input value and store it in val

  if (val != buttonState) {          // the input pin has changed
    if (val == LOW) {                // check if value is now high
      cntr++;                        // Increment digits dialed counter
  
// Decode CM8870 Data
dtmf = 0;
if (digitalRead(2) == HIGH) dtmf = dtmf + 1;
if (digitalRead(3) == HIGH) dtmf = dtmf + 2;
if (digitalRead(4) == HIGH) dtmf = dtmf + 4;
if (digitalRead(5) == HIGH) dtmf = dtmf + 8;

// Display Digits Dialed Counter with updated digit count
   lcd.setCursor(0,0);
   lcd.print("Number of Digits Dialed = ");
   lcd.print(cntr);
   
// Display DTMF Data
if (dtmf == 0) dial = dial + "D";
if (dtmf == 1) dial = dial + "1";
if (dtmf == 2) dial = dial + "2";
if (dtmf == 3) dial = dial + "3";
if (dtmf == 4) dial = dial + "4";
if (dtmf == 5) dial = dial + "5";
if (dtmf == 6) dial = dial + "6";
if (dtmf == 7) dial = dial + "7";
if (dtmf == 8) dial = dial + "8";
if (dtmf == 9) dial = dial + "9";
if (dtmf == 10) dial = dial + "0";
if (dtmf == 11) dial = dial + "*";
if (dtmf == 12) dial = dial + "#";
if (dtmf == 13) dial = dial + "A";
if (dtmf == 14) dial = dial + "B";
if (dtmf == 15) dial = dial + "C";

lcd.setCursor(0,1);  // Prints on 2nd row ist column
lcd.print(dial);     // The digit contained in DTMF data

Serial.print(dtmf);
Serial.println();

if (cntr > 40)  // Resets code back to 0 when 41st digit is dialed 
{
  resetFunc(); 
}
	}
		}   
 buttonState = val;  // Saves valid tone state input from CM8870 chip     
}

