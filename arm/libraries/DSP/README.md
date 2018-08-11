## Compilation problem with Arduino IDE
Due to some problem in the builder scripts for Arduino, the `new` keyword in C++ is not supported. Since this library involves the using of `new`, compiling
it for XMC1000 boards in the Arduino IDE would report the following error message:
```
In function `_sbrk':

sbrk.c:(.text._sbrk+0x18): undefined reference to `end'

collect2.exe: error: ld returned 1 exit status
```
The current work around would be to add the following lines at the top of your sketch:
```
extern "C" void *_sbrk(int incr);
void dummy_sbrk_caller() __attribute__((__used__));
void dummy_sbrk_caller()
{
  _sbrk(0);
} 
```

However, in PlatformIO the problem described above does not appear.