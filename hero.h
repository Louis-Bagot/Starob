#ifndef HERO_DEFINE
#define HERO_DEFINE
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
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
  // SFML // !!! We assumed so far that the sprite is a square.
          // If it must be done rectangular, create "position m_sizesprite",
          // and put .x .y everywhere needed.
  std::string m_image;
  sf::Sprite m_sprite;
  sf::Texture m_texture;

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
  sf::Sprite getSprite() const;
  int getSpriteSize() const;


  // Hero management
  bool validPos(const position pos) const;
  void takeDamage(const int damage);
  void manageShield();
  void manageMovement();
  bool dead();


  // statics
  static direction getQZSD();
  static direction getLUDR();

};

#endif //HERO_DEFINE
