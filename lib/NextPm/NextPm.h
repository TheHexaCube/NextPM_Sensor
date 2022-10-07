#ifndef NextPm_h
#define NextPm_h

#include <Arduino.h>
#include <SoftwareSerial.h>



/** Library to interface with the Tera NextPM Particle Sensor
 * 
 * Datasheet:           https://docs.rs-online.com/ab19/A700000006569693.pdf
 * User-Guide:          https://docs.rs-online.com/15b0/A700000006625602.pdf
 * Technical Note:      https://docs.rs-online.com/e64f/A700000006967547.pdf
 * 
 * Datum:               24.06.2022 
 * Autor:               *snip*
 * 
 * 
 *  
 **/




/**
 * @brief Class to interface with the Tera NextPM Particle Sensor
 * 
 */

class NextPm {

    public:
        /** @brief Constructor for HardwareSerial.
         *  @param SerialPort HardwareSerial Port to use.
         */
              

        NextPm(Stream *serialStream);       

        

        void writeRegister(uint16_t adress, uint16_t value);

        /** @brief Read a register from the NextPM Sensor
         *  @param adress Starting adress of the register(s) to read
         *  @param length Number of bytes to read
         *  
         */
        void readRegister(int16_t adress, uint8_t length);
    

    private:

        byte _buffer[32]; // Buffer for reading out Modbus Data
        Stream *_serialStream; // Hardware Serial Port to use
        uint16_t crc16(byte *payload, uint8_t length); 
    







};


#endif