    /* 
      Percobaan Arduino Sederhana : Menghidupkan LED Dengan Sensor Gerak di Arduino 
     */  
       
    int led = 13;                    // Pilih pin untuk lampu LED  
    int pir = 2;                     // Pilih pin untuk PIR Sensor  
    int pirState = LOW;              // Saat mulai, PIR menganggap tidak ada gerakan  
    int val = 0;                     // Variabel untuk membaca status PIR  
       
    void setup() {  
      pinMode(led, OUTPUT);          // Mendeklarasikan LED sebagai output  
      pinMode(pir, INPUT);           // Mendeklarasikan PIR sebagai input  
       
      Serial.begin(9600);  
    }  
       
    void loop(){  
      val = digitalRead(pir);         // Membaca input dari PIR  
      if (val == HIGH) {              // Mengecek apakah terdeteksi gerakan  
        digitalWrite(led, HIGH);      // Jika terdeteksi gerakan, LED akan menyala  
        if (pirState == LOW) {  
          Serial.println("Terdeteksi gerakan!");  // Menampilkan teks serial saat terdeteksi gerakan  
          pirState = HIGH;  
        }  
      } else {  
        digitalWrite(led, LOW);    // LED kembali dimatikan  
        if (pirState == HIGH){  
          Serial.println("Gerakan selesai");   // Menampilkan teks serial saat deteksi selesai  
          pirState = LOW;  
        }  
      }  
    }  
