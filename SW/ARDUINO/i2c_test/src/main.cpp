#include <Arduino.h>
#include <Wire.h>

#define I2C_SDA 21
#define I2C_SCL 22

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_SDA, I2C_SCL); 
  Wire.setClock(100000);   
  Serial.println("\nI2C Scanner");  
  uint8_t error;
  int i;
  for(i=0;i<127;i++){
    Wire.beginTransmission(i);
    error = Wire.endTransmission();
    if(error){
      Serial.print(".");
    }
    else{
      delay(10);
      Serial.print("0x");
      Serial.println(i,HEX);
    }    
  }
}
void loop() {
}