/*
  Simple example to check heap memory during run time for XMC devices
  Demonstrates the ability to check on free heap memory.
*/

#include <DeviceControlXMC.h>

XMCClass XMC;

char *pointer;        // Points to allocated memory 
size_t  freeMemory;  // Used to store the value of unused memory;

void setup()
{
  Serial.begin(9600);

}
void loop()
{
  // Check the total free memory
  freeMemory = XMC.freeHeapRAM();
  Serial.print("Free memory before allocation is :");
  Serial.print(freeMemory);
  delay(100);
  Serial.println();
  
  // Allocate some memory and check the changes
  pointer = (char*)malloc(100);
  if(pointer != 0)  // Check if we had enough space to allocate that memory
    Serial.print("Allocated 100 bytes");
  delay(100);
  freeMemory = XMC.freeHeapRAM();
  delay(100);
  Serial.print("Free memory after allocation is :");
  Serial.print(freeMemory);
  Serial.println();

  // Free the allocated memory and check the memory now 
  free(pointer);
  Serial.print("Freed 100 bytes");
  Serial.println();  
  freeMemory = XMC.freeHeapRAM();
  delay(100);
  Serial.print("Free memory after freeing is :");
  Serial.print(freeMemory);
  // Wait and do nothing
  while(1){}
}

