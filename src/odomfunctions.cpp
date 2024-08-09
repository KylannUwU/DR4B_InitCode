
#include <robot_config.h>






/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  Chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  Chassis.set_heading_constants(6, .4, 0, 1, 0);
  Chassis.set_turn_constants(12, .4, .03, 3, 15);
  Chassis.set_swing_constants(12, .3, .001, 2, 15);


  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  Chassis.set_drive_exit_conditions(1.5, 300, 5000);
  Chassis.set_turn_exit_conditions(1, 300, 3000);
  Chassis.set_swing_exit_conditions(1, 300, 3000);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */

void odom_constants(){
  default_constants();
  Chassis.heading_max_voltage = 10;
  Chassis.drive_max_voltage = 8;
  Chassis.drive_settle_error = 3;
  Chassis.boomerang_lead = .5;
  Chassis.drive_min_voltage = 0;
}

/**
 * The expected behavior is to return to the start position.
 */

void drive_test(){
  Chassis.drive_distance(6);
  Chassis.drive_distance(12);
  Chassis.drive_distance(18);
  Chassis.drive_distance(-36);
}

/**
 * The expected behavior is to return to the start angle, after making a complete turn.
 */

void turn_test(){
  Chassis.turn_to_angle(5);
  Chassis.turn_to_angle(30);
  Chassis.turn_to_angle(90);
  Chassis.turn_to_angle(225);
  Chassis.turn_to_angle(0);
}

/**
 * Should swing in a fun S shape.
 */

void swing_test(){
  Chassis.left_swing_to_angle(90);
  Chassis.right_swing_to_angle(0);
}

/**
 * A little of this, a little of that; it should end roughly where it started.
 */

void full_test(){
  Chassis.drive_distance(24);
  Chassis.turn_to_angle(-45);
  Chassis.drive_distance(-36);
  Chassis.right_swing_to_angle(-90);
  Chassis.drive_distance(24);
  Chassis.turn_to_angle(0);
}

/**
 * Doesn't drive the robot, but just prints coordinates to the Brain screen 
 * so you can check if they are accurate to life. Push the robot around and
 * see if the coordinates increase like you'd expect.
 */

void odom_test(){
  Chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", Chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", Chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", Chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", Chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", Chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

/**
 * Should end in the same place it began, but the second movement
 * will be curved while the first is straight.
 */

void tank_odom_test(){
  odom_constants();
  Chassis.set_coordinates(0, 0, 0);
  Chassis.turn_to_point(24, 24);
  Chassis.drive_to_point(24,24);
  Chassis.drive_to_point(0,0);
  Chassis.turn_to_angle(0);
}

/**
 * Drives in a square while making a full turn in the process. Should
 * end where it started.
 */

void holonomic_odom_test(){
  odom_constants();
  Chassis.set_coordinates(0, 0, 0);
  Chassis.holonomic_drive_to_pose(0, 18, 90);
  Chassis.holonomic_drive_to_pose(18, 0, 180);
  Chassis.holonomic_drive_to_pose(0, 18, 270);
  Chassis.holonomic_drive_to_pose(0, 0, 0);
}



