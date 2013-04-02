##PS2-USB

###Requirements
To setup and use PS2-USB, you'll need:
  * A PJRC Teensy 2.0
  * A copy of Arduino 1.0 or higher with Teensyduino installed 
  * Either
    * Two (2) 5.6k resistors
    * Or to convert your Teensy to 3.3 volts
  * One (1) 10k resistor
  * Either some perfboard, or a PCB made from the provided files
  * Header pins or wire, depending on how you build PS2-USB
  * A PS2 Controller (non-3.3v version only tested with official Dualshock 2 controller)
  * A method of connecting your controller to the circuit
  
###Wiring
PS2-USB can be used in two configurations, 5v and 3.3v. CadSoft EAGLE board and schematics are available in the hardware directory. If you are using perfboard, a breadboard, a freehand circuit, or any other method, follow these instructions.

####5v
NOTE: The 5v version has only been tested and confirmed to work with an official Sony Dualshock 2 controller. Your results may vary.
Thanks to Bill Porter and Curious Inventor for their work, diagrams, and instructions.

Controller ---------------> Teensy  
Pin 1 ----------> Pin B3  
        |-----(10k resistor)--> VCC  
Pin 2 ---------> Pin B1  
Pin 3 NC  
Pin 4 ---------> GND  
Pin 5 ---------> VCC  
Pin 6 --(5.6k resistor)--> Pin B2  
Pin 7 --(5.6k resistor)--> Pin B0  
Pin 8 NC  
Pin 9 NC  

####3.3v
NOTE: This requires that you [convert your Teensy to 3.3 volts](http://www.pjrc.com/teensy/3volt.html) or [run it from an external 3.3 volt supply] (http://www.pjrc.com/teensy/external_power.html).
Thanks to Bill Porter and Curious Inventor for their work, diagrams, and instructions.

Controller --------------> Teensy  
Pin 1 ----------> Pin B3  
        |-----(10k resistor)--> VCC  
Pin 2 ---------> Pin B1  
Pin 3 NC    
Pin 4 ---------> GND  
Pin 5 ---------> VCC  
Pin 6 ---------> Pin B2  
Pin 7 ---------> Pin B0  
Pin 8 NC  
Pin 9 NC  

###Software
The PS2-USB software is written in Teensyduino, which means that you need to have a a current (1.0 or above) version of the Arduino software installed, as well as the PJRC Teensyduino software.

To setup the software, simply open PS2_USB.ino in Arduino, select "Teensy 2.0" as the board type, "Keyboard \+ Mouse \+ Joystick" as the USB type, and "16 MHz" as the CPU speed (8 MHz if running on 3.3 volts). Then, hit verify, and wait for the Teensy Loader to open. When Teensy Loader is open, make sure your Teensy is connected and hit the reset button on the Teensy. After the code is loaded, you're good to go!

###Usage
PS2-USB shouldn't require any extra work once the hardware is built and the software loaded. There are a few things you should know, however. When PS2-USB is connected, the Teensy's LED will indicate its' status. If the light is flashing, either no controller is connected, or PS2X cannot talk to the controller. Try the instructions on [this page](http://www.billporter.info/arduino-playstation-2-controller-library-troubleshooting-guide/), or try using the 3.3 volt version. Once your controller is working, you may want to look at the Button Diagram.jpg file to see how the buttons are numbered (This diagram is based on a diagram available on the PJRC website. Photo taken by Duncan Murdock, Playstation is a registered trademark of Sony).

###Credits
PS2-USB relies upon the [PS2X library by Bill Porter] (http://www.billporter.info/playstation-2-controller-arduino-library-v1-0/) and the [PJRC Teensyduino joystick library] (http://www.pjrc.com/teensy/td_joystick.html). I would also like to thank Curious Inventor for their PS2 controller interface guide, and Bill Porter for his troubleshooting guide. 

PS2-USB's hardware uses parts from the Sparkfun Eagle Library, as well a modified part for the Teensy 2.0 created by Mark Gross. The modified version, details, and license are in the hardware directory.

PS2-USB is written and maintained by Duncan Murdock. PS2-USB and all related works by Duncan Murdock are licensed under the MIT License unless otherwise noted. A copy of the MIT License is provided in the accompanying LICENSE file. If the LICENSE file is not included or is damaged in some way, a copy can be viewed at http://www.opensource.org/licenses/mit-license.php.

