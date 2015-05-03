/*int a = 2;
int b = 3;
int c = 4;
int d = 5;*/

int vala;
int valb;
int valc;
int vald;

int led=13;

String vrify1(1);
String vrify2(1);
String vrify3(1);
String vrify4(1);
String vrify5(1);
String vrify6(1);
String vrify7(1);
String vrify8(1);
String vrify9(1);
String vrify0(1);

String gabung(16);

void setup() {                  // used to clear display after 41 digits
  Serial.begin(115200);
  gabung="";
  vrify1 ="";
  vrify2 ="";
  vrify3 ="";
  vrify4 ="";
  vrify5 ="";
  vrify6 ="";
  vrify7 ="";
  vrify8 ="";
  vrify9 ="";
  vrify0 ="";
  pinMode(led, OUTPUT);// sets the digital pin 13 as output
  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  digitalWrite(led, LOW);
}

void loop()
{
  
  vala = digitalRead(2);
  valb = digitalRead(3);
  valc = digitalRead(4);
  vald = digitalRead(5);
  /*vrify1 ="";
  vrify2 ="";
  vrify3 ="";
  vrify4 ="";
  vrify5 ="";
  vrify6 ="";
  vrify7 ="";
  vrify8 ="";
  vrify9 ="";
  vrify0 ="";
    if(vrify1==""){
      if (vala==LOW && valb==LOW && valc==LOW && vald==HIGH) {
          vrify1 = "1";
          gabung = gabung + "1";
      }
    }
    
    if(vrify2==""){
      if (vala==LOW && valb==LOW && valc==HIGH && vald==LOW) {
         vrify2 = "2";
         gabung = gabung + "2";
      }
    }
    
    if(vrify3==""){
      if (vala==LOW && valb==LOW && valc==HIGH && vald==HIGH) {
         vrify3 = "3";
         gabung = gabung + "3";
      }
    }
    if(vrify4==""){
      if (vala==LOW && valb==HIGH && valc==LOW && vald==LOW) {
         vrify4 = "4";
         gabung = gabung + "4";
      }
    }
    if(vrify5==""){
      if (vala==LOW && valb==HIGH && valc==LOW && vald==HIGH) {
         vrify5 = "5";
         gabung = gabung + "5";
      }
    }
    if(vrify6==""){
      if (vala==LOW && valb==HIGH && valc==HIGH && vald==LOW) {
         vrify6 = "6";
         gabung = gabung + "6";
      }
    }
    if(vrify7==""){
      if (vala==LOW && valb==HIGH && valc==HIGH && vald==HIGH) {
         vrify7 = "7";
         gabung = gabung + "7";
      }
    }
    if(vrify8==""){
      if (vala==HIGH && valb==LOW && valc==LOW && vald==LOW) {
         vrify8 = "8";
         gabung = gabung + "8";
      }
    }
    if(vrify9==""){
      if (vala==HIGH && valb==LOW && valc==LOW && vald==HIGH) {
         vrify9 = "9";
         gabung = gabung + "9";
      }
    }
    if(vrify0==""){
      if (vala==HIGH && valb==LOW && valc==HIGH && vald==LOW) {
         vrify0 = "0";
         gabung = gabung + "0";
      }
    }*/
    
	//gabung = vrify1+vrify2+vrify3+vrify4+vrify5+vrify6+vrify7+vrify8+vrify9+vrify0;
	//gabung = vrify1 + vrify2;
  
	//if(gabung=="13"){
		//Serial.print(gabung);
		//Serial.println();
               // digitalWrite(led, HIGH);
	//}

	if (vala==LOW && valb==LOW && valc==LOW && vald==HIGH){
		//Serial.print(gabung);
		//Serial.println();
                digitalWrite(led, HIGH);
	}

	if (vala==HIGH && valb==LOW && valc==HIGH && vald==LOW){
		//Serial.print(gabung);
		//Serial.println();
                digitalWrite(led, LOW);
	}
    //delay(50);
  //digitalWrite(13, 1);    // sets the LED to the button's value
}
