#include <avr/io.h>// Sleep and Interrupt libraries
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>

#include <Adafruit_GFX.h>//Screen libraries
#include <Adafruit_PCD8544.h>

#include <SFE_BMP180.h>//Pressure Sensor library
#include <SPI.h>
#include <Wire.h>

#include <EEPROM.h>//Memory library


Adafruit_PCD8544 display = Adafruit_PCD8544(8, 7, 6, 5, 4);

#define SPEAKER 2
#define BTNMENU 13
#define BTNUP 12
#define BTNDOWN 11
#define LIGHT 9
#define down 300

SFE_BMP180 pressure;
double baseline;// baseline pressure

float a = 0;
int f = 0;
int b = 0;
int v = 0;
int ve[] = {0,0,0,0};
int sh = 0;
int dh = 0;
double P,T;
boolean on = true;
long desliga = 0;
long time = 0;
long count = 0;
long countmenu = 0;
long fft = 0;
long rt = 0;
long navt = 0;
long m = 0;
long n = 0;
byte estado = 0;
byte atraso = 0;
byte  mode = 0;
byte conf = 0;
byte batatraso = 255;
byte bat = 0;
byte i = 0;
int ff1 = EEPROM.read(1020)*500;
int ff2 = EEPROM.read(1021)*500;
int nav1 = EEPROM.read(1022)*50;
int nav2 = EEPROM.read(1023)*50;
byte salto = EEPROM.read(1019);
char info;

void setup()   {
    
  Serial.begin(9600);
  pinMode(SPEAKER,OUTPUT);
  pinMode(LIGHT,OUTPUT);
  digitalWrite(SPEAKER,0);
  digitalWrite(LIGHT,0);
  pinMode(BTNMENU,INPUT_PULLUP);
  pinMode(BTNUP,INPUT_PULLUP);
  pinMode(BTNDOWN,INPUT_PULLUP);
  pressure.begin();
  baseline = getPressure();  
  delay(500);
  display.begin();
  display.setContrast(50);
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.display(); 
 
}


void loop() {
  PCICR &= ~(1 << PCIE1);    // set PCIE0 to enable PCMSK0 scan
  PCMSK1 &= ~(1 << PCINT8);  // set PCINT0 to trigger an interrupt on state change 
  sei();
  baseline = getPressure();
  delay(500); 
  desliga = millis();  
  while (1){
start:
  switch (estado) {
  case 0: //WAITING
    atraso++;
    delay(10);
    if (atraso>=20){
      data();
      tela1();
      atraso=0;
    }
    if ((millis() - desliga)/1000 > down){
      display.clearDisplay();
      display.setCursor(0,0);
      display.setTextSize(1);
      display.setTextColor(BLACK);
      display.print("");
      display.display();
      delay(100);
      sleepNow();
    }
    if (digitalRead(BTNMENU)==LOW) {
      estado = 1;
      delay(100);
    }
    if (a>=100){
      m = millis();
      n = 0;
      while (a>100 && millis()- m < 2000){
        n = millis() - m;
        data();
        tela1();
      }
      if (n>=1500){
        estado = 6;
        countmenu = millis()- n;
        digitalWrite(LIGHT,0);
    }
    goto start;
    break;
    
 case 1: //MENU
    countmenu = millis();
    desliga = millis();
    while (millis() - countmenu < 5000) {
      tela2(conf);
      if (digitalRead(BTNUP)==LOW) {
        if (conf==0)  conf = 3;
        else conf--;
        delay(100);
      }
       if (digitalRead(BTNDOWN)==LOW) {
         if (conf==3)  conf = 0; 
         else conf++;
         delay(100);
      }
      if (digitalRead(BTNMENU)==LOW) {
        estado = conf + 2;
        if (estado==3){
                 salto = EEPROM.read(1019);
                 rt= EEPROM.read(salto*5)*20; 
                 sh= EEPROM.read((salto*5)+1)*100;     
                 fft= EEPROM.read((salto*5)+2); 
                 dh= EEPROM.read((salto*5)+3)*100; 
                 navt= EEPROM.read((salto*5)+4)*10;
     }
        conf = 0;
        goto start;
      }
    }
    estado = 0;
    goto start;
    break;
    
 case 2: //CONFIG
   countmenu = millis();
    while (millis() - countmenu < 10000) {
    tela3(conf);
    if (conf==0){
      if (digitalRead(BTNUP)==LOW) {
        ff1 = ff1 + 500;
        delay(100);
      }
      if (digitalRead(BTNDOWN)==LOW) {
        ff1 = ff1 - 500;
        delay(100);
      }
    }
    if (conf==1){
       if (digitalRead(BTNUP)==LOW) {
        ff2 = ff2 + 500;
        delay(100);
      }
       if (digitalRead(BTNDOWN)==LOW) {
        ff2 = ff2 - 500;
        delay(100);
      }
    }  
    if (conf==2){
       if (digitalRead(BTNUP)==LOW) {
        nav1 = nav1 + 50;
        delay(100);
      }
      if (digitalRead(BTNDOWN)==LOW) {
        nav1 = nav1 - 50;
        delay(100);
      }
    }  
    if (conf==3){
       if (digitalRead(BTNUP)==LOW) {
        nav2 = nav2 + 50;
        delay(100);
      }
      if (digitalRead(BTNDOWN)==LOW) {
        nav2 = nav2 - 50;
        delay(100);
      }
    }  
    if (digitalRead(BTNMENU)==LOW) {
      conf++;
      if (conf>3) { 
        conf = 0; 
        estado = 0 ; 
        EEPROM.write(1020,ff1/500);
        EEPROM.write(1021,ff2/500);
        EEPROM.write(1022,nav1/50);
        EEPROM.write(1023,nav2/50);
        break; 
      }
     }
    }
    estado=0;
    goto start;
    break;
 case 3: //HISTORY
    tela4();
    if (digitalRead(BTNUP)==LOW) {
         salto++;
         rt= EEPROM.read(salto*5)*20; 
         sh= EEPROM.read((salto*5)+1)*100;     
         fft= EEPROM.read((salto*5)+2); 
         dh= EEPROM.read((salto*5)+3)*100; 
         navt= EEPROM.read((salto*5)+4)*10;
    }
        if (digitalRead(BTNDOWN)==LOW) {
         salto--;
         rt= EEPROM.read(salto*5)*20; 
         sh= EEPROM.read((salto*5)+1)*100;     
         fft= EEPROM.read((salto*5)+2); 
         dh= EEPROM.read((salto*5)+3)*100; 
         navt= EEPROM.read((salto*5)+4)*10;
    }
    if (digitalRead(BTNMENU)==LOW) {
       estado = 0;
       salto = EEPROM.read(1019); 
    }
    goto start;
    break;
    
 case 4: //ZERAR
    baseline = getPressure(); 
    display.clearDisplay(); 
    display.setCursor(20,20);
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.print("ZERADO");
    display.display();
    delay(2000);
    estado=0;
    goto start;
    break;
    
 case 5:
    digitalWrite(LIGHT,!digitalRead(LIGHT));
    estado=0;
    break;
    
 case 6:
 //tempo de subida
 //altura de saida
 //tempo de queda livre
 //altura de abertura
 //tempo de navegacao
  while(a>=30){
    desliga = millis();
    switch (mode) {
      case 0: //PLANE
         data();
         rt = ((millis() - countmenu)/1000);
         tela1();
         if(v>75) {
             m = millis();
             n=0;
             sh=a;
             while (v>75 && millis()- m < 2000){
                n=millis()-m;
                data();
                tela1();
            }
            if (n>=1500) {
               countmenu = millis() - n;
               mode = 1;
               digitalWrite(SPEAKER,0);
         }
         }
         goto start;
         break;
      
      case 1: //Freefly
         data();
         fft = (millis() - countmenu)/1000;
         tela1();
         if (a<ff1 && a>ff2) {
           digitalWrite(SPEAKER,!digitalRead(SPEAKER));
         }
         if (a<=ff2) digitalWrite(SPEAKER,1);
          if(v<=105 && v>=0) {
             m = millis();
             dh = a;
             n = 0;
             while (v<=105 && millis()- m < 2000){
                n=millis()-m;
                data();
                tela1();
            } 
            if (n>1500){  
               countmenu = millis() - n;
               mode = 2;
               digitalWrite(SPEAKER,0);
            }
          }
          goto start;
          break;
          
       case 2: //NAVIGATION 
         data();
         navt = (millis() - countmenu)/1000;
         tela1();
          if (a<nav1 && a>nav2) {
           i++;
           if (i>=200) {
           digitalWrite(SPEAKER,!digitalRead(SPEAKER));
           i = 0;
           }
         }
         if (a<=nav2) {
           digitalWrite(SPEAKER,1);
           i++;
           if (i>=20){
           digitalWrite(SPEAKER,!digitalRead(SPEAKER));
           i = 0;
           }   
         }
         break;    
    }
  }
    digitalWrite(LIGHT,1);
    salto++;
    if (rt>30){
    EEPROM.write(1019,salto);
    EEPROM.write((salto*5),(rt/20));
    EEPROM.write((salto*5)+1,(sh/100));
    EEPROM.write((salto*5)+2,fft);
    EEPROM.write((salto*5)+3,(dh/100));
    EEPROM.write((salto*5)+4,(navt/10));
    digitalWrite(SPEAKER,0);
    estado = 0;
    }
    goto start;
    break;   
  }  
 } 
}
}


ISR (PCINT8_vect) {
  sleep_disable();
}

void sleepNow(){
    PCICR |= (1 << PCIE1);    // set PCIE1 to enable PCMSK1 scan
    PCMSK1 |= (1 << PCINT8);  // set PCINT8 to trigger an interrupt on state change 
    sei();                    
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();

}












