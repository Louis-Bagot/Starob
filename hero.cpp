#include "hero.h"

using namespace std;
// source of functions for class Hero

/// Constructor, Destructor
Hero::Hero() {
  // stats
  m_life=10;
  m_speed=1;
  // position & directions
  m_pos.x=FX/2;
  m_pos.y=FY/2;
  m_spritesize=1;
  m_posShield.x=m_pos.x;
  m_posShield.y=m_pos.y+m_spritesize;
  m_dirShield=RIGHT;
  m_limit=1;
  // console display
  m_char='@';
  m_charShield=')';
  // SFML
  m_image="sprites/starob.png";

}

Hero::~Hero(){
  cout << "Hero destructed" << endl;
}

/// Functions
// gets
int Hero::getLife() const {return m_life;}
int Hero::getSpeed() const {return m_speed;}
position Hero::getPos() const {return m_pos;}
position Hero::getPosShield() const {return m_posShield;}
char Hero::getChar() const {return m_char;}
char Hero::getCharShield() const {return m_charShield;}
int Hero::getLimit() const {return m_limit;}
string Hero::getImage() const {return m_image;}
int Hero::getSpriteSize() const {return m_spritesize;}

// hero handling

bool Hero::validPos(const position pos) const {
  return ((pos.x>=m_limit)&&(pos.x<=FX-1-m_limit-m_spritesize)&&(pos.y>=m_limit)&&(pos.y<=FY-1-m_limit-m_spritesize));
}

void Hero::takeDamage(const int damage){
  m_life-=damage;
  if (m_life<=0) {
    m_life=0;
  }
}

void Hero::manageShield() {
  m_dirShield=Hero::getLUDR(); // LEFT UP DOWN RIGHT arrows
  switch (m_dirShield) {
    case UP:
      m_posShield.x=m_pos.x-m_spritesize;
      m_posShield.y=m_pos.y;
      m_charShield='_';
      break;
    case DOWN:
      m_posShield.x=m_pos.x+m_spritesize;
      m_posShield.y=m_pos.y;
      m_charShield='-';
      break;
    case RIGHT:
      m_posShield.x=m_pos.x;
      m_posShield.y=m_pos.y+m_spritesize;
      m_charShield=')';
      break;
    case LEFT:
      m_posShield.x=m_pos.x;
      m_posShield.y=m_pos.y-m_spritesize;
      m_charShield='(';
      break;
  }
}

void Hero::manageMovement(){
  direction dir;
  position saveP=m_pos;
  position saveS=m_posShield;
  dir=Hero::getQZSD(); // Q: left; Z: up; S: down; D: right;

  switch (dir) {
    case UP:
      m_pos.x-=m_speed;
      m_posShield.x-=m_speed;
      break;
    case DOWN:
      m_pos.x+=m_speed;
      m_posShield.x+=m_speed;
      break;
    case RIGHT:
      m_pos.y+=m_speed;
      m_posShield.y+=m_speed;
      break;
    case LEFT:
      m_pos.y-=m_speed;
      m_posShield.y-=m_speed;
      break;
  }

  if (!validPos(m_pos)) {
    m_pos=saveP;
    m_posShield=saveS;
  }

}

bool Hero::dead() {
  return (m_life==0);
}


direction Hero::getQZSD(){
  direction dir;
  if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            dir = UP;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            dir = DOWN;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            dir = LEFT;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            dir = RIGHT;
          }
return dir;
}

direction Hero::getLUDR(){
  direction dir;
  if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            dir = UP;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            dir = DOWN;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            dir = LEFT;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            dir = RIGHT;
          }
return dir;
}
