#pragma once

#include <stdint.h>
#include <Adafruit_MotorShield.h>
#include "GlobalConfig.h"

uint8_t getMotorDirection(float motorOutput);
uint8_t getMotorOutput(float motorOutput);

void stopMotor(Adafruit_DCMotor *motor);
void setMotor(Adafruit_DCMotor *motor, float& motorOut);