#include "foe.h"

using namespace std;

/// variables for all Foes
const int Foe::constantPop=100; // Foes will pop constantly after that much loops
const float Foe::foesPerLoop=1/1.; /// 1/Number of foe popping per loop
int Foe::counter=0;
const std::string Foe::m_image="sprites/foe.png";
sf::Texture Foe::m_texture;
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
  m_speed=10;
  m_spritesize=128;
  m_hitbox=m_spritesize/2;
  m_pos=randomFoePos(perso); // first initialalization of m_tilt too
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
  // SFML
  m_char='o';
  m_sprite.setTexture(Foe::m_texture);
  m_sprite.setPosition(sf::Vector2f(m_pos.y-(m_spritesize/2), m_pos.x-(m_spritesize/2))); // absolute position






}
Foe::~Foe(){}

int Foe::getAttack()const { return m_attack;}
int Foe::getSpeed()const { return m_speed;}
position Foe::getPos() const{return m_pos;}
char Foe::getChar() const{return m_char;}
std::string Foe::getImage() const{return m_image;}
sf::Sprite Foe::getSprite() const {return m_sprite;}

void Foe::advance(){

  if (abs((m_origin.y-m_pos.y-m_delta.y*m_speed)/float(m_origin.x-m_pos.x)-m_slope)<
      abs((m_origin.y-m_pos.y)/float(m_origin.x-m_pos.x-m_delta.x*m_speed)-m_slope)) {
    if (abs((m_origin.y-m_pos.y-m_delta.y*m_speed)/float(m_origin.x-m_pos.x)-m_slope)<
        abs((m_origin.y-m_pos.y-m_delta.y*m_speed)/float(m_origin.x-m_pos.x-m_delta.x*m_speed)-m_slope)) {
      m_pos.y+=m_delta.y*m_speed;
      m_pos.x+=m_delta.x*m_speed;
    } else m_pos.y+=m_delta.y*m_speed;
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
  int hit;

  if ((m_pos.x>=FX)||(m_pos.x<=-1)||(m_pos.y>=FY)||(m_pos.y<=-1)) // if we get out of field
    hit=1;
  else {
    if (m_pos-perso.getPosShield()<m_hitbox+perso.getHitbox()) // we want to cover the shield+hero case so no ifelse
    hit=2;
    if (m_pos-perso.getPos()<m_hitbox+perso.getHitbox()) // advantage to hero hit
    hit=3;

  }
  return hit;
}

int Foe::manage1Foe(Foe &opp, Hero &perso){
  int hit;
  opp.advance(); // execute movement
  opp.updateSprite();
  hit=opp.collision(perso); // check consequences
  if (hit==3) {
    perso.takeDamage(opp.getAttack());
  }
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
      del=(manage1Foe(*vFoe[i], perso)>0); // here foe moves and deals damage
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

void Foe::getState() const{
  std::cout << "Origin (" << m_origin.x <<","<< m_origin.y<<"), ";
  std::cout << "Position (" << m_pos.x <<","<< m_pos.y<<"), ";
  std::cout << "Pop number: " << m_number << ", " ;
}
