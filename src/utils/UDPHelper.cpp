#include "utils/UDPHelper.hpp"
#include <cstring>

uint32_t readID(char* buf)
{
    uint32_t retVal = 0;
    memcpy(&retVal, &buf[ID_IDX], sizeof(retVal));
    return retVal;
}

float readLeftMotor(char* buf)
{
    float retVal = 0;
    memcpy(&retVal, &buf[LEFT_MOTOR_IDX], sizeof(retVal));
    return retVal;
}

float readRightMotor(char* buf)
{
    float retVal = 0;
    memcpy(&retVal, &buf[RIGHT_MOTOR_IDX], sizeof(retVal));
    return retVal;
}