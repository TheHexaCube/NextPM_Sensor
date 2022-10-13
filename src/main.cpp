#include <Arduino.h>
#include <NextPm.h>
#include <SparkFun_SGP30_Arduino_Library.h>
#include <Wire.h>

NextPm pm(&Serial1);

SGP30 sgp;

long t1, t2;
uint16_t sgp30_interval = 1000;


void setup() {
  Serial.begin(115200); 
  Serial1.begin(115200, SERIAL_8E1);

  Wire.begin();

  if (!sgp.begin()){
    Serial.println("SGP30 Sensor not found; check connections.");
    while(1);
  }

  sgp.initAirQuality();
  t1 = millis();


  pm.writeRegister(100, 5500); // default value?
  delay(1000);

  // put your setup code here, to run once:
}

void loop() {

  /* t2 = millis();

  if (t2 >= t1 + sgp30_interval){
    t1 = t2;
    
    
    sgp.measureAirQuality();
    Serial.print("CO2: ");
    Serial.print(sgp.CO2);
    Serial.print(" ppm\tTVOC: ");
    Serial.print(sgp.TVOC);
    Serial.println(" ppb");
    //get raw values for H2 and Ethanol
    sgp.measureRawSignals();
    Serial.print("Raw H2: ");
    Serial.print(sgp.H2);
    Serial.print(" \tRaw Ethanol: ");
    Serial.println(sgp.ethanol);
  } */


 pm.writeReadRegister(19, 0x0001);
 Serial.println("------------------");
 delay(2000);



 pm.writeReadRegister(19, 0x0000);
 Serial.println("------------------");
 delay(2000);

 


pm.readRegister(102, 1); // default 0x131 -> 305
Serial.println("------------------");
delay(2000);

pm.writeReadRegister(102, 100);
Serial.println("------------------");
delay(2000);




  

  
}