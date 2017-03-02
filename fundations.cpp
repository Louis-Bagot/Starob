#include "fundations.h"


bool operator==(const position& pos1, const position& pos2){
  return ((pos1.x==pos2.x)&&(pos1.y==pos2.y));
}

float operator-(const position &pos1, const position &pos2){
  return sqrt((pos1.x-pos2.x)*(pos1.x-pos2.x)+(pos1.y-pos2.y)*(pos1.y-pos2.y));
}
