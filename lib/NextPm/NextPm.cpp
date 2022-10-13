#include "Arduino.h"


#include "NextPm.h"
#include "printhex.h"


NextPm::NextPm(Stream *serialStream) { //Use Hardware Serial
    _serialStream = serialStream;
};


void NextPm::writeReadRegister(uint16_t adress, uint16_t value){
    memset(_buffer, 0, sizeof(_buffer)); //clear buffer
    byte payload[] = {0x01, 0x17, adress >> 8, adress & 0xFF, 0x00, 0x01, adress >> 8, adress & 0xFF, 0x00, 0x01, 0x02, value >> 8, value & 0xFF, 0xFF, 0xFF};
    
    uint16_t CRC = crc16(payload, sizeof(payload));   

    payload[sizeof(payload)-2] = CRC & 0xFF; // split 16-bit across two byte
    payload[sizeof(payload)-1] = CRC >> 8;  
    

    Serial.print("Sending : ");

    for (int i = 0; i < sizeof(payload); i++){
        printHex(payload[i], 2);
    }
    Serial.println();
    _serialStream->write(payload, sizeof(payload)); 

    while(!_serialStream->available()){};
    
    

    Serial.print("Received: ");
    if(_serialStream->available()){        
        //printHex(_serialStream->read(), 2);
        _serialStream->readBytes(&_buffer[0], 3);
        _serialStream->readBytes(&_buffer[3], _buffer[2]+2);
    }
    
    for (int i = 0; i < _buffer[2]+5; i++){
        printHex(_buffer[i], 2);
    }
    Serial.println();
}


void NextPm::writeRegister(uint16_t adress, uint16_t value){

    // Write multiple registers: A1, C1, Start_adress, number_of_registers, number_of_bytes, data, CRC
    //in this case, just write a single register -> hardcode no of registers = 1, no of registers = 1
    memset(_buffer, 0, sizeof(_buffer)); //clear buffer
    byte payload[] = {0x01, 0x10, adress >> 8, adress & 0xFF, 0x00, 0x01, 0x02, value >> 8, value & 0xFF, 0xFF, 0xFF};
    
    uint16_t CRC = crc16(payload, sizeof(payload));   

    payload[sizeof(payload)-2] = CRC & 0xFF; // split 16-bit across two byte
    payload[sizeof(payload)-1] = CRC >> 8;  
    

    Serial.print("Sending : ");

    for (int i = 0; i < sizeof(payload); i++){
        printHex(payload[i], 2);
    }
    Serial.println();
    _serialStream->write(payload, sizeof(payload)); 

    while(!_serialStream->available()){};
    
    

    Serial.print("Received: ");
    if(_serialStream->available()){        
        //printHex(_serialStream->read(), 2);
        _serialStream->readBytes(&_buffer[0], 3);
        _serialStream->readBytes(&_buffer[3], _buffer[2]+2);
    }
    
    for (int i = 0; i < _buffer[2]+5; i++){
        printHex(_buffer[i], 2);
    }
    Serial.println();



};

/* Modbus Format:
A0 C0 R0 R1 N0 N1 CRC16
A0:                     Adress of PM Next Module                        - 0x01
C0:                     Read  Command                                   - 0x03
                        Write Command                                   - 0x06printhexS
R0 R1:                  Target Register Address (16 Bit)
N0 N1:                  Number of Registers to Read (16 Bit)
CRC16:                  CRC16 Checksum
*/ 

uint16_t NextPm::crc16(byte *payload, uint8_t length){
    uint16_t CRC = 0xFFFF;  

    for (int i = 0; i < length-2; i++) {            

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
        return CRC;
};

void NextPm::readRegister(int16_t adress, uint8_t length){ 

    byte payload[] = {0x01, 0x03, adress >> 8, adress & 0xFF, 0x00, length, 0xFF, 0xFF};
    
    uint16_t CRC = crc16(payload, sizeof(payload));   

    payload[6] = CRC & 0xFF; // split 16-bit across two byte
    payload[7] = CRC >> 8;  
    
    Serial.print("Sending : ");

    for (int i = 0; i < sizeof(payload); i++){
        printHex(payload[i], 2);
    }
    Serial.println();
    _serialStream->write(payload, sizeof(payload)); 

    while(!_serialStream->available()){};

    

    Serial.print("Received: ");
    if(_serialStream->available()){        
        //printHex(_serialStream->read(), 2);
        _serialStream->readBytes(&_buffer[0], 3);
        _serialStream->readBytes(&_buffer[3], _buffer[2]+2);
    }
    
    for (int i = 0; i < _buffer[2]+5; i++){
        printHex(_buffer[i], 2);
    }
    Serial.println();
    
};    


