/*
  Hint: after uploading, you need to reconnect the relax kit with the other port that is not used for uploading sketch; you can also let both ports connected
  
  This example demonstrates how to realize a simple two-way communication with USB. Open COM22 and enter c, then the 26 letters should be printed
  This example can have problem when run with the task mechanism (startTask()), if nothing works better polling should be used*/

#if !defined(USB0)
#error "USB not supported on this board"
#else
  
#include "USB.h"

void setup()
{
    USB.begin(115200);
    // Letters A to Z are written into buffer
    for (int i = 65; i < 91; i++)
    {
        USB.writeToBuffer(i);
    }
    USB.writeToBuffer('\n');
}

void loop()
{
    char c;
    while (USB.available())
    {
        c = (char)USB.read();
        if (c == 'c')
        {
            USB.clearTxBuffer();
        }
    }
}
#endif