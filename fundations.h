// Base set of game Starob

#ifndef FUNDATIONS_DEFINE
#define FUNDATIONS_DEFINE
//#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define FX 1080
#define FY 1920
#define FMAX MAX(FX,FY)



typedef struct position {
  int x;
  int y;
} position;

enum direction {RIGHT,LEFT,UP,DOWN};

bool operator==(const position &pos1, const position &pos2);
float operator-(const position &pos1, const position &pos2); // Substraction is distance.

#endif //FUNDATIONS_DEFINE
