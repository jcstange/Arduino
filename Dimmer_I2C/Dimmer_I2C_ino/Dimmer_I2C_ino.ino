
#include <Wire.h>

char m[] = {0,0,0,0};
byte Lamp1= 128;
long crosstime = 0;
byte lumen[] = {128, 100, 90, 80, 70, 60, 50, 40, 30, 20, 5};

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Wire.begin(0x4);
Wire.onReceive(receiveEvent);
pinMode(5, INPUT);
pinMode(6, OUTPUT);
}

void loop() {
  if(digitalRead(5)){
        zero_crosss_int();
  }
  if (m[0]=='#' && m[3]=='*'){
    Serial.println(m);
    char g[]={m[2]};
    Lamp1 = lumen[atoi(g)];
    m[0]=0;
    m[1]=0;
    m[2]=0;
    m[3]=0;
  }
    
}

void zero_crosss_int()
{
 long currentcycle = 0;
 crosstime = micros();                             
      while((micros() - crosstime) < 8100){ 
          currentcycle = micros() - crosstime;
          if (currentcycle > (Lamp1*63)) {
            digitalWrite(6,1);
            digitalWrite(6,0);
          }
      }
}

void receiveEvent(int howMany) {
  if (Wire.available()>0) {
    Serial.println("recebeu");
    m[0] = Wire.read();
    m[1] = Wire.read();
    m[2] = Wire.read();
    m[3] = Wire.read();
  }
}
        

