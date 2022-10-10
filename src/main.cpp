#include <Arduino.h>
#include <NextPm.h>

NextPm pm(&Serial1);



void setup() {
  Serial.begin(115200); 
  Serial1.begin(115200, SERIAL_8E1);



  delay(1000);



  

  

  
  
  // put your setup code here, to run once:
}

void loop() {

  pm.readRegister(89, 1);
  delay(2500);

  pm.writeRegister(89, 50);
  //pm.writeRegister(0x0065, 0x0000);
  delay(5000);

  pm.writeRegister(89, 290); // default value?
  //pm.writeRegister(0x0065, 0x2710);
  delay(5000);
  // put your main code here, to run repeatedly:

  
}