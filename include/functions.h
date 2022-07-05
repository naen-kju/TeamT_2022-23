#ifndef functions_h
#define functions_h

#include "vex.h"

void Thresholds ( float Variable, int Max, int Min );

void RemixEnable ();

bool RemixControlEnabled ();

void WildEnable ();

bool WildControlEnabled ();

float Clamp ( float value, float min, float max );

void SpinDrive(int lVel, int rVel);

void StopAll(bool LMs, bool RMs);

void SpinForDrive(float lDeg, float rDeg, int lVel, int rVel, bool next);

void TimeDrv(int Lvel, int Rvel, float milsec);

void DegDrv(int vel, float dist, bool next);

void DegTurn();

#endif