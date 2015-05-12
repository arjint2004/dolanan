#include <SD.h>                      // need to include the SD library
//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SD_ChipSelectPin 10  //using digital pin 4 on arduino nano 328
#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>

TMRpcm tmrpcm;   // create an object for use in this sketch
char mychar;
//----------------------------------------------

int vala;
int valb;
int valc;
int vald;

int indikator;

String gabung(16);

void setup() {
  //------------------------------------------------------------------------------------------------------------
  //tmrpcm.speakerPin = 9; //11 on Mega, 9 on Uno, Nano, etc

  Serial.begin(115200);
  /*if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;   // don't do anything more if not
  }*/
  ///tmrpcm.play("REC006.wav"); //the sound file "music" will play each time the arduino powers up, or is reset
  ///Serial.println("REC006.wav");  
  //-----------------------------------------------------------------------------------------------------------
  
  
  gabung="";
  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  
  pinMode(7, INPUT);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);
}

void loop()
{
    indikator = digitalRead(7);
    
    if(indikator==1){
      readdtmf();
      
        vala = digitalRead(5);
        valb = digitalRead(4);
        valc = digitalRead(3);
        vald = digitalRead(2);

            if (vala==LOW && valb==LOW && valc==LOW && vald==HIGH) {
                gabung = gabung + "1";
            }

            if (vala==LOW && valb==LOW && valc==HIGH && vald==LOW) {
               gabung = gabung + "2";
            }

            if (vala==LOW && valb==LOW && valc==HIGH && vald==HIGH) {
                 gabung = gabung + "3";
            }

            if (vala==LOW && valb==HIGH && valc==LOW && vald==LOW) {
               gabung = gabung + "4";
            }
            
            if (vala==LOW && valb==HIGH && valc==LOW && vald==HIGH) {
               gabung = gabung + "5";
            }
      
            if (vala==LOW && valb==HIGH && valc==HIGH && vald==LOW) {
               gabung = gabung + "6";
            }
            if (vala==LOW && valb==HIGH && valc==HIGH && vald==HIGH) {
               gabung = gabung + "7";
            }
            if (vala==HIGH && valb==LOW && valc==LOW && vald==LOW) {
               gabung = gabung + "8";
            }
            if (vala==HIGH && valb==LOW && valc==LOW && vald==HIGH) {
               gabung = gabung + "9";
            }
            if (vala==HIGH && valb==LOW && valc==HIGH && vald==LOW) {
               gabung = gabung + "0";
            }
      
      
            if (vala==HIGH && valb==HIGH && valc==LOW && vald==LOW) {
                if(gabung=="111"){
                  //delay(1000);
                  digitalWrite(8, LOW);
                  //tmrpcm.play("REC006.wav");
                  Serial.println("pompa hidup");
                  //delay(15000);
                  //digitalWrite(8, LOW);
                }
                if(gabung=="000"){
                  digitalWrite(8, HIGH);
                  //tmrpcm.play("REC006.wav");
                  Serial.println("POMPA MATI");  
                }      
                gabung="";            
            }
            
      Serial.print(gabung);
      Serial.println();
      

    }

}

void readdtmf(){
  indikator = digitalRead(7);
  if(indikator==1){
      readdtmf();
  }
}
