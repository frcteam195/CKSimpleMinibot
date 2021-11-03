#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include "GlobalConfig.h"

void connectToWiFi(const char * ssid, const char * pwd, const uint8_t LED_PIN);
void printLine();