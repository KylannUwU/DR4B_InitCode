#include "vex.h"
#include "robot_config.h"

#define RED false
#define Blue true
#define NegativeCorner false
#define PositiveCorner true

#define Alliance RED
#define Side PositiveCorner

void SetMaxSpeed()
{
    Lift.setVelocity(100,percent);
    Take.setVelocity(100,percent);

}
void SetTimeOuts(int Time, int Time2 = -1)
{
    if(Time2 == -1)
    {

        Time2 = Time;
    }

    Lift.setTimeout(Time,msec);
    Take.setTimeout(Time2,msec);
}


// int StealMoGo()
// {
//     SetTimeOuts(1500);
//     Lift.setVelocity(100,percent);
//     Take.setVelocity(100,percent);
//     Lift.spinToPosition(1000,degrees,false);
//     Take.spinToPosition(-400,degrees);
//     wait(1000,msec);
//     Lift.spinToPosition(400,deg);
//     wait(500,msec);
//     Lift.spinToPosition(1000,degrees);
    
// return(0);
// }



int IntakeInside()
{
    SetTimeOuts(500);
    Take.spin(forward,70,percent);
    Lift.spinToPosition(300,degrees);
    Intake.set(true);
    Lift.spinToPosition(900,degrees);
        SetTimeOuts(1000);
    Take.spinToPosition(-430,deg,false);
    while(Lift.torque(InLb) < 4 )
        Lift.spin(vex::directionType::rev);
    Take.stop(hold);
    Take.spinFor(forward,30,deg);
    return 0;
}


int TakeFromFloor()
{
    SetTimeOuts(1300);
    IntakeAction::Mogo();
            SetTimeOuts(1000);        
    Take.spinToPosition(-440,deg,false);
    while(Lift.torque(InLb) < 4 )
        Lift.spin(vex::directionType::rev);
    Lift.stop(coast);
    Take.stop(hold);
    Take.spinFor(forward,30,deg);
    return 0;
}

int TakeMogo()
{
    waitUntil(Chassis.get_left_position_in() >= 30);
    MoGo.set(true);
    return 0;
}


int LastTake()
{
       // Intake_Action_Take();
    Intake.set(false);
//  Take.spinToPosition(-350, degrees);
    Lift.setTimeout(2500, msec);
    Lift.spinToPosition(700, degrees);
    Lift.spinToPosition(900, degrees, false);
    Take.spinToPosition(0, degrees);
    Take.spin(fwd,70,percent);
    Lift.spinToPosition(400, degrees);
    Intake.set(true);
    Lift.spinFor(fwd, 500, degrees);
     Take.stop();
    return 0;
}



int TakeMid()
{
    SetTimeOuts(1800);
    Lift.spinToPosition(0,degrees);
    Take.spinToPosition(-400,degrees);
    Intake.set(false);
    Take.spinToPosition(-150,degrees);
    Lift.spinToPosition(1100,degrees);

    return 0;
}

// AUTONS

void PositiveCornerBlue()
{
    SetMaxSpeed();
    Lift.spinToPosition(800,degrees,false);
    wait(300,msec);
    task mogo1(TakeMogo);
    Chassis.drive_distance(42);
    wait(50,msec);
    Chassis.drive_with_voltage(0,0);
    wait(200,msec);
    Chassis.drive_distance(-8);
    Chassis.turn_to_angle(270);
    task Preload(IntakeInside);
    wait(1800,msec);
    Chassis.drive_distance(18);
    task Taking1(LastTake);
    wait(1400,msec);
    Chassis.turn_to_angle(305);
    MoGo.set(false);
    Chassis.drive_distance(-30);
    Chassis.turn_to_angle(110);
    Chassis.drive_distance(6);
    TakeMid();
    Chassis.drive_distance(8);
    Chassis.left_swing_to_angle(180);
    Chassis.drive_with_voltage(9,9);
    wait(600,msec);
    Chassis.drive_with_voltage(6,6);
    Lift.spinToPosition(700,degrees);
    Intake.set(true);
    Lift.spinToPosition(1100,degrees);
    Chassis.drive_with_voltage(-12,-12);
    wait(1000,msec);
}



void NegativeCornerBlue()
{
    SetMaxSpeed();
    Lift.spinToPosition(800,degrees,false);
    wait(300,msec);
    task mogo1(TakeMogo);
    Chassis.drive_distance(42);
    wait(50,msec);
    Chassis.drive_with_voltage(0,0);
    wait(200,msec);
    Chassis.drive_distance(-8);
    Chassis.turn_to_angle(90);
    task Preload(IntakeInside);
    wait(2100,msec);
    Chassis.drive_distance(18);
    task Taking1(TakeFromFloor);
    wait(1700,msec);
    Chassis.turn_to_angle(0);
    wait(200,msec);
    Chassis.drive_distance(8);
    task Taking2(LastTake);
    wait(100,msec);
    Chassis.drive_distance(-10);
    wait(1500,msec);
    Chassis.turn_to_angle(95);
    MoGo.set(false);
    Chassis.drive_with_voltage(-12,-12);
    wait(500,msec);
    Chassis.drive_with_voltage(-5,-5);
    wait(2000,msec);
}




void PositiveCornerRed()
{
  SetMaxSpeed();
    Lift.spinToPosition(800,degrees,false);
    wait(300,msec);
    task mogo1(TakeMogo);
    Chassis.drive_distance(42);
    wait(50,msec);
    Chassis.drive_with_voltage(0,0);
    wait(200,msec);
    Chassis.drive_distance(-8);
    Chassis.turn_to_angle(90);
    task Preload(IntakeInside);
    wait(1800,msec);
    Chassis.drive_distance(18);
    task Taking1(LastTake);
    wait(1400,msec);
    Chassis.turn_to_angle(55);
    MoGo.set(false);
    Chassis.drive_distance(-30);
    Chassis.turn_to_angle(250);
    Chassis.drive_distance(6);
    TakeMid();
    Chassis.left_swing_to_angle(200);
    Chassis.drive_with_voltage(12,12);
    wait(600,msec);
    Chassis.drive_with_voltage(6,6);
    Lift.spinToPosition(700,degrees);
    Intake.set(true);
    Lift.spinToPosition(1100,degrees);
    Chassis.drive_with_voltage(-12,-12);
    wait(1000,msec);
}

void NegativeCornerRed()
{
SetMaxSpeed();
    Lift.spinToPosition(800,degrees,false);
    wait(300,msec);
    task mogo1(TakeMogo);
    Chassis.drive_distance(42);
    wait(50,msec);
    Chassis.drive_with_voltage(0,0);
    wait(200,msec);
    Chassis.drive_distance(-8);
    Chassis.turn_to_angle(270);
    task Preload(IntakeInside);
    wait(2100,msec);
    Chassis.drive_distance(18);
    task Taking1(TakeFromFloor);
    wait(1700,msec);
    Chassis.turn_to_angle(0);
    wait(200,msec);
    Chassis.drive_distance(8);
    task Taking2(LastTake);
    wait(100,msec);
    Chassis.drive_distance(-10);
    wait(1500,msec);
    Chassis.turn_to_angle(265);
    MoGo.set(false);
    Chassis.drive_with_voltage(-12,-12);
    wait(500,msec);
    Chassis.drive_with_voltage(-5,-5);
    wait(2000,msec);
}

void RedStakePos()
{
    SetTimeOuts(2000);
    Lift.spinToPosition(1100,deg);
    Take.spinToPosition(-400,deg);
    Lift.spinToPosition(900,deg);
    Intake.set(true);
    Lift.spinToPosition(1100,deg);
}


void Skills1()
{
    wait(2000,msec);
    SetMaxSpeed();
    RedStakePos();
    Chassis.drive_distance(-5);
    IntakeAction::Taking;
    wait(2000,msec);
    //Pos to redstake
    //release ring and bring back
    Chassis.drive_distance(-10);
    Chassis.turn_to_angle(90);
    Chassis.drive_distance(26);
    //Take mogo
    IntakeAction::Taking();
    Chassis.drive_distance(8);
    TakeFromFloor();
    Chassis.drive_distance(8);
    TakeFromFloor();
    Chassis.turn_to_angle(180);
    Chassis.drive_distance(24);
    TakeFromFloor();
    Chassis.turn_to_angle(155);
    Chassis.drive_distance(12);
    //Take and raise
    Chassis.turn_to_angle(90);
    Chassis.drive_distance(10);
    //Inside and release mogo
    Chassis.drive_distance(-10);
    Chassis.turn_to_angle(135);
    Chassis.drive_distance(-60);
    Chassis.turn_to_angle(270);
    Chassis.drive_distance(24);
    //Take mogo
    Chassis.drive_distance(10);
    TakeFromFloor();
    Chassis.drive_distance(10);
    TakeFromFloor();
    Chassis.turn_to_angle(180);
    Chassis.drive_distance(24);
    TakeFromFloor();
    Chassis.turn_to_angle(205);
    Chassis.drive_distance(12);
    //Takeandraise
    Chassis.turn_to_angle(270);

    
    


}