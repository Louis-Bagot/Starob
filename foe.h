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
  // variables for "advance"
  position m_origin; // origin position
  position m_delta; // handle whether x and y should go right or left
  float m_slope; // slope of the line foe will follow
  // pop variable(s)
  static const int constantPop; // number of loops after which Foes pop constantly
  static const float foesPerLoop; // number of loops after which Foes pop constantly

  static int counter; // nb of Foes created so far
  int m_number; // n° of creation
  // console display
  char m_char; // console display
  // SFML
  std::string m_image;
  sf::Sprite m_sprite;
  sf::Texture m_texture;

  position randomFoePos(); // generator of initial random position (for Constructor)

public:
  // Constructor(s), Destructor
  Foe(const Hero &perso);
  ~Foe();

  // gets
  int getAttack() const;
  int getSpeed() const;
  position getPos() const;
  char getChar() const;
  std::string getImage() const;
  sf::Texture getTexture()const;
  sf::Sprite getSprite()const;


  void getState() const; // current foe state

  // Foe routine:
  void advance(); // move one iteration. BEFORE first collision test !
  int collision(Hero &perso); // return options: 0: not; 1: border; 2: shield; 3: perso

  static int manage1Foe(Foe &opp,Hero &perso);
  static bool generator(const int &loop); // returns true if a foe must be summoned
  static void manageFoes(Hero &perso, int loop, std::vector<Foe*> &vFoe);
};


#endif //FOE_DEFINE
