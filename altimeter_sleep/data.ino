void data(){
  P = getPressure();
  a = pressure.altitude(P,baseline);
  a = a*3.28084;
  f = a;
  time = ((millis() - count));
  ve[0]=ve[1];
  ve[1]=ve[2];
  ve[2]=ve[3];
  ve[3]= ((1000*(b - a))/time);
  v = (ve[0]+ve[1]+ve[2]+ve[3])/4;
  b = a;
  count = millis();
}
