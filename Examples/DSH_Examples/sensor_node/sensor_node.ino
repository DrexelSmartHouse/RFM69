#include "RFM69_DSH.h"

RFM69_DSH dsh_radio;

const uint8_t node_id = 1;
const uint8_t network_id = 0;

void setup()
{
	Serial.begin(9600);

	dsh_radio.initialize(RF69_915MHZ, node_id, network_id);
	dsh_radio.setHighPower();

}

void loop()
{

	if (dsh_radio.receiveDone()) {

		Serial.println("Transmission Received");

		if (dsh_radio.requestAllReceived()) {

      		Serial.println("Sending all sensor Data");

			if (sendAllSensorReadings()) {
        		Serial.println("Transmission Failed");
			}

			dsh_radio.sendEnd();

		}

		if (dsh_radio.ACKRequested()) {
			dsh_radio.sendACK();
			Serial.println("ACK sent");
		}
	}
}

bool sendAllSensorReadings() {

	if (!dsh_radio.sendSensorReading("TEMP", 123))
		return false;

	delay(10);

	else if (!dsh_radio.sendSensorReading("LIGHT", 55.5))
		return false;

	delay(10);

	else if (!dsh_radio.sendSensorReading("HUM", 25))
		return false;

	return true;
}
