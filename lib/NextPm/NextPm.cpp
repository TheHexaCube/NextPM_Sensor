#include "Arduino.h"


#include "NextPm.h"
#include "printhex.h"



NextPm::NextPm() { //Use Hardware Serial
    Serial1.begin(115200, SERIAL_8E1);
}


void NextPm::sendRegister(){};

/* Modbus Format:
A0 C0 R0 R1 N0 N1 CRC16
A0:                     Adress of PM Next Module                        - 0x01
C0:                     Read  Command                                   - 0x03
                        Write Command                                   - 0x06
R0 R1:                  Target Register Address (16 Bit)
N0 N1:                  Number of Registers to Read (16 Bit)
CRC16:                  CRC16 Checksum
*/ 



void NextPm::readRegister(int16_t adress, uint8_t length){
    
    Serial.println(Serial1.readBytes(buffer, 32));
    

    if (Serial1) {
        uint16_t CRC = 0xFFFF;      


        byte payload[] = {0x01, 0x03, adress << 8, adress & 0xFF, 0x00, length, 0xFF, 0xFF};
        
       
        for (int i = 0; i < sizeof(payload)-2; i++) {
            

            // calculate CRC16 of payload and append to payload
            CRC ^= payload[i];

            for (int j = 0; j < 8; j++) {
                if( CRC & 0x0001 )
                {
                    CRC >>= 1;
                    CRC ^= 0xA001;
                }
                else
                {
                    CRC >>= 1;
                }
            }
        }
       
        payload[6] = CRC & 0xFF; // split 16-bit across two byte
        payload[7] = CRC >> 8;
        

        
        for (int i = 0; i < sizeof(payload); i++) {
            //printHex(payload[i], 2); // debug output
           
        }        
         Serial1.write(payload, sizeof(payload)); // send payload over Serial1 to sensor <---- no working!       
       
    }    
};


