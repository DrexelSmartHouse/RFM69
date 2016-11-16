#include "dsh_rfm69_gateway.h"


bool sendDataRequest(RFM69& radio, uint8_t node_id, char *request) {

	// calculate the length of the request including null space char
	const unsigned int request_length = strlen(request)+1;

	// check to make sure it doesn't exceed data limit
	if (request_length > RF69_MAX_DATA_LEN) {
		return false;
	}

	// send the request 
	return radio.sendWithRetry(node_id, request, request_length);

}

String receiveSensorNodePacket(RFM69& radio) {

	// check to make sure the packet is the right length
	// don't send ack if its not the right data
	if (radio.DATALEN != sizeof(Packet)) {
		return "ERROR: DATA LENGTH";
	}

	// cast byte array back into struct
	Packet received_packet = *(Packet*)radio.DATA;

	// convert the data type char [] to string
	const String data_type = String(received_packet.str);
	// convert the float data to a string with 3 decimal places
	const String data = String(received_packet.data, 3);

	// send the ack if requested
	if (radio.ACKRequested()) {
		radio.sendACK();
	}

	return data_type + ":" + data;
}
