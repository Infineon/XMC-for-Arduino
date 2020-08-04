/*
 * Simple DMA example for XMC4700 Relax Kit V1
 * Demonstrates how to setup an DMA, to transfer data between two places in memory.
 * Prints the message in Serial port.
 */

#include <DMA.h>

DMA dma_module;

#define DATA_LENGTH 10

uint32_t source_data[DATA_LENGTH] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
uint32_t destination_data[DATA_LENGTH];

void setup()
{
  Serial.begin(9600);
}

// The loop function is called in an endless loop
void loop()
{
  Serial.print("We are going to copy from source this data: ");
  for(int i=0; i<DATA_LENGTH; i++)
    Serial.print(source_data[i]);
  Serial.println();
  delay(1000);
  
  dma_module.beginDMA(DMA0);
  dma_module.configDMA_M2M(DMA0,0,(uint32_t)&source_data[0],(uint32_t)&destination_data[0],DATA_LENGTH,TRANSFER_WIDTH_32,BURST_LENGTH_8,true);
  dma_module.attachDMAInterrupt(DMA0, 0, dma_interrupt, BLOCK_TRANSFER_COMPLETE);

  /* Start DMA transfer */
  dma_module.beginDMATransaction(DMA0, 0);
  while(1)
  {
    /* Infinite loop */
  }
}

void dma_interrupt(void) {
  if (memcmp(source_data, destination_data, DATA_LENGTH) != 0)
  {
    /* Error array are not equal */
    __BKPT(0);
    Serial.print("An error happened \n");
  }
  Serial.print("We have copied to destination this data: ");
  for(int i=0; i<DATA_LENGTH; i++)
    Serial.print(destination_data[i]);
  Serial.println();
}


