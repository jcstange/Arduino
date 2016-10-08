#include <Wire.h>
#include <LiquidCrystal.h>


#define TIME 100
#define BUZZER 9
#define RELAY 8
#define LED9 10
#define LED10 11

int volt;
float v0,a0;
long v;
long reading;
byte state, x;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() { 
    Serial.begin(9600);
    pinMode(LED9,OUTPUT);
    pinMode(LED10,OUTPUT);
    x=B11111111;
    digitalWrite(LED9,1);
    digitalWrite(LED10,1);
    Wire.begin();
    PFC8574();
    lcd.begin(16,2);
    pinMode(BUZZER,OUTPUT);//buzzer
    pinMode(RELAY,OUTPUT);//relay
    digitalWrite(13,0);
}

void loop() {

    if(millis()-reading>TIME){
    reading = millis();
    v=readVcc();
    a0= analogRead(A0);
    v0 = v*(a0/1023);
    volt = v0;
    if (volt>=0 && volt<834) state=4; //Scanning...
    if (volt>833 && volt<837)state=0;//Normal Zone
    if (volt>836 && volt<851)state=1;//GSM - Wifi Zone
    if (volt>850 && volt<951){// Danger Zone!
      state=2;
      digitalWrite(BUZZER,1);
      delay(200);
      } else if (volt<850) digitalWrite(BUZZER,0);
     if (volt>950 && volt<6000){//100% jammer detect
      state=3;
      digitalWrite(RELAY,1);
      digitalWrite(BUZZER,1);
      delay(200);
      } else digitalWrite(RELAY,0);

switch (state) {
  case 0:
      lcd.clear();
      lcd.print("Normal Zone");
      lcd.setCursor(12,1);
      lcd.print(volt / 1000 % 10);
      lcd.print(volt / 100 % 10);
      lcd.print(volt / 10 % 10);
      lcd.print(volt % 10);
      lcd.display();
      delay(200);
      break;
  case 1:
      lcd.clear();
      lcd.print("GSM & Wifi Zone");
      lcd.setCursor(12,1);
      lcd.print(volt / 1000 % 10);
      lcd.print(volt / 100 % 10);
      lcd.print(volt / 10 % 10);
      lcd.print(volt % 10);
      lcd.display();
      delay(200);
      break;
  case 2:
      lcd.clear();
      lcd.print("Danger Zone");
      lcd.setCursor(12,1);
      lcd.print(volt / 1000 % 10);
      lcd.print(volt / 100 % 10);
      lcd.print(volt / 10 % 10);
      lcd.print(volt % 10);
      lcd.display();
      delay(200);
    break;
  case 3:
    lcd.clear();
    lcd.print("100% Jammer");
    lcd.setCursor(0,1);
    lcd.print("detected");
    lcd.setCursor(12,1);
    lcd.print(volt / 1000 % 10);
    lcd.print(volt / 100 % 10);
    lcd.print(volt / 10 % 10);
    lcd.print(volt % 10);
    lcd.display();
    break;   
   case 4:
    lcd.clear();
    lcd.print("Scanning...");
    lcd.display();
    break;    
}
//    Serial.print(volt / 1000 % 10);
//    Serial.print(volt / 100 % 10);
//    Serial.print(volt / 10 % 10);
//    Serial.println(volt % 10);
    }

if (volt==0)              {x=B11111111;PFC8574();digitalWrite(LED9,1);digitalWrite(LED10,1);}
if (volt>829 && volt<843) {x=B00000000;PFC8574();digitalWrite(LED9,1);digitalWrite(LED10,0);}
if (volt>842 && volt<855) {x=B11111111;PFC8574();digitalWrite(LED9,0);digitalWrite(LED10,0);}
if (volt>854 && volt<867) {x=B01111111;PFC8574();digitalWrite(LED9,0);digitalWrite(LED10,0);}
if (volt>866 && volt<879) {x=B00111111;PFC8574();digitalWrite(LED9,0);digitalWrite(LED10,0);}
if (volt>878 && volt<891) {x=B00011111;PFC8574();digitalWrite(LED9,0);digitalWrite(LED10,0);}
if (volt>890 && volt<903) {x=B00001111;PFC8574();digitalWrite(LED9,0);digitalWrite(LED10,0);}
if (volt>902 && volt<915) {x=B00000111;PFC8574();digitalWrite(LED9,0);digitalWrite(LED10,0);}
if (volt>914 && volt<927) {x=B00000011;PFC8574();digitalWrite(LED9,0);digitalWrite(LED10,0);}
if (volt>926 && volt<939) {x=B00000001;PFC8574();digitalWrite(LED9,0);digitalWrite(LED10,0);}
if (volt>938 && volt<6000){x=B00000000;PFC8574();digitalWrite(LED9,0);digitalWrite(LED10,0);}

}

void PFC8574(){
  Wire.beginTransmission(32); // transmit to device #8
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting
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
