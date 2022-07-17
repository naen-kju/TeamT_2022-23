#include "vex.h"

// Functions for all.
  void MecanumSpin ( float Y, float X, float R );

  void StopAll (bool LFM, bool RFM, bool LBM, bool RBM);

// Functions for user.
  void Thresholds ( float Variable, int Max );

  void DriverControl ( int Y, int X, int R, int Max );

// Functions for auto.
  void MecanumMoveTheta ( float theta, float power, float stop);