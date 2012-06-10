/******************************************************************************
*                                 PS2-USB                                     *
*=============================================================================*
*                             By: Duncan Murdock                              *
*                             Date: 1/20/2012                                 *
*                             Version: 1                                      *
*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*
*  Uses a Teensy 2.0 in Joystick mode to convert a PS2 controller to USB.     *
* Based on the PJRC Joystick example and Bill Porter's excellent PS2X library *
* Hardware and software are currently UNTESTED. Licensed under the MIT license*
* , a copy of which is located in the included LICENSE file.                  *
*                                 Enjoy!                                      *
*-----------------------------------------------------------------------------*
*                       https://github.com/damurdock                          *
******************************************************************************/

#include <PS2X_lib.h>
PS2X controller;
int error = 0;
byte type = 0;

void setup(){
  error = controller.config_gamepad(0,1,2,3, false, false); // setup controller, config_gamepad(clock, command, attention, data, Pressures?, Rumble?); rumble and pressures currently unsupported (feel free to add them!)
  // Right now this code only works with a DualShock controller or similar clone, I'll add Guitar Hero support later. If you need it, there's support in the PS2X library. I'm just lazy.
  Joystick.useManualSend(true); // only send a USB packet after reading controller
}

void loop(){
  if(error == 1){ // flash led if there's an error
   digitalWrite(11,HIGH); 
   delay(500);
   digitalWrite(11,LOW); 
   delay(500);
   error = controller.config_gamepad(0,1,2,3, false, false); // Try to setup the controller again
  }
  else{ // turn on the LED if all's good
    digitalWrite(11,HIGH); 
  }
  controller.read_gamepad(); //read the controller
  // now that we've read the pad, we can build our usb packet and send it 
  // remember that the packet will not send until you call Joystick.send_now();

  Joystick.button(1, controller.Button(PSB_PINK));
  Joystick.button(2, controller.Button(PSB_BLUE));
  Joystick.button(3, controller.Button(PSB_RED));
  Joystick.button(4, controller.Button(PSB_GREEN));
  Joystick.button(5, controller.Button(PSB_L1));
  Joystick.button(6, controller.Button(PSB_R1));
  Joystick.button(7, controller.Button(PSB_L2));
  Joystick.button(8, controller.Button(PSB_R2));
  Joystick.button(9, controller.Button(PSB_SELECT));
  Joystick.button(10, controller.Button(PSB_START));
  Joystick.button(11, controller.Button(PSB_PAD_LEFT)); // Currently the D-Pad is being treated as four buttons
  Joystick.button(12, controller.Button(PSB_PAD_DOWN)); // Pressures could be supported with a later update
  Joystick.button(13, controller.Button(PSB_PAD_RIGHT)); //or, as sugggested by a diagram at PJRC, the D-Pad
  Joystick.button(14, controller.Button(PSB_PAD_UP)); //   could be made a POV Hat stick 
  Joystick.button(15, controller.Button(PSB_L3));
  Joystick.button(16, controller.Button(PSB_R3));
  
  Joystick.X(((controller.Analog(PSS_LX) + 1) * 4) - 1); // have to do some gymnastics here because PS2X reports the analog value
  Joystick.Y(((controller.Analog(PSS_LY) + 1) * 4) - 1); // as 0-255, while the Teensy expects values from 0-1023 
  Joystick.Z(((controller.Analog(PSS_RY) + 1) * 4) - 1); // some precision is lost, hopefully that doesn't matter
  Joystick.Zrotate(((controller.Analog(PSS_RX) + 1) * 4) - 1);
  delay(0); // for some reason, the code won't compile unless I either add a random function call or comment one out. not a clue why
  Joystick.send_now(); // send the packet and begin the loop anew
}
