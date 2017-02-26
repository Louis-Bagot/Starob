// Base set of game Starob

#ifndef FUNDATIONS_DEFINE
#define FUNDATIONS_DEFINE
//#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define FX 13
#define FY 75
#define FMAX max(FX,FY)



typedef struct position {
  int x;
  int y;
} position;

enum direction {RIGHT,LEFT,UP,DOWN};

bool operator==(const position& pos1, const position& pos2);

#endif //FUNDATIONS_DEFINE
