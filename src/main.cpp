#include "vison.h"

competition Match;

// Code for robot setup
void pre_auton( void )
{
  Gyro.calibrate();
  while ( Auto1 == false || Auto2 == false || Auto3 == false || Auto4 == false )
  if ( Con1.ButtonA.pressing() )
  {
    Auto1 = true;
  }
  else if ( Con1.ButtonB.pressing() )
  {
    Auto2 = true;
  }
  else if ( Con1.ButtonX.pressing() )
  {
    Auto3 = true;
  }
  else if ( Con1.ButtonY.pressing() )
  {
    Auto4 = true;
  }
  wait ( 100, msec );
}

// Code for Autonomous Control period
void auton ( void )
{
  if ( Auto1 == true )
  {
    Rolling ( 50, true, 1000 );
    MoveFwdDeg ( 100, -8, 0, true );
    TurnRDeg ( 30, 90 );
    MoveFwdDeg ( 200, -120, 0, true);
    Intaking ( -200, false, 5000 );
    MoveFwdDeg ( 100, 80, 0, true );
    Intake.stop();
    TurnLDeg( 30, 90 );

    /*TurnRDeg ( 30, 45 );
    MoveFwdDeg ( 100, 24, 0, true);
    Rolling ( 50, true, 1000 );
    MoveFwdDeg ( 100, -12, 0, true);
    TurnLDeg ( 30, 90 );
    MoveFwdDeg ( 200, -128, 0, true);
    Intaking ( -100, true, 5000 );*/

  }
  if ( Auto2 == true )
  {
    MoveFwdDeg ( 100, 0, -40, true);
    MoveFwdDeg ( 100, 8, 0, true);
    Rolling (50, true, 1000 );
    MoveFwdDeg ( 200, -8, 0, true );
    TurnLDeg ( 30, 90 );
    MoveFwdDeg ( 100, -120, 0, true );
    Intaking ( -200, false, 5000 );
    MoveFwdDeg ( 100, 80, 0, true );
    Intake.stop();

  }
  if ( Auto3 == true )
  {
    MoveFwdDeg ( 100, 4, 0, true );
    Rolling ( 200, true, 1000 );
    MoveFwdDeg ( 100, -8, 0, true );
    TurnLDeg ( 30, 90 );
    MoveFwdDeg ( 200, -120, 0, true);
    MoveFwdDeg ( 200, 0, -240, true );
    MoveFwdDeg ( 100, 12, 0, true );
    Intaking ( 50, true, 1000 );
    TurnRDeg( 30, 90 );
    MoveFwdDeg ( 200, 60, 0, true );
    Flying( 600, false, 1 );
    wait ( 5000, msec );
    Intaking ( 200, false, 1 );
  }
  if ( Auto4 == true)
  {

  }
}

// Code for User Control period
void user ( void )
{
  SetMec ( coast );

  float
  Y1Thres, X1Thres, R1Thres;

  while (true)
  {
    // Drivetrain
    Y1Thres = Con1.Axis3.position ( pct ),
    X1Thres = Con1.Axis4.position ( pct ),
    R1Thres = Con1.Axis1.position ( pct );
    MecSpin ( Y1Thres, X1Thres, R1Thres );

    // Intake
    IntakeSpin();

    // Flywheel
    FlySpin();

    // Rollers
    RollSpin();

    wait ( coolDown, msec );
  }
}


int main ()
{
  Con1.ButtonL2.pressed(IntakeF);
  Con1.ButtonL1.pressed(IntakeR);
  Con1.ButtonR2.pressed(FlyF);
  Con1.ButtonR1.pressed(FlyS);
  Con1.ButtonY.pressed(RollF);
  Con1.ButtonRight.pressed(RollR);

  vexcodeInit ();

  Match.autonomous ( auton );
  Match.drivercontrol ( user );

  pre_auton ();

  while ( true )
  {
    wait ( 100, msec );
  }
}
