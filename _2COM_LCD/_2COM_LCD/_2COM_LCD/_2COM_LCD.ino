#include <LiquidCrystal.h>

#define TIME 500
#define BUZZER 6
#define RELAY 7

int volt;
float v0,a0;
long v;
long reading;
byte state;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() { 
    Serial.begin(9600);
    lcd.begin(16, 2);// screen (2,3,4,5,11,12)
    pinMode(BUZZER,OUTPUT);//buzzer
    pinMode(RELAY,OUTPUT);//relay
}

void loop() {

    if(millis()-reading>TIME){
    reading = millis();
    v=readVcc();
    a0= analogRead(A0);
    v0 = v*(a0/1023);
    volt = v0;
    if (volt == 0) state=5;
    if (volt>0 && volt<1100) state=0; //Normal Zone
    if (volt>1100 && volt<1600)state=1;//GSM - Wifi Zone
    if (volt>1600 && volt<2100)state=2;//Warning Zone!
    if (volt>2100 && volt<3100){//Warning Danger - Jammer detect
      state=3;
      digitalWrite(BUZZER,1);
      delay(200);
      } else if (volt<2100) digitalWrite(BUZZER,0);
     if (volt>3100 && volt<6000){//Warning!!! 100% jammer detect
      state=4;
      digitalWrite(RELAY,1);
      digitalWrite(BUZZER,1);
      delay(200);
      } else digitalWrite(RELAY,0);

switch (state) {
  case 0:
      lcd.clear();
      lcd.print("Normal Zone");
      lcd.setCursor(12,1);
      lcd.print(volt);
      lcd.display();
      delay(200);
      break;
  case 1:
      lcd.clear();
      lcd.print("GSM - Wifi Zone");
      lcd.setCursor(12,1);
      lcd.print(volt);
      lcd.display();
      delay(200);
      break;
  case 2:
      lcd.clear();
      lcd.print("Warning Zone!");
      lcd.setCursor(12,1);
      lcd.print(volt);
      lcd.display();
      delay(200);
    break;
  case 3:
     lcd.clear();
     lcd.print("Warning Danger -");
     lcd.setCursor(0,1);
     lcd.print("Jammer detect");
     lcd.setCursor(12,1);
     lcd.print(volt);
     lcd.display();
     break;
  case 4:
    lcd.clear();
    lcd.print("Warning!!!");
    lcd.setCursor(0,1);
    lcd.print("100% Jammer");
    lcd.setCursor(12,1);
    lcd.print(volt);
    lcd.display();
    break;   
   case 5:
    lcd.clear();
    lcd.print("Scanning...");
    lcd.display();
    break;    
}

    
    Serial.print(volt / 1000 % 10);
    Serial.print(volt / 100 % 10);
    Serial.print(volt / 10 % 10);
    Serial.println(volt % 10);
    }
//if (volt>0 && volt<500) {}
//
//if (volt>500 && volt<1000) {}
//
//
//if (volt>1000 && volt<1500) {}
//
//
//if (volt>1500 && volt<2000) {}
//
//
//if (volt>2000 && volt<2500) {}
//
//
//if (volt>2500 && volt<3000) {}
//
//
//if (volt>3000 && volt<3500) {}
//
//
//if (volt>3500 && volt<4000) {}
//
//
//if (volt>4000 && volt<4500) {}
//
//
//if (volt>4500 && volt<6000) {}

}




long readVcc() {
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
  #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
  #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif  
 
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring
 
  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
  uint8_t high = ADCH; // unlocks both
 
  long result = (high<<8) | low;
 
  result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
  return result; // Vcc in millivolts
}
