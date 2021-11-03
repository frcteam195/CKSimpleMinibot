#include "utils/WiFiHelper.hpp"

void connectToWiFi(const char * ssid, const char * pwd, const uint8_t LED_PIN)
{
	int ledState = 0;

#ifdef DEBUG
	printLine();
	Serial.println("Connecting to WiFi network: " + String(ssid));
#endif

	WiFi.begin(ssid, pwd);

	while (WiFi.status() != WL_CONNECTED) 
	{
		// Blink LED while we're connecting:
		digitalWrite(LED_PIN, ledState);
		ledState = (ledState + 1) % 2; // Flip ledState
		delay(500);
#ifdef DEBUG
		Serial.print(".");
#endif
	}

#ifdef DEBUG
	Serial.println();
	Serial.println("WiFi connected!");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
#endif
}

void printLine()
{
#ifdef DEBUG
	Serial.println();
	for (int i = 0; i < 30; i++)
	{
		Serial.print("-");
	}
	Serial.println();
#endif
}