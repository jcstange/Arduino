#include <Wire.h>
long cont = 0;
int tempsensor = 0;
int tempwanted = 25;

void setup() {
  for (int i=2; i<=13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i,0);
  }
  pinMode (A0,INPUT);
  Serial.begin(9600);
   Wire.begin(); // Join I2C bus
}

void loop() {
  temp_sensor();
  if (digitalRead(6)==HIGH || digitalRead(7)==HIGH) {
    temp_wanted();
  }
 
    if (tempsensor<tempwanted) {
      digitalWrite(8,1);
      digitalWrite(9,1);
    } else { 
      digitalWrite(8,0);
      digitalWrite(9,0);
    }
  cont = millis();
  while (millis()-cont < 1000) {
  digit(1);
  num (tempsensor / 10 % 10, 1);
  delay(4);
  num(tempsensor / 10 % 10, 0);
  digit(2);
  num(tempsensor % 10, 1);
  delay(4);
  num(tempsensor % 10, 0);
  digit(3);
  num (tempwanted / 10 % 10, 1);
  delay(4);
  num(tempwanted / 10 % 10, 0);
  digit(4);
  num(tempwanted % 10, 1);
  delay(4);
  num(tempwanted % 10, 0);

  }
}
void temp_wanted() {

  if (digitalRead(7)== HIGH) {
      tempwanted++;
  }
    if (digitalRead(6) == HIGH) {
      tempwanted--;
   }
}
void temp_sensor() {
 
  for(int i=0; i<10; i++) {  
    if(i<9) {
      tempsensor = tempsensor+(analogRead(A0)*readVcc()/10230);
    } else { tempsensor= tempsensor/9; }
  }
}

long readVcc() {
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(1); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1126400L / result; // Back-calculate AVcc in mV
  return result;
}


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
