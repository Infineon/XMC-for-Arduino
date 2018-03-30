/*
  Simple example to check heap memory during run time for XMC devices
  Demonstrates the ability to check on free heap memory.
  15 July 2017
 */
#include <DeviceControlXMC.h>

XMCClass xmc2go;

char *pointer;        // Points to allocated memory 
size_t  free_memory;  // Used to store the value of unused memory;

void setup()
{
  Serial.begin(9600);

}
void loop()
{
  // Check the total free memory
  
  free_memory = xmc2go.freeRAM_Heap();
  Serial.print("Free memory before allocation is :");
  Serial.print(free_memory);
  delay(100);
  Serial.println();
  
  // Allocate some memory and check the changes
  pointer = (char*)malloc(100);
  if(pointer != 0)  // check if we had enough space to allocate that memory
    Serial.print("Allocated 100 bytes");
  delay(100);
  free_memory = xmc2go.freeRAM_Heap();
  delay(100);
  Serial.print("Free memory after allocation is :");
  Serial.print(free_memory);
  Serial.println();

  // Free the allocated memory and check the memory now 
  free(pointer);
  Serial.print("Freed 100 bytes");
  Serial.println();  
  free_memory = xmc2go.freeRAM_Heap();
  delay(100);
  Serial.print("Free memory after freeing is :");
  Serial.print(free_memory);
  
  while(1){}
}

