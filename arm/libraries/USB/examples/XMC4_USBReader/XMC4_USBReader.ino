/*Hint: after uploading, you need to reconnect the relax kit with the other port that is not used for uploading sketch; you can also let both ports connected 
  
  Print input from USB (COM22) to Serial (COM14). Caution: ports not always fixed*/

#if !defined(USB0)
#error "USB not supported on this board"
#else
  
#include "USB.h"

void setup()
{

    USB.begin(9600);
    /* When reading data begin serial to print read data*/
    Serial.begin(9600);
}

void loop()
{
    while (USB.available())
        Serial.print((char)USB.read());
    Serial.println();

    delay(1000);
}
#endif