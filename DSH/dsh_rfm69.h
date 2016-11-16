#ifndef DSH_RFM69_H
#define DSH_RFM69_H

#include <RFM69.h>

/* rfm69 setup */
#define FREQUENCY     RF69_915MHZ
#define ENCRYPTKEY    "sampleEncryptKey" //exactly the same 16 characters/bytes on all nodes!
#define IS_RFM69HW

// the max length of the sensor type including the trailing null char
const uint8_t K_max_str_length = 10;

// the node that all sensor nodes transmit to
const uint8_t K_receiver_node_id = 1;

// request responses
const char K_bad_request[K_max_str_length] = "BAD REQ";
const char K_done_sending_values[K_max_str_length] = "DONE";

struct Packet {
  char str[K_max_str_length];
  float data;
};



/* radio setup function*/
void setupRadio(RFM69& radio, uint8_t node_id, uint8_t network_id);

#endif /*DSH_RFM69_H*/
