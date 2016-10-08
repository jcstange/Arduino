#include <Wire.h>

char m[] = {0,0,0,0};
int pulsador[] = {10, 11, 12, 13};

void setup() {
 Serial.begin(9600);
 Wire.begin(0x5); 
 for (int i=0; i < (sizeof(pulsador)/sizeof (int)); i++) {
   pinMode(pulsador[i], INPUT_PULLUP);
 }
}

void loop () {
  if (Serial.available()>0) {
  Serial.println(Serial.available());
  char c = Serial.read();
  Serial.println(c);
  m[0] = m[1];
  m[1] = m[2];
  m[2] = m[3];
  m[3] = c;
  if (m[0]=='#' && m[3]=='*'){
    Transmission(m);
    m[0] = 0;
    m[1] = 0;
    m[2] = 0;
    m[3] = 0;
    }
  }
}

