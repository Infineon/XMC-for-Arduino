/*
  Simple example to check stack memory during run time for XMC devices
  Demonstrates the ability to check on free stack memory.
  15 July 2017
 */
#include <DeviceControlXMC.h>

XMCClass xmc4700;

uint32_t free_stack = 0;
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // Check the stack value when in this function (loop)
  delay(1000);
  Serial.print("Free stack in function loop is:");
  free_stack = xmc4700.freeRAM_Stack();
  Serial.print(free_stack);
  Serial.println();
  delay(1000);
  
  // Check the stack value after calling another function
  doNothing(200);

  // Check the stack after going back to loop
  Serial.print("Free stack after going back to loop is:");
  free_stack = xmc4700.freeRAM_Stack();
  Serial.print(free_stack);
  Serial.println();
  delay(1000);
  
  while(1){}
}

// Function that does nothong. just some parameters & local variables, so that the difference
// in stack will be more obvious
void doNothing(int value) {
  
  int j=0;
  uint32_t stack_now = 0;
  for(int i =0; i < value; i++)  {
     j = i;
  }
  Serial.print("Free stack after entering doNothing function is:");
  stack_now = xmc4700.freeRAM_Stack();
  Serial.print(stack_now);
  Serial.println();
  delay(1000);
}

