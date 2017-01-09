
#include "RFM69_DSH.h"

RFM69_DSH dsh_radio;

const uint8_t network_id = 0;

void setup()
{
	Serial.begin(9600);
 
	dsh_radio.initialize(RF69_915MHZ, GATEWAY_ID, network_id);
	dsh_radio.setHighPower();

	// ping all nodes on the network
	for (uint8_t i = 1; i <= 10; ++i) {

		Serial.print("Pinging node ");
		Serial.print(i);

		if (dsh_radio.ping(i)) {
			Serial.println(": OK");
		} else {
			Serial.println(": FAILED");
		}
	}
dsh_radio.requestAll(1);

}

void loop()
{
  

	//delay(15);

	if (dsh_radio.receiveDone()) {

		Serial.println("Transmission Received");

		if (dsh_radio.errorReceived()) {
			Serial.println("Error Received");
		}
		
		if (dsh_radio.endReceived()) {
			Serial.println("End Received");
		}

		if (dsh_radio.eventReceived()) {
			Serial.println("Event Received");
		}

		if (dsh_radio.strReceived()) {
			Serial.println("String Received");
		}

		if (dsh_radio.sensorDataReceived()) {
			Serial.print("Sensor Data Received: ");
			Serial.print(dsh_radio.SENSOR_READING.sensorType);
			Serial.print(" : ");
			Serial.println(dsh_radio.SENSOR_READING.data);
		}

		// handle ACK
		if (dsh_radio.ACKRequested()) {
			dsh_radio.sendACK();
			Serial.println("ACK sent");
		}


	}

	/* request and receive data from the first node */

}
