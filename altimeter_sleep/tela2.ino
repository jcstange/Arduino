void tela2(byte conf) {
  display.clearDisplay(); 
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  if (conf==0)  display.setTextColor(WHITE, BLACK);
  display.println("CONFIG");
  display.setTextColor(BLACK);
  if (conf==1)  display.setTextColor(WHITE, BLACK);
  display.println("HISTORY");
  display.setTextColor(BLACK);
  if (conf==2)  display.setTextColor(WHITE, BLACK);
  display.println("ZERAR");
  display.setTextColor(BLACK);
  if (conf==3)  display.setTextColor(WHITE, BLACK);
  display.println("LIGHT");
  display.setTextColor(BLACK);
  display.display();
  delay(150);
}
