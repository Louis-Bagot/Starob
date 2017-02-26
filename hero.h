#ifndef HERO_DEFINE
#define HERO_DEFINE
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <SFML/Window/Keyboard.hpp>
#include "fundations.h"

// Hero class
class Hero {
private:
  // stats
  int m_life;
  int m_speed;
  // position & directions
  position m_pos;
  position m_posShield;
  direction m_dirShield;
  int m_limit; // minimum distance to the border of the field
  // console display
  char m_char;
  char m_charShield;
  // SFML
  std::string m_image;
  int m_spritesize;


public:
  // Constructor(s), Destructor
  Hero();
  ~Hero();

  // gets
  int getLife() const;
  int getSpeed() const;
  position getPosShield() const;
  position getPos() const;
  char getChar() const;
  char getCharShield() const;
  int getLimit() const;
  std::string getImage() const;
  int getSpriteSize() const;


  // Hero management
  bool validPos(const position pos) const;
  void takeDamage(const int damage);
  void manageShield();
  void manageMovement();


  // statics
  static bool dead(const Hero perso);
  static direction getQZSD();
  static direction getLUDR();

};

#endif //HERO_DEFINE
