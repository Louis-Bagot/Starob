#include "foe.h"

using namespace std;

/// variables for all Foes, load function
const int Foe::constantPop=100; // Foes will pop constantly after that much loops
const float Foe::foesPerLoop=1/15.; /// 1/Number of foe popping per loop
const std::string Foe::m_image="sprites/foe.png";
sf::Texture Foe::m_texture;
const int Foe::m_texturesize=512; // actually twice with popping sprite
int Foe::counter=0;
const int Foe::animationDelay=64; // reminder: for popping time

void Foe::loadText(sf::Texture &texture, const std::string &str){
  texture.loadFromFile(str);
  texture.setSmooth(true);
}

//if (!Foe::m_texture.loadFromFile(Foe::m_image)){std::cout << "Error loading file: Foe." << std::endl;}

/// Foe functions

position Foe::randomFoePos(const Hero &perso){ //initial random position generator (for Constructor)
  position randPos; // pop to return
  int redge(rand()%4); // random edge to pop to
  // pairing edges with integers: let 0:UP, 1:DOWN; 2:LEFT, 3:RIGHT

  switch (redge) {
    case 0:
      randPos.x=perso.getSpriteSize()/2;
      break;
    case 1:
      randPos.x=FX-1-perso.getSpriteSize()/2;
      break;
    case 2:
      randPos.y=perso.getSpriteSize()/2;
      break;
    case 3:
      randPos.y=FY-1-perso.getSpriteSize()/2;
      break;
  }
  if (redge>1) // we are either L or R, need an x
    randPos.x=rand()%(FX-perso.getSpriteSize())+perso.getSpriteSize()/2; //pop somwhere on rect
  else
    randPos.y=rand()%(FY-perso.getSpriteSize())+perso.getSpriteSize()/2;

  return randPos;
}


// Constructor using m_target based on Hero position
Foe::Foe(const Hero &perso) {
  m_attack=1;
  m_speed=perso.getSpeed()*1.5;
  m_spritesize=128;
  m_hitbox=5;
  m_pos=randomFoePos(perso);
  m_origin=m_pos;

  // "advance" variables
  if (perso.getPos().x==m_pos.x) { // handling extreme vertical line case
    if (m_pos.x==FX-1-perso.getLimit()) {
      m_pos.x-=1;
    } else m_pos.x+=1;
  }
  // deltas
  if (perso.getPos().x>=m_pos.x) m_delta.x=1;
  else m_delta.x=-1;
  if (perso.getPos().y>=m_pos.y) m_delta.y=1;
  else m_delta.y=-1;

  // slope formula:
  m_slope=(perso.getPos().y-m_pos.y)/float(perso.getPos().x-m_pos.x);

  m_number=counter;
  m_latency=0;
  // SFML
  m_sprite.setTexture(Foe::m_texture);
  // cross look
  m_sprite.setTextureRect(sf::IntRect(0, 0, Foe::m_texturesize, Foe::m_texturesize));
  m_sprite.setPosition(sf::Vector2f(m_pos.y-(m_spritesize/2), m_pos.x-(m_spritesize/2))); // absolute position
  m_sprite.setScale(sf::Vector2f((0.5*m_spritesize/(float)Foe::m_texturesize), (0.5*m_spritesize/(float)Foe::m_texturesize)));


  // sprite tilt management. 180/pi ~= 57.2958 is conversion radian to degree
  float radToDeg=57.2958;
  if ((m_delta.x>=0)&&(m_delta.y>=0)) {
    m_tilt=radToDeg*atan(m_slope);
  } else if ((m_delta.x>=0)&&(m_delta.y>=0)) {
    m_tilt=180-radToDeg*atan(m_slope);
  } else if ((m_delta.x>=0)&&(m_delta.y>=0)) {
    m_tilt=360-radToDeg*atan(m_slope);
  } else {
    m_tilt=180+radToDeg*atan(m_slope);
  }

//  m_sprite.setRotation(m_tilt); // absolute angle
}


Foe::~Foe(){}

int Foe::getAttack()const { return m_attack;}
int Foe::getSpeed()const { return m_speed;}
position Foe::getPos() const{return m_pos;}
std::string Foe::getImage() const{return m_image;}
sf::Sprite Foe::getSprite() const {return m_sprite;}

void Foe::advance(){

  if (abs((m_origin.y-m_pos.y-m_delta.y*m_speed)/float(m_origin.x-m_pos.x)-m_slope)<
      abs((m_origin.y-m_pos.y)/float(m_origin.x-m_pos.x-m_delta.x*m_speed)-m_slope)) {
    if (abs((m_origin.y-m_pos.y-m_delta.y*m_speed)/float(m_origin.x-m_pos.x)-m_slope)>
        abs((m_origin.y-m_pos.y-m_delta.y*m_speed)/float(m_origin.x-m_pos.x-m_delta.x*m_speed)-m_slope)) {
      m_pos.y+=m_delta.y*m_speed;
      m_pos.x+=m_delta.x*m_speed;
    } else  m_pos.y+=m_delta.y*m_speed;
 } else if (abs((m_origin.y-m_pos.y-m_delta.y*m_speed)/float(m_origin.x-m_pos.x-m_delta.x*m_speed)-m_slope)<
            abs((m_origin.y-m_pos.y)/float(m_origin.x-m_pos.x-m_delta.x*m_speed)-m_slope)) {
    m_pos.x+=m_delta.x*m_speed;
    m_pos.y+=m_delta.y*m_speed;
  } else m_pos.x+=m_delta.x*m_speed;

}

void Foe::updateSprite(){
  m_sprite.setPosition(sf::Vector2f(m_pos.y-m_spritesize/2, m_pos.x-m_spritesize/2));
}

int Foe::collision(Hero &perso){
  int hit=0;

  if ((m_pos.x>=FX)||(m_pos.x<=-1)||(m_pos.y>=FY)||(m_pos.y<=-1)) // if we get out of field
    hit=1;
  else {
    if (m_pos-perso.getPosShield()<m_hitbox+perso.getHitbox()) {// we want to cover the shield+hero case so no ifelse
      hit=2;
      perso.touchedShield();
    }
    if (m_pos-perso.getPos()<m_hitbox+perso.getHitbox()) {// advantage to hero hit
      hit=3;
      perso.touchedHero();
    }
  }
  return hit;
}

int Foe::manage1Foe(Hero &perso){
  int hit;
  float shrink=(0.5*m_spritesize/(float)Foe::m_texturesize)-(0.5*m_spritesize/(float)Foe::m_texturesize)*(m_latency/(float)Foe::animationDelay);
  if (m_latency<Foe::animationDelay) {
    m_latency++;
    m_sprite.setScale(sf::Vector2f(shrink, shrink));
    m_sprite.setPosition(sf::Vector2f(m_pos.y-0.5*m_spritesize/2*shrink, m_pos.x-0.5*m_spritesize/2*shrink)); // absolute position
    m_sprite.rotate(360/Foe::animationDelay); // offset relative to the current angle
  } else {
    if (m_latency==animationDelay) { // if we are the first moving loop, update sprite
      m_sprite.setRotation(0); // absolute angle
      m_sprite.setScale(sf::Vector2f((m_spritesize/(float)Foe::m_texturesize), (m_spritesize/(float)Foe::m_texturesize)));
      m_sprite.setTextureRect(sf::IntRect( Foe::m_texturesize, 0, Foe::m_texturesize, Foe::m_texturesize));
      m_latency++;
    }
    advance(); // execute movement
    updateSprite();
  }
  hit=collision(perso); // check consequences
  if (hit==3) {
    perso.takeDamage(getAttack());
  }
  std::cout << "hit="<< hit << std::endl;
  return hit;
}

bool Foe::generator(const int &loop) {return (loop%(int)floor(1/Foe::foesPerLoop)==0);}

/* A POSSIBLE GENERATOR - TO TWEAK
bool Foe::generator(const int &loop){
    // square fonction a parameter (f(x)=ax²)
    double a(Foe::foesPerLoop/(2*Foe::constantPop));
    // const b of tangent equation p(x-m)+b with slope p=f'(m), b=am²
    double b(a*Foe::constantPop*Foe::constantPop);

    // bool deciding of generation
    if (loop<Foe::constantPop) return (floor((loop*loop*a))>(floor((loop-1)*(loop-1)*a)));
    else return ((floor(Foe::foesPerLoop*(loop-Foe::constantPop)+b))>(floor((Foe::foesPerLoop*(loop-1-Foe::constantPop)+b))));
}
*/

void Foe::manageFoes(Hero &perso, int loop, std::vector<Foe*> &vFoe, sf::RenderWindow &window) {
  bool del=false; // will check if you have deleted the current explored foe

  // generation of foes
  if (Foe::generator(loop)) {// if foe generator deems generation necessary
    counter++;
    vFoe.push_back(new Foe(perso));
  }

  for (size_t i=0; i<vFoe.size(); i++) {
    do {
      del=(vFoe[i]->manage1Foe(perso)>0); // here foe moves and deals damage
      if (del) {
        if (i<vFoe.size()-1){
          delete(vFoe[i]);
          vFoe[i]=vFoe[vFoe.size()-1];
          vFoe[vFoe.size()-1]=0;
        } else del=false; // if it was the last, don't check again
        delete(vFoe[vFoe.size()-1]);
        vFoe.pop_back();
      }
    } while(del);
  window.draw(vFoe[i]->getSprite());
  }
}
