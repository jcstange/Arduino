void tela3(byte conf) {
  display.clearDisplay(); 
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.println("FF: ");
  display.print("ALM1: ");
  if (conf==0)  display.setTextColor(WHITE, BLACK);
  display.println(ff1);
  display.setTextColor(BLACK);
  display.print("ALM2: ");
  if (conf==1)  display.setTextColor(WHITE, BLACK);
  display.println(ff2);
  display.setTextColor(BLACK);
  display.println("NAV: ");
  display.print("ALM1: ");
   if (conf==2)  display.setTextColor(WHITE, BLACK);
  display.println(nav1);
  display.setTextColor(BLACK);
  display.print("ALM2: ");
  if (conf==3)  display.setTextColor(WHITE, BLACK);
  display.println(nav2);
  display.setTextColor(BLACK);  
  display.display();
  delay(150);
}
