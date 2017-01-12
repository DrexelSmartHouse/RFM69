
#include "RFM69_DSH.h"

RFM69_DSH dsh_radio;

const uint8_t network_id = 0;

volatile bool receiving = false;

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



}

void loop()
{

  	// check to see if were in the middle of a transmission 
  	// otherwise request all the data from the node
  	if (!receiving) {
    	delay(2000);
    	dsh_radio.requestAll(1);
    	receiving = true;
  	}

	if (dsh_radio.receiveDone()) {

		Serial.println("Transmission Received");

		if (dsh_radio.errorReceived()) {
			Serial.println("Error Received");
		}

		if (dsh_radio.endReceived()) {
			Serial.println("End Received");
      		receiving = false;
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
