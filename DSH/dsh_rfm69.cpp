#include "dsh_rfm69.h"

void setupRadio(RFM69& radio, uint8_t node_id, uint8_t network_id) {

  	radio.initialize(FREQUENCY, node_id, network_id);
  	radio.setHighPower(true);
  	radio.encrypt(ENCRYPTKEY);

}

