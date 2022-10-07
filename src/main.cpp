#include <Arduino.h>
#include <NextPm.h>

NextPm pm;




void setup() {
  Serial.begin(115200); 
  delay(1000);
  Serial.println("Started");
  
  
  // put your setup code here, to run once:
}

void loop() {
  pm.readRegister(0x0001, 0x01);
  delay(350);
}