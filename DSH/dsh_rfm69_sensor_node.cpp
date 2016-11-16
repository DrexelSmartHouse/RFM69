#include "dsh_rfm69_sensor_node.h"

inline bool sendPacket(RFM69& radio, Packet& payload) {
	
  	// print the payload
  	Serial.print("Sending packet: ");
	Serial.print(payload.str);
  	Serial.print(" ");
  	Serial.println(payload.data);

  	// send the payload
  	if (radio.sendWithRetry(K_receiver_node_id, (const void*)(&payload), sizeof(Packet), 1)) {
    	Serial.print(" ok!");
    	return true;
  	}
  	else {
    	Serial.println("failed to send");
    	return false;
  	}
}

bool sendSensorData(RFM69& radio, char sensor_type[], float data) {
	// the length of the inputed sensor type including the null char
  	unsigned int sensor_type_length = strlen(sensor_type) + 1;

  	if ( sensor_type_length > K_max_str_length ) {
    	Serial.println("Sensor type longer then max");
    	return false;
  	}

  	// prepare the payload
  	Packet payload;
  	// copy the sensor type into the payload
  	strncpy(payload.str, sensor_type, sensor_type_length);
  	//copy the data into the payload
  	payload.data = data;

  	return sendPacket(radio, payload); 
}

bool sendDoneMsg(RFM69& radio) {
	  Packet payload;
	  strncpy(payload.str, K_done_sending_values, strlen(K_done_sending_values)+1);
	  payload.data = 1;
	  return sendPacket(radio, payload); 

}

bool sendErrorMsg(RFM69& radio) {

	  Packet payload;
	  strncpy(payload.str, K_bad_request, strlen(K_bad_request)+1);
	  payload.data = -1;

  	return sendPacket(radio, payload); 
}
