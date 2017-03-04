#ifndef FOE_DEFINE
#define FOE_DEFINE
#include <cstdlib>
#include <cmath>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "fundations.h"
#include "hero.h"

// Foe class
class Foe {
private:
  // stats
  int m_attack;
  int m_speed;
  // position
  position m_pos; // position
  int m_hitbox; // size of the ROUND hitbox in pixels.
  // variables for "advance"
  position m_origin; // origin position
  position m_delta; // handle whether x and y should go right or left
  float m_slope; // slope of the line foe will follow
  // pop variable(s)

  int m_number; // n° of creation
  int m_latency; // loop counter for delayed apparition
  // console display
  char m_char; // console display
  // SFML
  sf::Sprite m_sprite;
  int m_spritesize;
  int m_tilt; // angle for the sprite // lol the day I code that


  position randomFoePos(const Hero &perso); // generator of initial random position (for Constructor)

public:
  // Constructor(s), Destructor
  Foe(const Hero &perso);
  ~Foe();

  // gets
  int getAttack() const;
  int getSpeed() const;
  position getPos() const;
  std::string getImage() const;
  sf::Texture getTexture()const;
  sf::Sprite getSprite()const;

  // Foe routine:
  void advance(); // move one iteration. BEFORE first collision test !
  void updateSprite(); // moves sprite where pos is
  int collision(Hero &perso); // return options: 0: not; 1: border; 2: shield; 3: perso
  int manage1Foe(Hero &perso);


  // static attributes and functions
  static const int constantPop; // number of loops after which Foes pop constantly
  static const float foesPerLoop; // number of loops after which Foes pop constantly
  static const std::string m_image;
  static sf::Texture m_texture; // cst SFML texture
  static const int m_texturesize;
  static int counter; // nb of Foes created so far
  static const int animationDelay; // time for popping animation

  static bool generator(const int &loop); // returns true if a foe must be summoned
  static void manageFoes(Hero &perso, int loop, std::vector<Foe*> &vFoe, sf::RenderWindow &window);
  static void loadText(sf::Texture &texture, const std::string &str);
};


#endif //FOE_DEFINE
