#include "hero.h"

using namespace std;
// source of functions for class Hero

/// Constructor, Destructor
Hero::Hero() {
  // stats
  m_life=10;
  m_speed=10;
  // position & directions
  m_pos.x=FX/2;
  m_pos.y=FY/2;
  m_texturesize=1024; // this is BOTH Hero and Shield. (minimise textures !)
  m_spritesize=128;
  m_hitbox=m_spritesize/2;
  m_posShield.x=m_pos.x;
  m_posShield.y=m_pos.y+1+m_spritesize/2;
  m_dirShield=RIGHT;
  m_limit=1.5*m_spritesize; // 3/2 is for 1 full unaccessible + 0.5 for dist center-spriteborder
  // SFML
  m_image="sprites/starob.png";
  if (!m_texture.loadFromFile(m_image)){std::cout << "Error loading file: Hero." << std::endl;}
  m_texture.setSmooth(true);
  // Hero sprite
  m_spriteHero.setTexture(m_texture);
  m_spriteHero.setTextureRect(sf::IntRect(0, 0, m_texturesize/2, m_texturesize/2));
  m_spriteHero.setScale(sf::Vector2f((2*m_spritesize/(float)m_texturesize), (2*m_spritesize/(float)m_texturesize))); // times 2: Hero+Shield
  m_spriteHero.setPosition(sf::Vector2f(m_pos.y-(m_spritesize/2), m_pos.x-(m_spritesize/2))); // absolute position
  // Shield sprite
  m_spriteShield.setTexture(m_texture);
  m_spriteShield.setScale(sf::Vector2f((2*m_spritesize/(float)m_texturesize), (2*m_spritesize/(float)m_texturesize))); // times 2: Hero+Shield
  m_spriteShield.setTextureRect(sf::IntRect(m_texturesize/2, 0, m_texturesize/2, m_texturesize/2));
  m_spriteShield.setPosition(sf::Vector2f(m_posShield.y-(m_spritesize/2), m_posShield.x-(m_spritesize/2))); // absolute position

}

Hero::~Hero(){cout << "Hero destructed" << endl;}

/// Functions
// gets
int Hero::getLife() const {return m_life;}
int Hero::getSpeed() const {return m_speed;}
position Hero::getPos() const {return m_pos;}
position Hero::getPosShield() const {return m_posShield;}
int Hero::getLimit() const {return m_limit;}
int Hero::getHitbox() const {return m_hitbox;}
string Hero::getImage() const {return m_image;}
sf::Sprite Hero::getSpriteHero() const {return m_spriteHero;}
sf::Sprite Hero::getSpriteShield() const {return m_spriteShield;}
int Hero::getSpriteSize() const {return m_spritesize;}

// hero handling

bool Hero::validPos(const position pos) const {
  return ((pos.x>=m_limit)&&(pos.x<=FX-1-m_limit)&&(pos.y>=m_limit)&&(pos.y<=FY-1-m_limit));
}

void Hero::takeDamage(const int damage){
  m_life-=damage;
  if (m_life<=0) {
    m_life=0;
  }
}

void Hero::manageShield() {
/* Shield with keyboard
  m_dirShield=Hero::getLUDR(); // LEFT UP DOWN RIGHT arrows
  switch (m_dirShield) {
    case UP:
      m_posShield.x=m_pos.x-1-m_spritesize/2;
      m_posShield.y=m_pos.y;
      break;
    case DOWN:
      m_posShield.x=m_pos.x+1+m_spritesize/2;
      m_posShield.y=m_pos.y;
      break;
    case RIGHT:
      m_posShield.x=m_pos.x;
      m_posShield.y=m_pos.y+1+m_spritesize/2;
      break;
    case LEFT:
      m_posShield.x=m_pos.x;
      m_posShield.y=m_pos.y-1-m_spritesize/2;
      break;
  }
*/ // Shield with mouse:

sf::Vector2i vMouse = sf::Mouse::getPosition(); // !warning - desktop coordinates are (Y, X)
position mousepos;
mousepos.x=vMouse.y;
mousepos.y=vMouse.x;
float distance(m_pos-mousepos);
m_posShield.x=m_pos.x-(m_spritesize/2)*(m_pos.x-mousepos.x)/distance;
m_posShield.y=m_pos.y-(m_spritesize/2)*(m_pos.y-mousepos.y)/distance;

}

void Hero::manageMovement(){
  position saveP=m_pos;
  position saveS=m_posShield;

  if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
          m_pos.x-=m_speed;
          m_posShield.x-=m_speed;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
          m_pos.x+=m_speed;
          m_posShield.x+=m_speed;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
          m_pos.y-=m_speed;
          m_posShield.y-=m_speed;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
          m_pos.y+=m_speed;
          m_posShield.y+=m_speed;}
          }

  if (!validPos(m_pos)) {
    m_pos=saveP;
    m_posShield=saveS;
  }
}

void Hero::updateSprite(){
  m_spriteHero.setPosition(sf::Vector2f(m_pos.y-m_spritesize/2, m_pos.x-m_spritesize/2));
  m_spriteShield.setPosition(sf::Vector2f(m_posShield.y-m_spritesize/2, m_posShield.x-m_spritesize/2));
}

bool Hero::dead() {
  return (m_life==0);
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



void Hero::manageHero(Hero &perso) {
  perso.manageShield();
  perso.manageMovement();
  perso.updateSprite();
}
