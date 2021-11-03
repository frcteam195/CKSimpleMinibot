#pragma once

#include <stdint.h>
#include "GlobalConfig.h"

//Update this for added bytes
/*
{
    uint32_t api_packet_id,
    float left_motor_val,
    float right_motor_val,
}
*/
#define ID_IDX 0
#define LEFT_MOTOR_IDX 4
#define RIGHT_MOTOR_IDX 8
#define MIN_PACKET_SIZE 12

uint32_t readID(char* buf);
float readLeftMotor(char* buf);
float readRightMotor(char* buf);