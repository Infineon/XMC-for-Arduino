/*
 * Simple DMA example for XMC4700 Relax Kit V1
 * Demonstrates how to setup an DMA, between memory and UART module. 
 * Prints the message in Serial port.
 */

#include <DMA.h>
DMA dma_module;

#define BUFFER_LENGTH 11

volatile bool transfer_done = false;
uint8_t message[] = "Hello World";
uint8_t received_message[BUFFER_LENGTH];
int led2 = 25;

//The setup function is called once at startup of the sketch
void setup()
{
  Serial.begin(9600);
  pinMode(led2, OUTPUT);  
}

void loop()
{
  uint8_t i;
  dma_module.beginDMA(DMA0);
  
  dma_module.configDMA_M2P(DMA0, 0, UART0_CH0, (uint32_t)&message[0],BUFFER_LENGTH,TRANSFER_WIDTH_8, TRANSFER_WIDTH_8, BURST_LENGTH_4, BURST_LENGTH_1,true);
  dma_module.attachDMAInterrupt(DMA0, 0 ,dma_interrupt, BLOCK_TRANSFER_COMPLETE);

  // If P2M 
  //dma_module.configDMA_P2M(DMA0, 0, UART0_CH0,(uint32_t)&received_message[0],BUFFER_LENGTH,TRANSFER_WIDTH_8, TRANSFER_WIDTH_8, BURST_LENGTH_1, BURST_LENGTH_1,true);
  //dma_module.attachDMAInterrupt(DMA0, 0,NULL, BLOCK_TRANSFER_COMPLETE);

  dma_module.beginDMATransaction(DMA0, 0);
  
  while (transfer_done == false){
  }
  // If P2M is used, print the buffer
  /* for(i = 1; i < BUFFER_LENGTH; i++)
    Serial.print((char)(received_message[i]));*/
    
  while(1);
}

void dma_interrupt() {
  transfer_done = true;
  digitalWrite(led2, HIGH);
}

