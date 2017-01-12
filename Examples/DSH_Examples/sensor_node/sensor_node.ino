#include "RFM69_DSH.h"

RFM69_DSH dsh_radio;

const uint8_t node_id = 1;
const uint8_t network_id = 0;

volatile bool send_all = false;

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

		if (dsh_radio.requestAllReceived())
		  send_all = true;
      
		if (dsh_radio.ACKRequested()) {
			dsh_radio.sendACK();
			Serial.println("ACK sent");
		}
   
	}
	
	if (send_all) {
    if (!sendAllSensorReadings())
        Serial.println("Transmission Failed");
        
     send_all = false;
  }
  
}

bool sendAllSensorReadings() {
  
  Serial.println("Sending all sensor Data");

	if (!dsh_radio.sendSensorReading("TEMP", 13))
		return false;

	if (!dsh_radio.sendSensorReading("LIGHT", 55.5))
		return false;

	if (!dsh_radio.sendSensorReading("HUM", 25))
		return false;

   dsh_radio.sendEnd();
   
	return true;
}
