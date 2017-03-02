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
  int m_hitbox; // radius of the ROUND hitbox in pixels.
  int m_limit; // minimum distance to the border of the field
  // console display
  char m_char;
  char m_charShield;
  // SFML
  std::string m_image;
  sf::Texture m_texture;
  int m_texturesize;
  sf::Sprite m_spriteHero;
  sf::Sprite m_spriteShield;
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
  int getHitbox() const;
  int getLimit() const;
  std::string getImage() const;
  sf::Sprite getSpriteHero() const;
    sf::Sprite getSpriteShield() const;
  int getSpriteSize() const;


  // Hero management
  bool validPos(const position pos) const;
  void takeDamage(const int damage);
  void manageShield();
  void manageMovement();
  void updateSprite();
  bool dead();


  // statics
  static direction getLUDR();
  static void manageHero(Hero &perso);

};

#endif //HERO_DEFINE
