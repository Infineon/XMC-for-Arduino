/* Print input from USB (COM22) to Serial (COM14). Caution: ports not always fixed*/

#if (UC_FAMILY == XMC1)
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