#include "utils/MotorHelper.hpp"

uint8_t getMotorDirection(float motorOutput)
{
    if (motorOutput > 0)
    {
        return FORWARD;
    }
    else if (motorOutput < 0)
    {
        return BACKWARD;
    }
    else
    {
        return RELEASE;
    }
}

uint8_t getMotorOutput(float motorOutput)
{
    motorOutput = fminf(fabsf(motorOutput), 1.0f);
    return (uint8_t)(motorOutput * 255);
}

void stopMotor(Adafruit_DCMotor *motor)
{
    motor->setSpeed(0);
	motor->run(RELEASE);
}

void setMotor(Adafruit_DCMotor *motor, float& motorOut)
{
    motor->setSpeed(getMotorOutput(motorOut));
    motor->run(getMotorDirection(motorOut));
}
