#include <SimpleKalmanFilter.h>
#include <Wire.h>
#include "I2C.h"
#define RESTRICT_PITCH
SimpleKalmanFilter simpleKalmanFilter(1, 1, 0.001);
 
uint8_t i2cData[14]; // Buffer for I2C data
 
int16_t accX;
float accX_kalman;
 
void setup()
{
    Serial.begin(9600);
    Wire.begin();
#if ARDUINO >= 157
    Wire.setClock(400000UL); // Set I2C frequency to 400kHz
#else
    TWBR = ((F_CPU / 400000UL) - 16) / 2; // Set I2C frequency to 400kHz
#endif
 
    i2cData[0] = 7; // Set the sample rate to 1000Hz - 8kHz/(7+1) = 1000Hz
    i2cData[1] = 0x00; // Disable FSYNC and set 260 Hz Acc filtering, 256 Hz Gyro filtering, 8 KHz sampling
    i2cData[2] = 0x00; // Set Gyro Full Scale Range to ±250deg/s
    i2cData[3] = 0x03; // Set Accelerometer Full Scale Range to ±16g
    while (i2cWrite(0x19, i2cData, 4, false))
        ; // Write to all four registers at once
    while (i2cWrite2(0x6B, 0x01, true))
        ; // PLL with X axis gyroscope reference and disable sleep mode
}
void loop()
{
 
    while (i2cRead(0x3B, i2cData, 14)) {
        ;
    }
    accX = (int16_t)((i2cData[0] << 8) | i2cData[1]);
    accX_kalman = simpleKalmanFilter.updateEstimate((float)accX);
    Serial.print(accX);
    Serial.print(",");
    Serial.print(accX_kalman, 3);
    Serial.println();
}
