//#include <SD.h>                      // need to include the SD library
//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
//#define SD_ChipSelectPin 10  //using digital pin 4 on arduino nano 328
//#include <TMRpcm.h>           //  also need to include this library...
//#include <SPI.h>
#include <EEPROM.h>
//TMRpcm tmrpcm;   // create an object for use in this sketch
char mychar;
//----------------------------------------------

int vala;
int valb;
int valc;
int vald;

int epp8=1;
int epp9=1;
int epp10=1;
int epp11=1;

int indikator;

String gabung(16);


int x;
int j=1;  
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
  
  x=0;



  
  gabung="";
  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  
  pinMode(7, INPUT);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
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

            //epp 1
            if (vala==HIGH && valb==HIGH && valc==HIGH && vald==LOW) {
                if(gabung=="8"){
                  epp8=1;
                  digitalWrite(8, LOW);
                }
                if(gabung=="9"){
                  
                  epp9=1;
                  digitalWrite(9, LOW);
                }
                if(gabung=="10"){
                  epp10=1;
                  digitalWrite(10, LOW);
                }
                if(gabung=="11"){
                  epp11=1;
                  digitalWrite(11, LOW);
                }
                
                gabung ="";
            }
            //epp 0
            if (vala==HIGH && valb==HIGH && valc==HIGH && vald==HIGH) {
                if(gabung=="8"){
                  digitalWrite(8, HIGH);
                  epp8=0;
                }
                if(gabung=="9"){
                  digitalWrite(9, HIGH);
                  epp9=0;
                }
                if(gabung=="10"){
                  digitalWrite(10, HIGH);
                  epp10=0;
                }
                if(gabung=="11"){
                  digitalWrite(11, HIGH);
                  epp11=0;
                }
                
                gabung ="";
            }
            if (vala==HIGH && valb==HIGH && valc==LOW && vald==HIGH) {
              
              if(gabung="1234"){
                  EEPROM.write(8, epp8);
                  EEPROM.write(9, epp9);
                  EEPROM.write(10, epp10);
                  EEPROM.write(11, epp11);
                  
                  Serial.println(epp8);
                  Serial.println(epp9);
                  Serial.println(epp10);
                  Serial.println(epp11);
                  
                  hidupsemua();
                  delay(200);
                  matisemua();  
                  delay(200);                
                  hidupsemua();
                  delay(200);
                  matisemua(); 
                  delay(200);                 
                  hidupsemua();
                  delay(200);
                  matisemua();
              }
              
              gabung="";
            }
            //* bintang enter
            if (vala==HIGH && valb==LOW && valc==HIGH && vald==HIGH) { 
              //Program eprom
              if(gabung=="9"){
                int i;
                if(x==3){x=0;}
                x=x+1;
                int no_pompa[]= {8,9,10,11};
                int pompa_hidup[]= {1,2,3,4}; 
                for(i = 0; i < sizeof(pompa_hidup); i ++){
                  if(i==x){
                    digitalWrite(no_pompa[x], LOW);
                    EEPROM.write(no_pompa[x], 1);
                    Serial.println(no_pompa[x]);
                    
                  }
                   
                }
               
              } 
              if(gabung=="5"){
                Serial.println(EEPROM.read(8));
                Serial.println(EEPROM.read(9));
                Serial.println(EEPROM.read(10));
                Serial.println(EEPROM.read(11));
              }
              if(gabung=="8"){
                
                  EEPROM.write(8, 0);
                  EEPROM.write(9, 0);
                  EEPROM.write(10, 0);
                  EEPROM.write(11, 0);
                
                  digitalWrite(8, HIGH);
                  digitalWrite(9, HIGH);
                  digitalWrite(10, HIGH);
                  digitalWrite(11, HIGH);
                  Serial.println("RESET EPROM");  
              }
               gabung="";              
            }
            
            
            
            if (vala==HIGH && valb==HIGH && valc==LOW && vald==LOW) { 
             
              //--------------------------------------------------------------------------------------------
              //gantian pompa
              
              //hidup
              if(gabung=="6"){
                
                int nn[4];
                int jml=0;
                if(EEPROM.read(8)==1){ nn[jml]=8; jml++; }
                if(EEPROM.read(9)==1){ nn[jml]=9; jml++;}
                if(EEPROM.read(10)==1){ nn[jml]=10; jml++;}
                if(EEPROM.read(11)==1){ nn[jml]=11; jml++;}
                int no_pompa[jml];
                
                int h;
                for(h = 0; h < jml; h ++){
                    no_pompa[h]=nn[h];
                }
                
                
                
                int i;
                int sizearr;
                int eppr; 
                
                sizearr=sizeof( no_pompa ) / sizeof( int );
               
                if(x==sizearr){x=0;}
                for(i = 0; i < sizearr; i ++){
                  if(i==x){
                      //Serial.println(i);
                      matisemua();
                      digitalWrite(no_pompa[x], LOW);
                  }
                   
                }
               x=x+1;
              }
              
              
              //mati
              if(gabung=="7"){
                matisemua();
               
              }
              
               
              //--------------------------------------------------------------------------------------------
              
              //pompa 1 hidup
              if(gabung=="11"){
                  digitalWrite(8, LOW);
                  Serial.println("pompa 1 hidup");
                }
                //pompa 1 mati
              if(gabung=="10"){
                  digitalWrite(8, HIGH);
                  Serial.println("POMPA 1 MATI");  
                } 
                
              //-----------------------------------------------------------------  
                
              //pompa 2 hidup
              if(gabung=="21"){
                  digitalWrite(9, LOW);
                  Serial.println("pompa 2 hidup");
                }
              //pompa 2 mati
              if(gabung=="20"){
                  digitalWrite(9, HIGH);
                  Serial.println("POMPA 2 MATI");  
                }
                
               //-----------------------------------------------------------------  
                
              //pompa 3 hidup
              if(gabung=="31"){
                  digitalWrite(10, LOW);
                  Serial.println("pompa 3 hidup");
                }
              //pompa 3 mati
              if(gabung=="30"){
                  digitalWrite(10, HIGH);
                  Serial.println("POMPA 3 MATI");  
                } 
                
                //----------------------------------------------------------------- 
                
              //pompa 4 hidup
              if(gabung=="41"){
                  digitalWrite(11, LOW);
                  Serial.println("pompa 4 hidup");
    
                }
              //pompa 4 mati
              if(gabung=="40"){
                  digitalWrite(11, HIGH);
                  Serial.println("POMPA 4 MATI");  
                } 
                
              //----------------------------------------------------------------- 
              
              //pompa hidup semua
              if(gabung=="1111"){
                  digitalWrite(8, LOW);
                  digitalWrite(9, LOW);
                  digitalWrite(10, LOW);
                  digitalWrite(11, LOW);
                  Serial.println("SEMUA pompa hidup");
    
                }
              //pompa 4 mati
              if(gabung=="0000"){
                  digitalWrite(8, HIGH);
                  digitalWrite(9, HIGH);
                  digitalWrite(10, HIGH);
                  digitalWrite(11, HIGH);
                  Serial.println("SEMUA POMPA MATI");  
                } 
                
              //----------------------------------------------------------------- 
              //reset arduino
              if(gabung=="88"){
                  
                  Serial.println("RESET"); 
                  asm volatile ("  jmp 0"); 
                } 

                gabung="";            
            }
            
      Serial.print(gabung);
      Serial.println();
      

    }

}
void matisemua(){
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
}


void hidupsemua(){
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
}
void readdtmf(){
  indikator = digitalRead(7);
  if(indikator==1){
      readdtmf();
  }
}
