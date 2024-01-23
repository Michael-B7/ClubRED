// This code was created by Abel Fernandez for FUSD's ClubRED students.
// This is a simple code for tank drive with an Arduino mega, Cytron Motor Shield, and Cytron PS2 Shield.
// Tank drive is where joysticks are used to control motors.  One joystick per motor

#include <SoftwareSerial.h>    //Make sure to have this library.
#include <Cytron_PS2Shield.h>  //Make sure to have this library.
#include "CytronMotorDriver.h" //Make sure to have this library.

Cytron_PS2Shield ps2(0,1); // SoftwareSerial: Rx and Tx pin.  Look at your mini jummper is connected to the corresponding numbers.  
// Please read the Shield-PS2 User's manual for more information
// Note if 1 and/or 0 are used for RX and TX pins, disconnect PS2 shield when uplaoding code
// for reference look at page 6 in Shield-PS2 User's manual item #10 and #9

// Configure the motor driver.
CytronMD motor1(PWM_DIR, 9, 8);  //  PWM 1 = Pin 9, DIR 1 = Pin 8. Make sure that the mini jummpers is connected to the corresponding #
CytronMD motor2(PWM_DIR, 11, 13); // PWM 2 = Pin 11, DIR 2 = Pin 13.  Make sure that the mini jummpers is connected to the corresponding #
CytronMD motor3(PWM_DIR, 10, 12); // PWM 3 = Pin 10, DIR 3 = Pin 12.  Make sure to double check the jumper connector for this pin.  
// for reference look at page 2 in Cytron dual channel motor driver shield datasheet

int ly = 0;  // int stands for integer (a variable).  This variable will be defined for the Left joystick Y-axis (up and down) later
int ry = 0;  // int stands for integer (a variable).  This variable will be defined for the Right joystick Y-axis (up and down) later
int intakeState = 0; // Initialize intake state vaiable
/*  state descriptions:
 *   0  motor off 
 *   1  motor forward (load)
 *   2 motor backwards (unload)
 */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ps2.begin(9600); // This bandrate must be the same with the jumper settings on the PS2 shield
                   // for reference look at page 6 in Shield-PS2 User's manual item #6


}

void loop() {
  
 ly = ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS);  // Defining the ly integer as the Left Joystick Y-Axis
 ry = ps2.readButton(PS2_JOYSTICK_RIGHT_Y_AXIS); // Defining the ry integer as the Right Joystick Y-Axis

// Look on page 13 of the Shield-PS2 User Manual for how the joystick is mapped
// Y-Axis
// Middle (neutral), Value is 128
// Push up, value change is from 128 to 0
// Push down, value change from 128 to 255

// if ry value is grater than 130 (push down)
 if(ry>130){
       ry=(ry-128)*-2;       // Take your (ry value - 128) multiply it by -2 (negative for backward and 2 so at full throttle down, it is a full power *255*)
       motor2.setSpeed(ry);  // write your new value
    }else if(ry<125){        // if your ry value is less than 125 (push up)
       ry=(127-ry)*2;        // (127 - your ry value) then multiply it by 2 ( 2 so at full throttle up, it is a full power *255*).
       motor2.setSpeed(ry);  // write your new value     
    }else{
       motor2.setSpeed(0);   // else stop
    }
    
// if ly value is grater than 130 (push down)    
    if(ly>130){             
       ly=(ly-128)*-2;       // Take your (ly value - 128) multiply it by -2 (negative for backward and 2 so at full throttle down, it is a full power *255*)
       motor1.setSpeed(ly);  // write your new value
    }else if(ly<125){        // if your ry value is less than 125 (push up)
       ly=(127-ly)*2;        // (127 - your ly value) then multiply it by 2 ( 2 so at full throttle up, it is a full power *255*).
       motor1.setSpeed(ly);  // write your new value     
    }else{
       motor1.setSpeed(0);   // else stop
    }
    
  if(ps2.readButton(PS2_SELECT)== 0)
  { // 0 means pressed
      autonomous();
    }
  
    if(ps2.readButton(PS2_LEFT_2)== 0) // 0 = pressed, 1 == released 
  {
  intakeState = 2; 
  
  }

  if(ps2.readButton(PS2_RIGHT_2)== 0) // 0 = pressed, 1 == released 
  {
  intakeState = 1;
  
  }
  

  if(ps2.readButton(PS2_LEFT_1)== 0) // 0 = pressed, 1 == released 
  {
  intakeState = 0;
  
  }
  if(ps2.readButton(PS2_RIGHT_1)== 0) // 0 = pressed, 1 == released 
  {
  intakeState = 0;
  
  }
  //implement button state
  if(intakeState == 2)
  {
    motor3.setSpeed(-255);
  }
   if(intakeState == 1)
  {
    motor3.setSpeed(255);
  }
  if(intakeState == 0)
  {
    motor3.setSpeed(0);
  }
  
  }
  
  // Define autonomous mode! When done (after 15 seconds) go back to main loop
  void autonomous()
  {
      motor3.setSpeed(255);
      motor2.setSpeed(100);
      motor1.setSpeed(100);
    // drive forward for a certain amount of time
  delay(8000);
    
    // robot turn around toward start?

}
