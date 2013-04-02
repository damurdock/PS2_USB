/******************************************************************************
 *                                 PS2-USB                                     *
 *=============================================================================*
 *                             By: Duncan Murdock                              *
 *                             Date: 1/20/2012                                 *
 *                             Version: 3                                      *
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*
 *  Uses a Teensy 2.0 in Joystick mode to convert a PS2 controller to USB.     *
 * Based on the PJRC Joystick example and Bill Porter's excellent PS2X library *
 * Hardware and software are currently TESTED. Licensed under the MIT license  *
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
  error = controller.config_gamepad(0,1,2,3, false, false); // setup controller, config_gamepad(clock, command, attention, data, Pressures?, Rumble?); rumble and pressures currently unsupported
    //Guitar Hero controllers should work now. I don't have one to test though.
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
  else{ // turn on the LED and get controller type if all's well
    digitalWrite(11,HIGH); 
    type = controller.readType();
  }
  controller.read_gamepad(); //read the controller
  // now that we've read the pad, we can build our usb packet and send it 
  // remember that the packet will not send until we call Joystick.send_now();
  if(type !=2){ 
    Joystick.button(1, controller.Button(PSB_PINK));
    Joystick.button(2, controller.Button(PSB_BLUE));
    Joystick.button(3, controller.Button(PSB_RED));
    Joystick.button(4, controller.Button(PSB_GREEN));
    Joystick.button(5, controller.Button(PSB_L1));
    Joystick.button(6, controller.Button(PSB_R1));
    Joystick.button(7, controller.Button(PSB_L2));
    Joystick.button(8, controller.Button(PSB_R2));
    Joystick.button(11, controller.Button(PSB_L3));
    Joystick.button(12, controller.Button(PSB_R3));
    
    // working on PS3 compatibility, start && select will work as the PS button (hopefully)
    if(controller.Button(PSB_SELECT) && controller.Button(PSB_START)){
      Joystick.button(14, 1);
    }
    
    else if(controller.Button(PSB_SELECT) &! controller.Button(PSB_START)){
      Joystick.button(9, 1);
    }
    
    else if(!controller.Button(PSB_SELECT) & controller.Button(PSB_START)) {
      Joystick.button(10, 1);
    }
    
    // treat the dpad like a POV hat
    if(controller.Button(PSB_PAD_LEFT) && !controller.Button(PSB_PAD_UP) && !controller.Button(PSB_PAD_DOWN)){
      Joystick.hat(270);
    }
    else if(controller.Button(PSB_PAD_RIGHT) && !controller.Button(PSB_PAD_UP) && !controller.Button(PSB_PAD_DOWN)){
      Joystick.hat(90);
    }
    else if(controller.Button(PSB_PAD_UP)){
      Joystick.hat(0);
    }
    else if(controller.Button(PSB_PAD_DOWN)){
      Joystick.hat(180);
    }
    else if(controller.Button(PSB_PAD_LEFT) && controller.Button(PSB_PAD_UP)){
      Joystick.hat(315);
    }
    else if(controller.Button(PSB_PAD_LEFT) && controller.Button(PSB_PAD_DOWN)){
      Joystick.hat(135);
    }
    else if(controller.Button(PSB_PAD_RIGHT) && controller.Button(PSB_PAD_UP)){
      Joystick.hat(45);
    }
    else if(controller.Button(PSB_PAD_RIGHT) && controller.Button(PSB_PAD_DOWN)){
      Joystick.hat(225);
    }

    Joystick.X(((controller.Analog(PSS_LX) + 1) * 4) - 1); // have to do some gymnastics here because PS2X reports the analog value
    Joystick.Y(((controller.Analog(PSS_LY) + 1) * 4) - 1); // as 0-255, while the Teensy expects values from 0-1023 
    Joystick.Z(((controller.Analog(PSS_RX) + 1) * 4) - 1); // some precision is lost, hopefully that doesn't matter
    Joystick.Zrotate(((controller.Analog(PSS_RY) + 1) * 4) - 1);
    Joystick.send_now(); // send the packet and begin the loop anew
    delay(50);
    Joystick.button(14, 0);
    Joystick.button(9, 0);
    Joystick.button(10, 0);
    Joystick.hat(-1);
  }
  else if(type == 2){ // guitar hero
    Joystick.button(1, controller.Button(GREEN_FRET));
    Joystick.button(2, controller.Button(RED_FRET));
    Joystick.button(3, controller.Button(YELLOW_FRET));
    Joystick.button(4, controller.Button(BLUE_FRET));
    Joystick.button(5, controller.Button(ORANGE_FRET));
    Joystick.button(6, controller.Button(UP_STRUM) || controller.Button(DOWN_STRUM)); // if you strum at all, this button goes true.
    Joystick.button(9, controller.Button(STAR_POWER));
    Joystick.button(10, controller.Button(UP_STRUM));
    Joystick.button(11, controller.Button(DOWN_STRUM));
    
    // working on PS3 compatibility, start && select will work as the PS button (hopefully)
    if(controller.Button(PSB_SELECT) && controller.Button(PSB_START)){
      Joystick.button(14, 1);
    }
    
    else if(controller.Button(PSB_SELECT) &! controller.Button(PSB_START)){
      Joystick.button(7, 1);
    }
    
    else if(!controller.Button(PSB_SELECT) & controller.Button(PSB_START)) {
      Joystick.button(8, 1);
    }
    
    Joystick.X(((controller.Analog(WHAMMY_BAR) + 1) * 4) - 1);
    Joystick.send_now();
  }
}

