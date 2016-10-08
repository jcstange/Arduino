#include <Wire.h>

void setup() {
//  for (int i=2; i<=13; i++) {
//    pinMode(i, OUTPUT);
//    digitalWrite(i,0);
//  }
  Serial.begin(9600);
   Wire.begin(); // Join I2C bus
  Serial.println("setup");
}

void loop() {
//for (byte m=32; m<34; m++) {  
 for (byte x=0; x<256;x++) {
    Serial.println(x);
    Wire.beginTransmission(32);
    Wire.write(x);
    Wire.endTransmission();

    delay(50);
 }
//    }
  }

  
  

void digit (int n, boolean on) {
  
  switch(n) {
    case (1):
      digitalWrite(9,on);
      break;
    case (2):
      digitalWrite(8,on);
      break;
    case (3):
      digitalWrite(7,on);
      break;
    case (4):
      digitalWrite(6,on);
      break;
  }
}
void num(int n, boolean on) {
    switch(n){
     case (0):
     
      digitalWrite(3,on);  
      digitalWrite(11,on);
      break;
     
      case (1):  
    
      digitalWrite(3,on);
      digitalWrite(4,on);
      digitalWrite(5,on);
      digitalWrite(11,on);
      digitalWrite(12,on);
      digitalWrite(13,on);
      break;
  
    case (2):
      digitalWrite(2,on);
      digitalWrite(5,on);
      digitalWrite(11,on);
      break;
 
    case (3):
    
      digitalWrite(5,on);
      digitalWrite(13,on);
      digitalWrite(11,on);
      break;
  
    case (4):
    
      digitalWrite(4,on);
      digitalWrite(12,on);
      digitalWrite(13,on);
      digitalWrite(11,on);
      break;
  
   case (5):
   
      digitalWrite(10,on);
      digitalWrite(13,on);
      digitalWrite(11,on);
      break;
  
   case (6):
   
      digitalWrite(10,on);
      digitalWrite(11,on);
      break;

  
   case (7):
   
       digitalWrite(3,on);
       digitalWrite(5,on);
       digitalWrite(11,on);
       digitalWrite(12,on);
       digitalWrite(13,on);
       break;
   
   case (8):
   
       digitalWrite(11,on);
       break;
   
   case (9):
   
       digitalWrite(13,on);
       digitalWrite(11,on);
       break;
  }
}
