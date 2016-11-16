#ifndef DSH_RFM69_SENSOR_NODE
#define DSH_RFM69_SENSOR_NODE
#include "dsh_rfm69.h"

/* 
 * sends sensor data to the reciever node.
 * note the max sensor type length
 * 
 */
bool sendSensorData(RFM69& radio, char sensor_type[], float data);

// functions used to send the done and error message
bool sendDoneMsg(RFM69& radio);
bool sendErrorMsg(RFM69& radio);


#endif /* DSH_RFM69_SENSOR_NODE */
