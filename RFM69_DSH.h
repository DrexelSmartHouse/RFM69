#ifndef RFM69_DSH_H
#define RFM69_DSH_H

#include <RFM69.h>

/* rfm69 setup */
#define FREQUENCY RF69_915MHZ
#define ENCRYPTKEY "sampleEncryptKey" //exactly the same 16 characters/bytes on all nodes!

/* CTL byte definitions 
 *
 * RMF69 defaults:
 * 
 * 0x80 - send ack, lib defined
 *
 * 0x40 - request ack, lib defined
 * 
 * Custom:
 * 
 * 0x20 - REQ, this packet contains a request. Response is either
 * 		  data or and error. The response must be terminated with
 * 		  a done packet. Empty request means all data. 
 *
 * 0x10 - END, this is an empty packet the marks the
 * 		  end of a variable length response
 *
 * 0x08 - EVENT, (NOT YET IMPLEMENTED) this packet means that an asyn event happen
 * 		  and needs to be handled ASAP.
 *
 * 0x04 - STR, packet is a null term string
 *
 * 0x02 - SEN_DATA, packet is a SensorData struct
 *
 * NOTE: if 0x04 and 0x02 are both set then the an error occured (0x06)
 *
 * 0x01 - undefined bit
 *
 */

const uint8_t RFM69_CTL_DATA_REQ        = 0x20;
const uint8_t RFM69_CTL_SEND_END        = 0x10;
const uint8_t RFM69_CTL_EVENT           = 0x08;
const uint8_t RFM69_CTL_STR_PACKET      = 0x04;
const uint8_t RFM69_CTL_SEN_DATA_PACKET = 0x02;

// both data bits are one means there is an error
const uint8_t RFM69_CTL_ERROR = RFM69_CTL_STR | RFM69_CTL_SEN_DATA; // 0x06


// the node that all sensor nodes transmit to
const uint8_t GATEWAY_ID = 0;


/* Data Types */

// The max length of the string contained in a Data struct
// This INCLUDES the null char. Be careful!
const uint8_t MAX_SENSOR_NAME_LEN = 10;

typedef char[MAX_SENSOR_NAME_LEN] SensorName;

//SEN_DATA packet
struct SensorData {
  SensorName sensor_name;
  float data;
};

// STR packet
typedef char* StrPacket;

//Error packet
typedef char* ErrorPacket;

class RFM69_DSH: public RFM69 {

public:
	
	// original constructor with RFM69HW as the default
	RFM69_DSH(uint8_t slaveSelectPin=RF69_SPI_CS, uint8_t interruptPin=RF69_IRQ_PIN, bool isRFM69HW=true, uint8_t interruptNum=RF69_IRQ_NUM) :
		RFM69(slaveSelectPin, interruptPin, isRFM69HW, interruptNum) {
	}

	//TODO easy to use init functions for gateway and sensor node
	

	// Easy to use interface for received data
	bool errorReceived() const ( return ERROR_RECEIVED; } 
	bool strReceived() const { return STR_PACKET_RECEIVED && !errorReceived(); }
	bool sensorDataReceived() const { return SENSOR_DATA_PACKET_RECEIVED && !errorReceived(); }
	bool endReceived() const { return END_RECEIVED; }
	bool eventReceived() const { return EVENT_RECEIVED; }

	// new flags for the added CTL bits
	// naming convention was used to keep consistent with lib
	static volatile uint8_t DATA_REQUESTED;
	static volatile uint8_t END_RECEIVED;
	static volatile uint8_t EVENT_RECEIVED;
	static volatile uint8_t STR_PACKET_RECEIVED;
	static volatile uint8_t SENSOR_DATA_PACKET_RECEIVED;
	static volatile uint8_t ERROR_RECEIVED;
	
	// vars to hold the received data
	static volatile String RECEIVED_STRING;
	static volatile SensorData RECEIVED_SENSOR_DATA;


protected:

	// custom sendFrame function for sending different CTL bits
	void sendFrame(uint8_t toAddress, const void* buffer, uint8_t size, uint8_t CTLbyte);

	// override the interruptHook
	virtual void interruptHook(uint8_t CTLbyte);



}

#endif /* RFM69_DSH_H */
