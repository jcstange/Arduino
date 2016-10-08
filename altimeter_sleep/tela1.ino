void tela1() {
  int minuto;
  int segundo;
  display.clearDisplay(); 
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  if (estado==0) {
    display.print("STB ");
    minuto=(((millis() - desliga)/60000));
    segundo= ((millis() - desliga)/1000);
    display.print((minuto / 10)% 6);
    display.print(minuto % 10);
    display.print(":");
    display.print((segundo / 10)% 6);
    display.print(segundo % 10);
  }
  if (estado==6) {
    switch (mode) {
      case 0:
        display.print("PL: ");
        minuto=rt/60;
        segundo=rt;
        display.print((minuto / 10)% 6);
        display.print(minuto % 10);
        display.print(":");
        display.print((segundo / 10)% 6);
        display.print(segundo % 10);
        break;
      case 1: 
        display.print("FFL: ");
        minuto=fft/60;
        segundo=fft;
        display.print((minuto / 10)% 6);
        display.print(minuto % 10);
        display.print(":");
        display.print((segundo / 10)% 6);
        display.print(segundo % 10);
        break;
      case 2:
        display.print("NAV: ");
        minuto=navt/60;
        segundo=navt;
        display.print((minuto / 10)% 6);
        display.print(minuto % 10);
        display.print(":");
        display.print((segundo / 10)% 6);
        display.print(segundo % 10);
        break;
  }
  }
  display.setCursor(72,0);
  display.print(T,0); 
  //display.drawLine(0, 7, 84, 7, BLACK);//inix,iniy,finx,finy
  //display.drawLine(0, 39, 84, 39, BLACK);//inix,iniy,finx,finy
  
  if(f < 0) {
    display.setCursor(0,18);
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.print("-");
    f = -f;
  }
  if (f >= 3500) {
  display.setTextSize(3);
  display.setCursor(6,9);
  display.setTextColor(BLACK);
  display.print((f / 10000)%10);
  display.print((f / 1000)%10);
  display.print(".");
  display.print((f / 100)%10);
  display.setTextColor(BLACK);
  display.setTextSize(1);
  display.print("kft");
  }
  if (f < 3500 && f >= 0) {
  display.setTextSize(3);
  display.setTextColor(BLACK);
  display.setCursor(6,9);
  display.print((f / 1000)%10);
  display.print((f / 100)%10);
  display.print((f / 10)%10);
  display.setTextColor(BLACK);
  display.setTextSize(1);
  display.print(f % 10);
  display.print("ft");
  }
  if (mode==2) { 
  display.setCursor(0,30);
  display.print(sh);
  display.print(" : ");
  display.print(dh); 
  }
  if(v < 0) {
    display.setCursor(0,40);
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.print("-");
    v = -v;
  }
  display.setCursor(6,40);  
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.print((v/100)%10);
  display.print((v/10)%10);
  display.print(v%10);
  display.print(" ft/s");
  display.setCursor(65,40);
  if (batatraso>=254){
   bat = (readVcc()-3850)*0.2857;
   batatraso=0;
  }
  if (bat>100) display.print("C...");
  else display.print(bat);
  display.display();
  delay(150);
  batatraso++;
}
