/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       robol                                                     */
/*    Created:      7/8/2024, 3:20:47 PM                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include <robot_config.h>


using namespace vex;

// A global instance of competition
competition Competition;
brain  Brain;
motor leftMotorA = motor(PORT12, ratio18_1, true);
motor leftMotorB = motor(PORT13, ratio18_1, true);
motor leftMotorC = motor(PORT14, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB, leftMotorC);
motor rightMotorA = motor(PORT18, ratio18_1, true);
motor rightMotorB = motor(PORT19, ratio18_1, false);
motor rightMotorC = motor(PORT20, ratio18_1, false);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB, rightMotorC);
motor leftLift = motor(PORT5, ratio18_1, true);
motor rightLift = motor(PORT6, ratio18_1, false);

motor leftTake = motor(PORT1, ratio18_1, true);
motor rightTake = motor(PORT10, ratio18_1, false);
motor_group Take = motor_group(leftTake, rightTake);
motor_group Lift = motor_group(leftLift, rightLift);
controller Controller = controller(primary);
const int32_t InertialPort = PORT17;
Drive Chassis(ZERO_TRACKER_ODOM,LeftDriveSmart,RightDriveSmart,InertialPort, 3.25, 1/0.6, 360,
//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT2,     -PORT3,

//LB:      //RB: 
PORT7,     -PORT8,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the Chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
3,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2.75,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
-2,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
1,

//Sideways tracker diameter (reverse to make the direction switch):
-2.75,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
5.5

);

digital_out MoGo = digital_out(Brain.ThreeWirePort.A);
digital_out Intake = digital_out(Brain.ThreeWirePort.B);

void tuned_constants()
{
Chassis.set_drive_constants(12, 0.7, 0.01, 1.2, 10); // Increase KD
  Chassis.set_heading_constants(6, .4, 0, 1, 0); // turning tune
 // Chassis.set_turn_constants(12, 0.25, 0.0005, 1.25, 15);
Chassis.set_turn_constants(12, 0.47, 0.008, 2.2, 15); // Increase KP, decrease KI, and decrease KD

  Chassis.set_swing_constants(12, 0.47, 0.008, 2.2, 15);
  Chassis.set_drive_exit_conditions(1.5, 300, 2200);
  Chassis.set_turn_exit_conditions(1, 300, 1500);
  Chassis.set_swing_exit_conditions(1, 300, 1500);
}




int current_auton_selection = 0;
bool auto_started = false;





void pre_auton(void) {

tuned_constants();
Chassis.Gyro.calibrate();
  while (Chassis.Gyro.isCalibrating()) 
  {
    wait(25, msec);
  }
  Brain.Screen.clearScreen();
while(!auto_started){
    Brain.Screen.clearScreen();
    Controller.Screen.clearScreen();
    Brain.Screen.printAt(5, 20, "JAR Template v1.2.0");
    Brain.Screen.printAt(5, 40, "Battery Percentage:");
    Brain.Screen.printAt(5, 60, "%d", Brain.Battery.capacity());
    Brain.Screen.printAt(5, 80, "Chassis Heading Reading:");
    Brain.Screen.printAt(5, 100, "%f", Chassis.get_absolute_heading());
    Brain.Screen.printAt(5, 120, "Selected Auton:");
    Controller.Screen.setCursor(2,2);
    switch(current_auton_selection){
      case 0:
        Brain.Screen.printAt(5, 140, "Negative Corner Blue");
        Controller.Screen.print("Negative Corner Blue");
        break;
      case 1:
        Brain.Screen.printAt(5, 140, "Positive Corner Blue");
        Controller.Screen.print("Positive Corner Blue");
        break;
      case 2:
        Brain.Screen.printAt(5, 140, "Negative Corner Red");
        Controller.Screen.print("Negative Corner Red");  
        break;
      case 3:
        Brain.Screen.printAt(5, 140, "Positive Corner Red");
        Controller.Screen.print("Positive Corner Red");
        break;
      case 4:
        Brain.Screen.printAt(5, 140, "Auton 5");
        break;
      case 5:
        Brain.Screen.printAt(5, 140, "Auton 6");
        break;
      case 6:
        Brain.Screen.printAt(5, 140, "Auton 7");
        break;
      case 7:
        Brain.Screen.printAt(5, 140, "Auton 8");
        break;
    }
    if(Brain.Screen.pressing()){
      while(Brain.Screen.pressing()) {}
      current_auton_selection ++;
    } else if (current_auton_selection == 8){
      current_auton_selection = 0;
    }
    task::sleep(10);
  }

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/



void testing(void)
{
wait(2500,msec);
  PositiveCornerBlue();

}

void autonomous(void) {
  auto_started = true;
  switch(current_auton_selection){ 
    case 0:
      NegativeCornerBlue();
      break;
    case 1:         
      PositiveCornerBlue();
      break;
    case 2:
      NegativeCornerRed();
      break;
    case 3:
      PositiveCornerRed();
      break;
    case 4:
      full_test();
      break;
    case 5:
      odom_test();
      break;
    case 6:
      tank_odom_test();
      break;
    case 7:
      holonomic_odom_test();
      break;
 }
  
  odom_test();
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {

  Lift.setVelocity(100,percent);


  Take.setVelocity(100,percent);
  
  float SpeedWhileLifting = 1;

  task IntakeAction(IntakeAction::JoyControl);
  

  while(1)
  {
    if(Lift.position(degrees) > 700)
      SpeedWhileLifting = 0.65;
    
    else 
      SpeedWhileLifting = 1;


      
    if(abs(Controller.Axis3.position()) > 30 )
      LeftDriveSmart.spin(fwd,(Controller.Axis3.position())*SpeedWhileLifting,pct);

    else
      LeftDriveSmart.stop(coast);

    if(abs(Controller.Axis2.position()) > 30 )
      RightDriveSmart.spin(fwd,(Controller.Axis2.position())*SpeedWhileLifting,pct);

    else
      RightDriveSmart.stop(coast);


    



    if(Controller.ButtonLeft.pressing())
      Intake.set(true);
    
    if(Controller.ButtonRight.pressing())
      Intake.set(false);

    // if(Controller.ButtonX.pressing())
    //   {
    //     Intake_Action_Mogo();
    //   }

    // if(Controller.ButtonY.pressing())
    // {
    //   Intake_Action_Reset();
    // }


  wait(20,msec);

  }

}


//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
