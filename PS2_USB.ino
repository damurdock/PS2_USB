/******************************************************************************
 *                                 PS2-USB                                     *
 *=============================================================================*
 *                             By: Duncan Murdock                              *
 *                             Date: 1/20/2012                                 *
 *                             Version: 4                                      *
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
boolean config = false;

void setup(){
  error = controller.config_gamepad(0,1,2,3, false, false); // setup controller, config_gamepad(clock, command, attention, data, Pressures?, Rumble?); rumble and pressures currently unsupported
    //Guitar Hero controllers should work now. I don't have one to test though.
}

void loop(){
  if(error == 1){ // flash led if there's an error
    digitalWrite(11,HIGH); 
    delay(500);
    digitalWrite(11,LOW); 
    delay(500);
    error = controller.config_gamepad(0,1,2,3, false, false); // Try to setup the controller again
  }
  else if (!config) { // turn on the LED and get controller type if all's well
    digitalWrite(11,HIGH); 
    type = controller.readType();
    config = true;
  }
  controller.read_gamepad(); //read the controller
  // testing out sending the usb packet spontaneously, should reduce lag a bit
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
    
    // working on PS3 compatibility, start && select will work as the PS button
    if(controller.Button(PSB_SELECT) && controller.Button(PSB_START)){
      Joystick.button(13, 1);
      Joystick.button(9, 0);
      Joystick.button(10, 0);
    }
    
    else if(controller.Button(PSB_SELECT) &! controller.Button(PSB_START)){
      Joystick.button(9, 1);
    }
    
    else if(!controller.Button(PSB_SELECT) & controller.Button(PSB_START)) {
      Joystick.button(10, 1);
    }
    else {
      Joystick.button(13, 0);
      Joystick.button(9, 0);
      Joystick.button(10, 0);
    }
    
    // treat the dpad like a POV hat
    if(controller.Button(PSB_PAD_LEFT) && !controller.Button(PSB_PAD_UP) && !controller.Button(PSB_PAD_DOWN)){
      Joystick.hat(270);
    }
    else if(controller.Button(PSB_PAD_RIGHT) && !controller.Button(PSB_PAD_UP) && !controller.Button(PSB_PAD_DOWN)){
      Joystick.hat(90);
    }
    else if(controller.Button(PSB_PAD_UP) && !controller.Button(PSB_PAD_RIGHT) && !controller.Button(PSB_PAD_LEFT)){
      Joystick.hat(0);
    }
    else if(controller.Button(PSB_PAD_DOWN) && !controller.Button(PSB_PAD_RIGHT) && !controller.Button(PSB_PAD_LEFT)){
      Joystick.hat(180);
    }
    else if(controller.Button(PSB_PAD_LEFT) && controller.Button(PSB_PAD_UP)){
      Joystick.hat(315);
    }
    else if(controller.Button(PSB_PAD_LEFT) && controller.Button(PSB_PAD_DOWN)){
      Joystick.hat(225);
    }
    else if(controller.Button(PSB_PAD_RIGHT) && controller.Button(PSB_PAD_UP)){
      Joystick.hat(45);
    }
    else if(controller.Button(PSB_PAD_RIGHT) && controller.Button(PSB_PAD_DOWN)){
      Joystick.hat(135);
    }
    else {
      Joystick.hat(-1);
    }
    
    Joystick.X(map(controller.Analog(PSS_LX),0,255,0,1023)); // updated to use map(), which is designed for this
    Joystick.Y(map(controller.Analog(PSS_LY),0,255,1023,0)); // these axes are inversed for some reason
    Joystick.Z(map(controller.Analog(PSS_RX),0,255,0,1023));
    Joystick.Zrotate(map(controller.Analog(PSS_RY),0,255,1023,0));
  }
  else if(type == 2){ // guitar hero
    // mapping thanks to http://strategywiki.org/wiki/Guitar_Hero_II/Controls
    Joystick.button(8, controller.Button(GREEN_FRET));
    Joystick.button(3, controller.Button(RED_FRET));
    Joystick.button(4, controller.Button(YELLOW_FRET));
    Joystick.button(2, controller.Button(BLUE_FRET));
    Joystick.button(1, controller.Button(ORANGE_FRET));
    Joystick.button(9, controller.Button(STAR_POWER));
        
    if(controller.Button(UP_STRUM) || controller.Button(DOWN_STRUM)){ // if you strum at all, this button goes true.
      Joystick.hat(0);
    }
    else {
      Joystick.hat(-1);
    }
    
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
    
    Joystick.Y(map(controller.Analog(WHAMMY_BAR),0,255,0,1023));
    Joystick.send_now();
  }
}

