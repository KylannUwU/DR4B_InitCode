#include "vex.h"
#include "robot_config.h"


using namespace std;
using namespace vex;



bool DropStake = false;
bool ControlIntakeValue = true;


void IntakeAction::Taking()
{
    // if(Intake.value() == false) 
    // {
    //     Intake.set(true);
    //     wait(200,msec);
    // }
    
    // else
    Intake.set(true);
    Take.setTimeout(800,msec);
    Take.spinToPosition(-450,degrees);
    Take.spinFor(fwd,20,deg);
}

void IntakeAction::Reset()
{
    while(Take.torque(InLb) < 2.46 )
        Take.spin(vex::directionType::fwd);
    Take.stop();

    while(Lift.torque(InLb) < 4 )
        Lift.spin(vex::directionType::rev);
    Lift.stop();

}

void IntakeAction::Mogo()
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
    Take.spinToPosition(-150, degrees, false);
    Take.spinToPosition(-400, degrees, false);
    Lift.spinToPosition(0, degrees);
    Lift.stop(coast);
   Take.spinFor(fwd,10,deg);
}


void IntakeAction::LiftToHighStake()
{
    //Intake_Action_Take();
    Lift.setTimeout(10,seconds);
    Lift.spinToPosition(1500,degrees);
    Take.spinToPosition(-180,degrees);   
    DropStake = true;
}

void IntakeAction::DropOnStake()
{
    Lift.spinFor(fwd,-600,degrees);
//    Take.spinToPosition(-460,degrees,false);
    Intake.set(true);
    Lift.spinFor(fwd,650,degrees);
    Take.spinToPosition(-100,degrees);
    DropStake = false;
}

void IntakeAction::AllianceStake()
{
    //Intake_Action_Take();
    Lift.setTimeout(5,seconds);
    Lift.spinToPosition(1000,degrees);
    Take.spinToPosition(-180,degrees);
    DropStake = true;    
}



void IntakeAction::TakeMoGo()
{
    Lift.spinToPosition(800,degrees);
    Take.spinToPosition(10,degrees);
    MoGo.set(false);
}


void IntakeAction::GrabMoGo()
{
    MoGo.set(true);
    Taking();
}

bool SmartActionState = false;

void SmartActions()
{
    if(Controller.ButtonB.pressing() )
    {
        SmartActionState = !SmartActionState;       
    }
}

bool BtnPressed = false;
int counter = 0;

int IntakeAction::JoyControl() 
{
    while (1) {

        if(SmartActionState)
        {
        
            if (Controller.ButtonR2.pressing())
            {
                if(DropStake)
                    DropOnStake();
                else    
                    Taking();
            }

            if(Controller.ButtonR1.pressing() )
                Mogo();
        
            if(Controller.ButtonL1.pressing())
                {
                
                if(counter == 0)
                {
                    AllianceStake();
                    counter = 1;
                }
                
                else if(counter == 1)
                {
                    LiftToHighStake();
                    counter = 2;
                }
                else if (counter == 2)
                {                
                    Reset();
                    counter = 0;
                }
            }

            if (Controller.ButtonL2.pressing())
            {
                Reset();
                counter = 0;   
            }


                
            if(Controller.ButtonUp.pressing())
                GrabMoGo();
        
            if(Controller.ButtonDown.pressing())
                TakeMoGo();
                            
        }

        else
        {
            if (Controller.ButtonR1.pressing())
                Take.spin(fwd, 100, pct);
    
            else if(Controller.ButtonR2.pressing())
                Take.spin(fwd, -100, pct);
            
            else
                Take.stop(hold);

        

      

       
        
        if(Controller.ButtonL1.pressing())
            Lift.spin(fwd,100,pct);

        else if (Controller.ButtonL2.pressing())
        {
  
                Lift.spin(fwd,-100,pct);
        }
        else
            Lift.stop(hold);


        wait(20, msec); // Espera para permitir la ejecución de otras tareas y operaciones

        if(Lift.position(deg) < 300)
            DropStake = false;

        if(Controller.ButtonUp.pressing())
                MoGo.set(true);
        
        if(Controller.ButtonDown.pressing())
                MoGo.set(false);

        }


        // ACTIVATE OR DEACTIVATE SMART ACTIONS 

        if(Controller.ButtonB.pressing())
        {
            if(!BtnPressed)
            {
            SmartActions();
            BtnPressed = true;
            }   

        }

        if(!Controller.ButtonB.pressing() && BtnPressed)
            BtnPressed = false;
        

    }

    return 0;
}




