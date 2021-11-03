#include <Arduino.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <Adafruit_MotorShield.h>

#include "utils/GlobalConfig.h"
#include "utils/WiFiHelper.hpp"
#include "utils/UDPHelper.hpp"
#include "utils/MotorHelper.hpp"


//Make sure to update this file with your WiFi Credentials
#include "WiFiCredentials.hpp"

const uint16_t kUDPPort = 5809;

const uint8_t LED_PIN = 13;
#define VOLTAGE_PIN A13;

int ledState;
uint32_t ledCounter;

WiFiUDP mUDP;
char mPacketBuffer[1505];

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(3);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(4);

unsigned long mHeartbeat;
static constexpr unsigned long TIMEOUT_MILLIS = 2000;

void setMotors(float leftMotorOut, float rightMotorOut)
{
	setMotor(leftMotor, leftMotorOut);
	setMotor(rightMotor, rightMotorOut);
}

void stopMotors()
{
	stopMotor(leftMotor);
	stopMotor(rightMotor);
}

void blinkLEDStep(uint32_t maxCount)
{
	if (ledCounter++ % maxCount == 0)
	{
		digitalWrite(LED_PIN, ledState);
		ledState = (ledState + 1) % 2; // Flip ledState
	}
}

void setup() {
	// Initilize hardware:
#ifdef DEBUG
	Serial.begin(115200);
#endif
	pinMode(LED_PIN, OUTPUT);

	if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
	// if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
#ifdef DEBUG
		Serial.println("Could not find Motor Shield. Check wiring.");
#endif
		while (1)
		{
			blinkLEDStep(500);	//Blink LED to indicate connection error
		}
	}

	//Set all to off on setup
	stopMotors();

	// Connect to the WiFi network (see function below loop)
	connectToWiFi(netName, netPswd, LED_PIN);
	mUDP.begin(kUDPPort);
}

void loop() {
	int sensorValue = analogRead(A0);
	// Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
	float voltage = (sensorValue * (5.0 / 1023.0)) * 2.0;	//Double voltage (resistive tap) - Check this to make sure is not 3.3v

	if (voltage < 3.4)
	{
		//Do something for low battery handling
		//Blink LED every 2000 cycles
		blinkLEDStep(2000);
	}

	int packetSize = mUDP.parsePacket();
	if (packetSize) {
		// IPAddress remoteIp = mUDP.remoteIP();
		int len = mUDP.read(mPacketBuffer, 1505);
		if (len >= MIN_PACKET_SIZE) {
			uint32_t packetId = readID(mPacketBuffer);
			(void)packetId;	//Don't warn for currently unused variable

			float leftMotorOut = readLeftMotor(mPacketBuffer);
			float rightMotorOut = readRightMotor(mPacketBuffer);

			setMotors(leftMotorOut, rightMotorOut);

			mHeartbeat = millis();
		}
	}

	if (millis() - mHeartbeat >= TIMEOUT_MILLIS)
	{
		stopMotors();
	}
}