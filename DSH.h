#ifndef DSH_H
#define DSH_H

#include <RFM69.h>

/* rfm69 setup */
#define FREQUENCY     RF69_915MHZ
#define ENCRYPTKEY    "sampleEncryptKey" //exactly the same 16 characters/bytes on all nodes!
#define IS_RFM69HW

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

const uint8_t RFM69_CTL_REQ = 0x20;
const uint8_t RFM69_CTL_END = 0x10;
const uint8_t RFM69_CTL_EVENT = 0x08;
const uint8_t RFM69_CTL_STR = 0x04;
const uint8_t RFM69_CTL_SEN_DATA = 0x02;

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

#endif /*DSH_H*/
