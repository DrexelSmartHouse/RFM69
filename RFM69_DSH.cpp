#include <RFM69_DSH.h>

#include <RFM69.h>
#include <RFM69registers.h>
#include <SPI.h>

volatile uint8_t RFM69_DSH::DATA_REQUESTED;
volatile uint8_t RFM69_DSH::END_RECEIVED;
volatile uint8_t RFM69_DSH::EVENT_RECEIVED;
volatile uint8_t RFM69_DSH::STR_PACKET_RECEIVED;
volatile uint8_t RFM69_DSH::SENSOR_DATA_PACKET_RECEIVED;
volatile uint8_t RFM69_DSH::ERROR_RECEIVED;

//internal send function that accepts a CTLbyte
void RFM69_DSH::sendFrame(uint8_t toAddress, const void* buffer, uint8_t bufferSize, uint8_t CTLbyte) {

	// most of this is the original function except
	// that the CTL byte is now an input
	
	setMode(RF69_MODE_STANDBY); // turn off receiver to prevent reception while filling fifo
  	while ((readReg(REG_IRQFLAGS1) & RF_IRQFLAGS1_MODEREADY) == 0x00); // wait for ModeReady
  	writeReg(REG_DIOMAPPING1, RF_DIOMAPPING1_DIO0_00); // DIO0 is "Packet Sent"
  	if (bufferSize > RF69_MAX_DATA_LEN) bufferSize = RF69_MAX_DATA_LEN;

  	// write to FIFO
  	select();
  	SPI.transfer(REG_FIFO | 0x80);
  	SPI.transfer(bufferSize + 3);
  	SPI.transfer(toAddress);
  	SPI.transfer(_address);
  	SPI.transfer(CTLbyte);

  	for (uint8_t i = 0; i < bufferSize; i++)
    	SPI.transfer(((uint8_t*) buffer)[i]);
  	unselect();

  	// no need to wait for transmit mode to be ready since its handled by the radio
  	setMode(RF69_MODE_TX);
  	uint32_t txStart = millis();
  	while (digitalRead(_interruptPin) == 0 && millis() - txStart < RF69_TX_LIMIT_MS); // wait for DIO0 to turn HIGH signalling transmission finish
  	//while (readReg(REG_IRQFLAGS2) & RF_IRQFLAGS2_PACKETSENT == 0x00); // wait for ModeReady
  	setMode(RF69_MODE_STANDBY);
}


// method is called when a new packet is received
void RFM69_DSH::interruptHook(uint8_t CTLbyte) {

	// the first two bits are handled by the lib
	// these are the ack received and requested bits
	
	//set all the flags based on the CTL byte
	DATA_REQUESTED = CTLbyte & RFM69_CTL_DATA_REQ;
	END_RECEIVED   = CTLbyte & RFM69_CTL_SEND_END;
	EVENT_RECEIVED = CTLbyte & RFM69_CTL_EVENT;
	STR_PACKET_RECEIVED = CTLbyte & RFM69_CTL_STR_PACKET;
	SENSOR_DATA_PACKET_RECEIVED = CTLbyte & RFM69_CTL_SEN_DATA_PACKET;
	ERROR_RECEIVED = CTLbyte & RFM69_CTL_ERROR;
	
}
