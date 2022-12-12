#include "vex.h"

/*----------------------------------/
---Global Variables for functions----
/----------------------------------*/
  const float

    // Sets the gear ratio for the drivetrain
    driveGR = 1,

    // Sets the wheels' diameter (4 inches)
    wheelDia = 4,

    // Sets the wheels' circumfrence based on diameter
    wheelCirc = wheelDia * M_PI,

    // Finds the radians from degrees
    Deg2Rad = M_PI/180,

    // Finds the degrees from radians
    Rad2Deg = 180/M_PI,

    // Time for wait in msec, used to save resources between other functions
    coolDown = 5.0;

  float
    // Set up 3 axis control for mecanum drivetrain
    // Y: fwd & rev, X: Strafe left & right, R: Turn clockwise & counter
    Y1Thres, X1Thres, R1Thres,

    // Set initial speed for flywheel control for driver
    FlySpeed = 0,

    // Set initial speed for Intake control for driver
    IntRollSpeed = 0;

  bool
    // For optical sensor and rollers, will roll until blue for true, roll until red for false
    RollerBlue = true,
    
    // Enables optical sensor + roller combination for driver control
    RollerOn = false;

  // Initialization for showing different auton names when selected on brain
  std::string AutonName;

  int
  // Initialization to setup different autons
  AutoNum = 0;


  bool program = false;

/*----------------------------------/
------General functions for all------
/----------------------------------*/
  // Control for spinning in mecanum directions
  void MecSpin ( float Y, float X, float R )
  {
    LF.spin ( fwd, Y + X + R, pct );
    LB.spin ( fwd, Y - X + R, pct );
    RF.spin ( fwd, Y - X - R, pct );
    RB.spin ( fwd, Y + X - R, pct );
  }

  // Sets the brake type for the four drivetrain motors
  void SetMec ( brakeType type )
  {
    LF.setBrake ( type );
    LB.setBrake ( type );
    RF.setBrake ( type );
    RB.setBrake ( type );
  }

  // Sets the braking type for flywheel motor group
  void SetFly ( brakeType type )
  {
    FlyW.setStopping ( type );
  }

  // Sets the braking type for the Intake/Roller motor
  void SetInt ( brakeType type )
  {
    IntRoll.setBrake ( type );
  }

  // Locks a set value or variable to a minimum and maximum
  float Clip( float value, float min, float max )
  {
  if(value > max)
  {   return max; }
  else if(value < min)
  {   return min; }
  return value;
  }

/*----------------------------------/
-----Functions for void pre-auton----
/----------------------------------*/
  // Allows for auton selection thru controller buttons
  // Uses all face buttons
  // Sets the auton to a different value when different button is pressed
  void conAuton ()
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
  }

  void conWaitAuton()
  {
    while ( AutoNum == 0 )
    {
      conAuton();
      wait (coolDown, msec);
    }
    program = true;
  }

  void nameAuton()
  {
     if (AutoNum == 1)
    {
      AutonName = "Match Blue Left";
      RollerBlue = true;
    }
    else if (AutoNum == 2)
    {
      AutonName = "Match Blue Right";
      RollerBlue = true;      
    }
    else if (AutoNum == 3)
    {
      AutonName = "Match Red Left";
      RollerBlue = false;
    }
    else if (AutoNum == 4)
    {
      AutonName = "Match Red Right";
      RollerBlue = false;
    }
    else if (AutoNum == 5)
    {
      AutonName = "Skills Left";
      RollerBlue = true;
    }
    else if (AutoNum == 6)
    {
      AutonName = "Skills Right";
      RollerBlue = true;
    }
    else if (AutoNum == 7)
    {
      AutonName = "Testing";
    }
    else if (AutoNum == 8)
    {
      AutonName = "NaN";
    }
  }

  void printAuton ()
  {
    std::string 
      CurrA = "Current Auton: ";

    int 
      x1 = 5,
      y1 = 50,
      x2 = 50,
      y2 = 175,

      spacing = 60,
      rect = 8,

      x,
      y;

      color 
        selectA1 = red,
        selectA0 = blue,
        currCol;

    Cortex.Screen.setPenColor ( white );

    Cortex.Screen.setFont ( monoM );

    for ( int i = 0; i < rect; i++ ) 
    {
      if ( i + 1 == AutoNum ) 
      {
        currCol = selectA1;
      } 
      else 
      {
        currCol = selectA0;
      }

      Cortex.Screen.setPenColor ( currCol );
      Cortex.Screen.drawRectangle ( x1 + ( spacing * i ), y1, x2, y2, currCol);
    }

    while (true)
    {
      while (Cortex.Screen.pressing())
      {
        x = Cortex.Screen.xPosition (),
        y = Cortex.Screen.yPosition ();
      }
      

      if ( y > y1 && y < y1+y2 )
      {
        for ( int i = 0; i < rect; i++ )
        {
          if ( x > x1 + (spacing * i) && x < x2 * (i + 1) )
          {
            AutoNum = 1 + i;
          }
        }

        std::string CombAuton = CurrA.append(AutonName);

        const char * str = CombAuton.c_str();

        nameAuton();
        conAuton();
        Cortex.Screen.printAt(5, 30, str );
        wait ( coolDown, msec );
      }
    }
  }

  void printAuton2()
  {
    int 
      x1 = 5,
      x2 = 50,
      y1 = 50,
      y2 = 175,
      rect = 8;

    for ( int i; i < 8; i++ )
    {
      Cortex.Screen.setPenColor(blue);
      Cortex.Screen.drawRectangle( x1+(60*i), y1, x2, y2, blue );
    }

    while (true)
    {
      int 
        x = Cortex.Screen.xPosition(),
        y = Cortex.Screen.yPosition();

      for ( int i = 0; i < rect; i++ )
      {
        if ( x1+(60*i) < x && x < (60*(i+1))-5 )
        {
          AutoNum = i + 1;
        }
      }
      wait ( coolDown, msec);
    } 

  }

/*----------------------------------/
-------Functions for void user-------
/----------------------------------*/
  // Switches fwd to opposite of current, and rev to off for intake spin when called
  void IntRollF ()
  {
    RollerOn = false;

    while (Con1.ButtonL2.pressing())
    {
      if ( IntRollSpeed < 0 )
      {
        IntRollSpeed = 0;
        wait ( 250, msec );
      }
      else 
      {
        IntRollSpeed += 50;
        wait ( 250, msec );
      }
      wait ( coolDown, msec );
    }
  }
  // Switches rev to opposite of current, and fwd to off for intake spin when called
  void IntRollR ()
  {
    RollerOn = false;
  
    while (Con1.ButtonL1.pressing())
    {
      if ( IntRollSpeed > 0 )
      {
        IntRollSpeed = 0;
        wait ( 250, msec );
      }
      else 
      {
        IntRollSpeed -= 50;
        wait ( 250, msec );
      }
      wait ( coolDown, msec );
    }
  }
  // Spins intake either fwd or rev, based on variable bool value when called
  void IntRollSpin()
  {
    IntRoll.spin(fwd, IntRollSpeed, pct);
  }

  // Switches fwd to opposite, and rev to off for flywheel spin when called
  void FlyF ()
  {
    while ( Con1.ButtonR2.pressing())
    {
      if (FlySpeed == 0 )
      {
        FlySpeed = 45;
      } 
      else
      {
        FlySpeed += 5;
      }
      wait ( 250, msec);
    }
  }
  void FlyS ()
  {
    FlySpeed = 0;
  }
  // Spins flywheel either fwd or rev, based on bool value when called
  void FlySpin()
  {
    FlyW.spin ( fwd, FlySpeed, pct );
  }

  void Indexer1()
  {
    Index.spinFor ( fwd, 180, deg, 150, rpm );
  }
  void Indexer3()
  {
    Index.spinFor ( fwd, 180 * 3, deg, 150, rpm );
  }

  void RollerControl()
  {
    RollerOn = !RollerOn;
  }
  void RollColourSpin ()
  {
    if (RollerOn == true)
    {
       if (RollerBlue == false)
      {
        // insert coe here
      }
      if (RollerBlue == true)
      {
        // insert code here
      }
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

/*----------------------------------/
------Functions for void auton-------
/----------------------------------*/

  void MoveFwdDeg ( float vel, float Y, float X, bool next )
  {
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
      wait (coolDown, msec);
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
      wait ( coolDown, msec );
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

  void RollingCB( float vel )
  {
    wait (1, sec );
    IntRoll.spin(fwd, vel, pct);
    while ( Colour.color() == red )
    {
      wait ( coolDown, msec);
    }    
    IntRoll.stop();
  }
  void RollingCR( float vel )
  {
    wait (1, sec );
    IntRoll.spin(fwd, vel, pct);
    while ( Colour.color() == blue )
    {
      wait ( coolDown, msec);
    }    
    IntRoll.stop();
  }

  void Rolling( float vel, float time, directionType dir )
  {
    IntRoll.spin(dir, vel, pct );
    wait ( time, msec );
    IntRoll.stop();
  }

/*----------------------------------/
--Functions for void auton with PID--
/----------------------------------*/
  int FlyPID ( float targetSpeed )
  {
    float flyP = 0;
  }
