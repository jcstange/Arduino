#include <Wire.h>
long cont = 0;
boolean inicio = true;

void setup() {
  for (int i=2; i<=13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i,0);
  }

   Wire.begin(); // Join I2C bus
  Serial.println("setup");
}

void loop() {
 for (int d=0;d<24; d++) {
      
      for (int c=0;c<60; c++) {

           if (inicio) {
            inicio = false;
            d=1;
            c=8;

          }
          cont = millis();
          while (millis() - cont < 60000) {
              // horas
              digit(1);
              num(d / 10% 10,1);
              delay(1);
              digit(0);
              num(d / 10% 10,0);
              digit(2);
              num(d%10 ,1);
              digitalWrite(11,0);
              delay(1);
              digit(0);
              num(d%10,0);
              digitalWrite(11,1);
              // minutos
              digit(3);
              num(c / 10 % 10,1);
              delay(1);
              digit(0);
              num(c / 10% 10,0);
              digit(4);
              num(c % 10,1);
              delay(1);
              digit(0);
              num(c % 10,0);
          
        }
      }
    }


  }
//  
void digit (int n) {
  
  switch(n) {
    case (0):
      Wire.beginTransmission(56);
      Wire.write(B00000000);
      Wire.endTransmission();
      break;
    case (1):
      Wire.beginTransmission(56);
      Wire.write(B00000001);
      Wire.endTransmission();
      break;
    case (2):
      Wire.beginTransmission(56);
      Wire.write(B00000010);
      Wire.endTransmission();
      break;
    case (3):
      Wire.beginTransmission(56);
      Wire.write(B00000100);
      Wire.endTransmission();
      break;
    case (4):
      Wire.beginTransmission(56);
      Wire.write(B00001000);
      Wire.endTransmission();
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
