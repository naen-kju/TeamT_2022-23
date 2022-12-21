#include "vex.h"

/*  FUNCTIONS FOR FUNCTIONS
*/
  void MecSpin ( float Y, float X, float R )
  {
    LF.spin ( fwd, Y + X + R, pct );
    LB.spin ( fwd, Y - X + R, pct );
    RF.spin ( fwd, Y - X - R, pct );
    RB.spin ( fwd, Y + X - R, pct );
  }
  void SetMec ( brakeType type )
  {
    LF.setBrake ( type );
    LB.setBrake ( type );
    RF.setBrake ( type );
    RB.setBrake ( type );
  }
  float Clip( float value, float min, float max )
  {
    if(value > max)
    {   return max; }
    else if(value < min)
    {   return min; }
    return value;
  }

/*  FUNCTIONS FOR USERCONTROL
*/
  int intRollSpeed = 0;
  void IntRolling () 
  {
    while (Con1.ButtonL2.pressing())
    {
      if (intRollSpeed < 0)
      {
        intRollSpeed = 0;
      }
      else
      {
        intRollSpeed += 50;
      }
      IntRoll.spin(fwd, intRollSpeed, pct);
      wait (150, msec);
    }
    while (Con1.ButtonL1.pressing())
    {
      if (intRollSpeed > 0)
      {
        intRollSpeed = 0;
      }
      else if ( intRollSpeed > -100)
      {
        intRollSpeed -= 50;
      }
      else
      {
        intRollSpeed = -100;
      }
      IntRoll.spin(fwd, intRollSpeed, pct);
      wait (150, msec);
    }
  }

  int flySpeed = 0;
  void FlySpinning()
  {
    while (Con1.ButtonR2.pressing())
    {
      if (flySpeed == 0)
      {
        flySpeed = 50;
      }
      else
      {
        flySpeed += 5;
      }
      FlyW.spin(fwd, flySpeed, pct);
      wait (150, msec);
    }
    while (Con1.ButtonR1.pressing())
    {
      flySpeed = 0;
      FlyW.stop();
      wait (150, msec);
    }
  }
  

  void Indexer()
  {
    while (Con1.ButtonA.pressing())
    {
      Index.spinFor ( fwd, 180, deg, 150, rpm );
      wait(250, msec);
    }
  }

  void Expansion()
  {
    wait(1000, msec);
    if ( Con1.ButtonB.pressing() )
    {
      expand0.set(true);
      expand1.set(true);
    }
  }

/*  FUNCTIONS FOR AUTON
*/
  void MoveFwdDeg ( float vel, float Y, float X, bool next )
  {
    const float
    driveGR = 1,
    wheelDia = 4,
    wheelCirc = wheelDia * M_PI;

    float rY = ((Y/wheelCirc)*driveGR)*360;
    float rX = ((X/wheelCirc)*driveGR)*360;
    LF.spinFor( fwd, rY + rX, deg, vel, rpm, false );
    RF.spinFor( fwd, rY - rX, deg, vel, rpm, false );
    LB.spinFor( fwd, rY - rX, deg, vel, rpm, false );
    RB.spinFor( fwd, rY + rX, deg, vel, rpm, next );
  }
  void TurnRDeg ( float vel, float degr )
  {
    SetMec ( hold );
    while ( Gyro.rotation( deg) - degr <= 0 )
    {
      MecSpin ( 0, 0, vel );
      wait (5.0, msec);
    }
    MecSpin ( 0, 0, 0 );
    Gyro.resetRotation();
  }
  void TurnLDeg ( float vel, float degr )
  {
    SetMec ( hold );
    while ( Gyro.rotation( deg) + degr >= 0 )
    {
      MecSpin ( 0, 0, -vel );
      wait ( 5.0, msec );
    }
    MecSpin ( 0, 0, 0 );
    Gyro.resetRotation();
  }
  void Flying ( float Vel, bool Stop, float Time )
  {
    FlyW.spin(fwd, Vel, pct);
    if ( Stop == true)
    {
      wait ( Time, msec );
      FlyW.stop();
    }
  }
  void Intaking ( float Vel, bool Stop, float Time )
  {
    IntRoll.spin ( fwd, Vel, rpm );
    if ( Stop == true )
    {
      wait ( Time, msec );
      IntRoll.stop();
    }
  }
  void Rolling( float vel, float time, directionType dir )
  {
    IntRoll.spin(dir, vel, pct );
    wait ( time, msec );
    IntRoll.stop();
  }
  void RollingCB( float vel )
  {
    Rolling( 30, 500, reverse );
    Colour.setLightPower(25);
    wait (250, sec );
    IntRoll.spin(fwd, vel, pct);
    while ( Colour.color() == red )
    {
      wait ( 5.0, msec);
    }    
    IntRoll.stop();
  }
  void RollingCR( float vel )
  {
    Rolling( 30, 500, reverse );
    Colour.setLightPower(25);
    wait (250, sec );
    IntRoll.spin(fwd, vel, pct);
    while ( Colour.color() == blue )
    {
      wait ( 5.0, msec);
    }    
    IntRoll.stop();
  }

/*  FUNCTIONS FOR MAIN.CPP
*/
  void mainusercall()
  {
    Con1.ButtonB.pressed(Expansion);
  }

  int conAuton ()
  {
    int AutoNum = 0;

    while ( AutoNum == 0 )
    {
      if ( Con1.ButtonUp.pressing() ) // Match Blue Left
      {
        AutoNum = 1;
      }
      else if ( Con1.ButtonRight.pressing() ) // Match Blue Right
      {
        AutoNum = 2;
      }
      else if ( Con1.ButtonDown.pressing() ) // Match Red Left
      {
        AutoNum = 3;
      }
      else if ( Con1.ButtonLeft.pressing() ) // Match Red Right
      {
        AutoNum = 4;
      }
      else if ( Con1.ButtonX.pressing() ) // Skills Left
      {
        AutoNum = 5;
      }
      else if ( Con1.ButtonA.pressing() ) // Skills Right
      {
        AutoNum = 6;
      }
      else if ( Con1.ButtonB.pressing() ) // Testing
      {
        AutoNum = 7;
      }
      else if ( Con1.ButtonY.pressing() ) // NaN
      {
        AutoNum = 8;
      }
      wait (5.0, msec);
    }
    return AutoNum;
  }

  void autoncall()
  {
    int AutoNum = conAuton();
    if ( AutoNum == 1 ) // Match Blue Left Button Up
    {
      Colour.setLightPower(25);
      MoveFwdDeg(75, -2, 0, true );
      Rolling( 30, 500, reverse );
      RollingCB(20);
      MoveFwdDeg(75, 4, 0, true );
      TurnRDeg(50, 45);
      FlyW.spin(fwd, 60, pct);
      MoveFwdDeg(125, 50, 0 , true );
      TurnLDeg(30, 80);
      MoveFwdDeg(75, 10, 0 , true );
      wait ( 2000, msec );
      Index.spinFor(fwd, 180, deg, 150, rpm); wait( 1250, msec );
      Index.spinFor(fwd, 180, deg, 150, rpm); wait( 1000, msec );
      FlyW.stop();

    }

    else if ( AutoNum == 2 ) // Match Blue Right Button Right
    {
      Colour.setLightPower(25);
      MoveFwdDeg ( 50, 0, 29, true);
      MoveFwdDeg(75, -8, 0, true );
      Rolling( 30, 500, reverse );
      RollingCB(20);
      MoveFwdDeg(75, 4, 0, true );
      TurnLDeg(50, 45);
      FlyW.spin(fwd, 60, pct);
      MoveFwdDeg(125, 50, 0 , true );
      TurnRDeg(30, 70);
      wait ( 2000, msec );
      Index.spinFor(fwd, 180, deg, 150, rpm); wait( 1250, msec );
      Index.spinFor(fwd, 180, deg, 150, rpm); wait( 1000, msec );
      FlyW.stop();
    }

    else if ( AutoNum == 3 ) // Match Red Left Button Down
    {
      Colour.setLightPower(25);
      MoveFwdDeg(75, -2, 0, true );
      Rolling( 30, 500, reverse );
      RollingCR(20);
      MoveFwdDeg(75, 4, 0, true );
      TurnRDeg(50, 45);
      FlyW.spin(fwd, 67, pct);
      MoveFwdDeg(125, 50, 0 , true );
      TurnLDeg(30, 80);
      MoveFwdDeg(75, 10, 0 , true );
      wait ( 2000, msec );
      Index.spinFor(fwd, 180, deg, 150, rpm); wait( 1250, msec );
      Index.spinFor(fwd, 180, deg, 150, rpm); wait( 1000, msec );
      FlyW.stop();
    }

    else if ( AutoNum == 4) // Match Red Right
    {
      Colour.setLightPower(25);
      MoveFwdDeg ( 50, 0, 29, true);
      MoveFwdDeg(75, -8, 0, true );
      Rolling( 30, 500, reverse );
      RollingCR(20);
      MoveFwdDeg(75, 4, 0, true );
      TurnLDeg(50, 45);
      FlyW.spin(fwd, 67, pct);
      MoveFwdDeg(125, 50, 0 , true );
      TurnRDeg(30, 70);
      wait ( 2000, msec );
      Index.spinFor(fwd, 180, deg, 150, rpm); wait( 1250, msec );
      Index.spinFor(fwd, 180, deg, 150, rpm); wait( 1000, msec );
      FlyW.stop();
    }

    else if ( AutoNum == 5 ) // Skills Left
    {
      // BLANK
    }

    else if ( AutoNum == 6 ) // Skills Right
    {
      // BLANK
    }

    else if ( AutoNum == 7 ) // Test code
    {
      // BLANK
    }

    else if ( AutoNum == 8 ) // NaN
    {
      // BLANK
    }
  }

  void usercall()
  {
    SetMec ( coast );
    while (true)
    {
      int 
      Y1Thres = Con1.Axis3.position ( pct ),
      X1Thres = Con1.Axis4.position ( pct ),
      R1Thres = Con1.Axis1.position ( pct );
      MecSpin ( Y1Thres, X1Thres, R1Thres );
      IntRolling();
      FlySpinning();
      wait ( 5, msec );
    }
  }

  void preautoncall()
  {
    vexcodeInit();

    // Only allows color dection from optical
    Colour.gestureDisable();

    // Takes 3 seconds to calibrate inertial
    Gyro.calibrate();

    expand0.set(false);
    expand1.set(false);

    // Prints out auton selection on brain and enables auton selection thru controller 
    conAuton();
  }

  