
long cont = 0;
boolean inicio = true;

void setup() {
  for (int i=2; i<=13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i,0);
  }

}

void loop() {
     
  
  
    for (int d=0;d<24; d++) {
      
      for (int c=0;c<60; c++) {

           if (inicio) {
            inicio = false;
            d=12;
            c=23;

          }
          cont = millis();
          while (millis() - cont < 60000) {
              // horas
              digit(1,1);
              num(d / 10% 10,1);
              delay(1);
              digit(1,0);
              num(d / 10% 10,0);
              digit(2,1);
              num(d%10 ,1);
              digitalWrite(11,0);
              delay(1);
              digit(2,0);
              num(d%10,0);
              digitalWrite(11,1);
              // minutos
              digit(3,1);
              num(c / 10 % 10,1);
              delay(1);
              digit(3,0);
              num(c / 10% 10,0);
              digit(4,1);
              num(c % 10,1);
              delay(1);
              digit(4,0);
              num(c % 10,0);
          
        }
      }
    }
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
