#include <SD.h>                      // need to include the SD library
//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SD_ChipSelectPin 10  //using digital pin 4 on arduino nano 328
#include <TMRpcm.h>           //  also need to include this library...// library untuk play file wav dari sdcard
#include <SPI.h>			  

TMRpcm tmrpcm;   // create an object for use in this sketch // mengambil object dari library <TMRpcm.h> 
//char mychar;
//----------------------------------------------
// variable untuk menyimpan hasil decoder DTMF dari shield DTMF
int vala;
int valb;
int valc;
int vald;

//untuk penanda jika tone DTMF datang/masuk
int indikator;

//untuk menyimpan digit password dari DTMF max 16 char
String gabung(16);

//TONE************************** AREA tone factory
// DTMF (Dual Tone Multiple Frequency) Demonstration

// http://en.wikipedia.org/wiki/Dual-tone_multi-frequency

// To mix the output of the signals to output to a small speaker (i.e. 8 Ohms or higher),
// simply use 1K Ohm resistors from each output pin and tie them together at the speaker.
// Don't forget to connect the other side of the speaker to ground!

#include <Tone.h>

int ptt=8; // pin untuk mengaktifkan ptt pesawat 2meter / HT
int buttonPin = 0; // pin yang membaca keadaan radar switch / pelampung bak air
int pinCekAliranAir = 1; // pin untuk membaca keadaan aliran air dari pompa (sensor keadaan pompa hidup/mati)
int aliranAir; // variable untuk menampung data dari sensor aliran air pipa transmisi dari pompa
int radar; //variable untuk menampung data dari sensor pelampung/radar
boolean currentState = LOW; //stroage for current button state 
boolean lastState = LOW; //storage for last button state

Tone freq1;  // create an object for use in this sketch // mengambil object dari library <Tone.h>  untuk freq1
Tone freq2;	 // create an object for use in this sketch // mengambil object dari library <Tone.h>  untuk freq2

const int DTMF_freq1[] = { 1336, 1209, 1336, 1477, 1209, 1336, 1477, 1209, 1336, 1477, 1633 }; // tentukan frequensi DTMF 1
const int DTMF_freq2[] = {  941,  697,  697,  697,  770,  770,  770,  852,  852,  852, 941 }; // tentukan frequensi DTMF 1
//TONE**************************

void setup() {
  //------------------------------------------------------------------------------------------------------------
  tmrpcm.speakerPin = 9; //speaker output untuk mengeluarkan suara dari file WAV

  Serial.begin(115200); //membuka komunikasi serial dengan baudrate 115200
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;   // don't do anything more if not
  }

  
  
  gabung=""; // set vadiable kosong
  
  pinMode(2, INPUT); // buat pin 2 sebagai input
  pinMode(3, INPUT); // buat pin 3 sebagai input
  pinMode(4, INPUT); // buat pin 4 sebagai input
  pinMode(5, INPUT); // buat pin 5 sebagai input
  
  pinMode(7, INPUT);  // buat pin 7 sebagai input
  pinMode(8, OUTPUT);  // buat pin 7 sebagai output
  digitalWrite(8, HIGH); //membuat PIN 8 HIGH 
  digitalWrite(7, LOW);//membuat PIN 8 LOW 
  digitalWrite(buttonPin, LOW);
  digitalWrite(pinCekAliranAir, LOW);
  //TONE**************************
  pinMode(buttonPin, INPUT);//this time we will set the pin as INPUT
  pinMode(ptt, OUTPUT);
  freq1.begin(16); // set pin 16/ pin2 analog untuk output tone 1
  freq2.begin(17); // set pin 17/ pin3 analog untuk output tone 2
  //TONE**************************
}

void loop()
{
    indikator = digitalRead(7);// membaca keadaan pin 7
    
    if(indikator==1){ // jika indikator ==1 lakukan algoritma pengecekan DTMF yang masuk
      readdtmf(); // fungsi untuk membaca dtmf saat ada input masuk
      
        vala = digitalRead(5); // membaca pin
        valb = digitalRead(4);
        valc = digitalRead(3);
        vald = digitalRead(2);

            if (vala==LOW && valb==LOW && valc==LOW && vald==HIGH) { //jika vala==LOW && valb==LOW && valc==LOW && vald==HIGH maka tambahkan char 1 ke var gabung
                gabung = gabung + "1";
            }

            if (vala==LOW && valb==LOW && valc==HIGH && vald==LOW) { // dst
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
      
      
            if (vala==HIGH && valb==HIGH && valc==LOW && vald==LOW) { // cek jika dtmf di pencet char #
                if(gabung=="1"){ //jika char 1 lakukan berikut
                  //delay(600);
                  digitalWrite(ptt, LOW);// aktifkan ptt ht / transmit
                  delay(1000);
                  tmrpcm.play("10.wav");
                  Serial.println("10.wav");
                  delay(1000);
                  digitalWrite(ptt, HIGH);
                }
                if(gabung=="000000"){ //jika char 1 lakukan berikut
                  digitalWrite(ptt, HIGH);// deactive ptt ht / standby
                  tmrpcm.play("REC006.wav");
                  Serial.println("REC006.wav");  
                }      
                gabung="";            
            }
            
      Serial.print(gabung);
      Serial.println();
      

    }
    
    //TONE**************************
    ToneRadar(); // cek pelampung apakah penuh atau kosong. jika penuh otomatis akan mematikan pompa . jika kosong otomatis menghidupkan pompa
    //TONE**************************

    //warning
    warning(); // cek jika meluap/ kosong dan pompa tidak bisa diperinttah maka kirim warning ke ht operator
}

void readdtmf(){
  indikator = digitalRead(7);
  if(indikator==1){
      readdtmf();
  }
}

//TONE**************************************

void playDTMF(uint8_t number, long duration)
{
  freq2.play(DTMF_freq2[number], duration); //play tone
  freq1.play(DTMF_freq1[number], duration); //play tone
  
}
void warning()
{
  aliranAir=digitalRead(pinCekAliranAir); // baca sensor aliran air 
  radar = digitalRead(buttonPin); // baca sensor radar
 
  if(aliranAir==HIGH && radar==LOW){ // jika meluap maka matikan pompa
        //delay(600);
        digitalWrite(ptt, LOW);
        delay(1000);
        tmrpcm.play("9.wav");
        //Serial.println("9.wav");
        delay(1000);
        //digitalWrite(ptt, HIGH);
        //delay(1000);
        matikanPompa(); // memanggil fungsi matikan pompa
        delay(9000);
  }
  
  //cek jika kosong
  if(aliranAir==LOW && radar==HIGH){
        //delay(600);
        digitalWrite(ptt, LOW); 
        delay(1000);
        tmrpcm.play("5.wav");
        //Serial.println("5.wav");
        delay(1000);
        //digitalWrite(ptt, HIGH);
        //delay(1000);
        hidupkanPompa();  // memanggil fungsi hidupkan pompa
        delay(9000);
  }  
}
void hidupkanPompa()
{
        digitalWrite(ptt, LOW); // aktifkan ptt
        delay(800); // beri jeda 0.8 detik
        int i;
        uint8_t phone_number[] = { 1,1,1,10 }; // kirim kode dtmf 1 1 1 10
        tmrpcm.play("1.wav"); // putar file wav
        delay(1500); // beri jeda 1.5 detik
        for(i = 0; i < sizeof(phone_number); i ++)
        {
         // Serial.print(phone_number[i], 10);
          //Serial.print(' ');
		  
          playDTMF(phone_number[i], 900); // mainkan dtmf yang diatas 1 1 1 10
          delay(1000); // beri jeda 1 detik
        }
        delay(1500);
        digitalWrite(ptt, HIGH); //aktifkan ptt / kirim tone lewat ht
        // Serial.println();
        //delay(6000);      
        delay(1);//crude form of button debouncing  
}
void matikanPompa()
{
        digitalWrite(ptt, LOW);
        delay(800); 
        int i;
        uint8_t phone_number[] = { 0,0,0,10 };
        tmrpcm.play("2.wav");
        delay(1500);
        for(i = 0; i < sizeof(phone_number); i ++)
        {
          //Serial.print(phone_number[i], 10);
          //Serial.print(' ');
          playDTMF(phone_number[i], 900);
          delay(1000);
        }
        delay(1500);
		
        digitalWrite(ptt, HIGH);
        //Serial.println();
        //delay(6000);      
        delay(1);//crude form of button debouncing  
}
void ToneRadar()
{
    currentState = digitalRead(buttonPin); // baca keadaan radar
    if (currentState == HIGH && lastState == LOW){//jika radar on (HIGH) maka hidupkan pompa
        hidupkanPompa();
    } else if(currentState == LOW && lastState == HIGH){
        matikanPompa();
    }
    lastState = currentState;
}
//TONE**************************************
