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
 * 0x20 - EVENT, this packet contains data (string and a float)
 * 		  but was not requested.
 *
 * 0x10 - PING, this is a ping request. Response is a simple ack 
 *
 * 0x08 - ERROR, this packet contains an error message
 *
 * 0x04 - REQ, this packet contains a request. Response is either
 * 		  data or and error. The response must be terminated with
 * 		  a done packet. All nodes must handle the "ALL" request
 * 0x02 - DATA, this packet contains data (string and a float)
 *
 * 0x01 - END, this is an empty packet the marks the
 * 		  end of a variable length response
 */

const uint8_t RFM69_CTL_EVENT = 0x20;
const uint8_t RFM69_CTL_PING = 0x10;
const uint8_t RFM69_CTL_ERROR = 0x08;
const uint8_t RFM69_CTL_REQ = 0x04;
const uint8_t RFM69_CTL_DAT = 0x02;
const uint8_t RFM69_CTL_EN = 0x01;

// the node that all sensor nodes transmit to
const uint8_t GATEWAY_ID = 0;

// The max length of the string contained in a Data struct
// This INCLUDES the null char. Be careful!
const uint8_t MAX_DATA_STR_LEN = 10;

// data contained in an EVENT or a DATA packet
struct Data {
  char str[MAX_DATA_STR_LEN];
  float data;
};

#endif /*DSH_H*/
