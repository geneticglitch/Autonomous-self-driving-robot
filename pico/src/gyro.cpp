#include <Arduino.h>
#include "MPU6050_6Axis_MotionApps20.h"
#include "I2Cdev.h"
// MPU6050 variables
MPU6050 mpu;
bool dmpReady = false;
uint16_t packetSize;
uint16_t fifoCount;
uint8_t fifoBuffer[64];
Quaternion q;
VectorFloat gravity;
float ypr[3];
int16_t gyro[3];
const int INTERRUPT_PIN = 2;
volatile bool mpuInterrupt = false;

void dmpDataReady()
{
    mpuInterrupt = true;
}

void gyro_setup()
{
    Wire.begin();
    Wire.setClock(400000);
    mpu.initialize();
    mpu.dmpInitialize();
    mpu.setXAccelOffset(-3699);
    mpu.setYAccelOffset(-2519);
    mpu.setZAccelOffset(1391);
    mpu.setXGyroOffset(-156);
    mpu.setYGyroOffset(-11);
    mpu.setZGyroOffset(-14);
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);
    mpu.setDLPFMode(MPU6050_DLPF_BW_42);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
    mpu.setDMPEnabled(true);
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
    
}

bool gyro_ready()
{
    if (!dmpReady)
    {
        return false;
    }

    if (mpuInterrupt && mpu.dmpGetCurrentFIFOPacket(fifoBuffer))
    {
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
        mpu.dmpGetGyro(gyro, fifoBuffer);
        return true;
    }
    else
    {
        return false;
    }
}

float get_angle(bool skew)
{
    float angle = ypr[0] * 180 / M_PI;
    if(skew){
        if(angle<0){
            return 360 + angle;
        }
    }
    return angle;
}

float get_angular_velocity()
{
    return gyro[2];
}