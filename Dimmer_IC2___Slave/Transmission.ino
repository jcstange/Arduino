void Transmission(char* t) {
    
    Wire.beginTransmission(0x4);
    
    Wire.write(t);
    
    Wire.endTransmission();
}
