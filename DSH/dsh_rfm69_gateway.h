#ifndef DSH_RFM69_GATEWAY_H
#define DSH_RFM69_GATEWAY_H

#include <string>

#include "dsh_rfm69.h"

// send a data request to the provided node
bool sendDataRequest(RFM69& radio, uint8_t node_id, char *request);

// receives and parses the data from a sensor node
// this function will send ack if requested
String receiveSensorNodePacket(RFM69& radio);

#endif /* DSH_RFM69_GATEWAY_H */
