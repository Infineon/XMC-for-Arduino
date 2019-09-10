/*
  ButtonMouseControl

 For XMC4700 Relax Kit V1

 Controls the mouse from pushbuttons.

 The mouse movement is always relative. This sketch reads four pushbuttons, and uses them to set the movement of the mouse.

 Hint: after uploading, you need to reconnect the relax kit with the other port that is not used for uploading sketch; you can also let both ports connected

 this code is in the public domain

 */

#if (UC_FAMILY == XMC1)
#error "USB not supported on this board"
#else
  
#include <Mouse.h>

// set pin numbers for the five buttons:
const int upButton = BUTTON1;
const int downButton = BUTTON2;
const int leftButton = 4;
const int rightButton = 5;
const int mouseButton = 6;

int range = 5;              // output range of X or Y movement; affects movement speed
int responseDelay = 100;     // response delay of the mouse, in ms


void setup() {
  // initialize the buttons' inputs:
  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);
  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);
  pinMode(mouseButton, INPUT);
  // initialize mouse control:
  Mouse.begin();
}

void loop() {
  // read the buttons:
  int upState = digitalRead(upButton);
  int downState = digitalRead(downButton);
  int rightState = false; // digitalRead(rightButton);
  int leftState = false; // digitalRead(leftButton);
  int clickState = true; //digitalRead(mouseButton);

  // calculate the movement distance based on the button states:
  int  xDistance = (leftState - rightState) * range;
  int  yDistance = (upState - downState) * range;

  // if X or Y is non-zero, move:
  if ((xDistance != 0) || (yDistance != 0)) {
    Mouse.move(xDistance, yDistance, 0);
  }

  // if the mouse button is pressed:
  if (clickState == HIGH) {
    // if the mouse is not pressed, press it:
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
    }
  }
  // else the mouse button is not pressed:
  else {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
  }

  // a delay so the mouse doesn't move too fast:
  delay(responseDelay);
}
#endif
