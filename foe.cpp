#include "foe.h"

using namespace std;
const float Foe::popSlowFactor=0.001; /// AAaH a global variable /o/ run4urLaif


position Foe::randomFoePos(){ //initial random position generator (for Constructor)
  position randPos;

  m_edge=rand()%4; // We want Foe to pop on the side.
                   //let 0&1 be U&D and 2&3 be L&R
  switch (m_edge) {
    case 0:
      randPos.x=0;
      break;
    case 1:
      randPos.x=FX-1;
      break;
    case 2:
      randPos.y=0;
      break;
    case 3:
      randPos.y=FY-1;
      break;
  }
  if (m_edge>1) // we are either L or R, need an x
    randPos.x=rand()%(FX-1) +1; // we dodge dead corner positions
  else
    randPos.y=rand()%(FY-1) +1;

  return randPos;

}


// Constructor using m_target based on Hero position
Foe::Foe(const Hero perso) {
  m_attack=1;
  m_speed=1;
  m_pos=randomFoePos(); // initialalizes m_edge too
  m_origin=m_pos;

  // "advance" variables
  if (perso.getPos().x==m_pos.x) { // handling extreme vertical line case
    if (m_pos.x==FX-1-perso.getLimit()) {
      m_pos.x-=m_speed;
    } else m_pos.x+=m_speed;
  }
  // deltas
  if (perso.getPos().x>=m_pos.x) m_delta.x=1;
  else m_delta.x=-1;
  if (perso.getPos().y>=m_pos.y) m_delta.y=1;
  else m_delta.y=-1;

  // slope formula:
  m_slope=(perso.getPos().y-m_pos.y)/float(perso.getPos().x-m_pos.x);
  m_first=true;
  // SFML
  m_char='o';
  m_image="foe.jpg";
}
Foe::~Foe(){std::cout << "Foe destructed" << std::endl;}

int Foe::getAttack()const { return m_attack;}
int Foe::getSpeed()const { return m_speed;}
position Foe::getPos() const{return m_pos;}
char Foe::getChar() const{return m_char;}
std::string Foe::getImage() const{return m_image;}

void Foe::advance(){
  if (m_first) {
    m_first=false;
    switch (m_edge) {
      case 0:
        m_pos.x+=m_speed;
        break;
      case 1:
        m_pos.x-=m_speed;
        break;
      case 2:
        m_pos.y+=m_speed;
        break;
      case 3:
        m_pos.y-=m_speed;
        break;
    }
  } else {
    if (abs((m_origin.y-m_pos.y-m_delta.y*m_speed)/float(m_origin.x-m_pos.x)-m_slope)<abs((m_origin.y-m_pos.y)/float(m_origin.x-m_pos.x-m_delta.x*m_speed)-m_slope)) {
      m_pos.y+=m_delta.y*m_speed;
    } else m_pos.x+=m_delta.x*m_speed;
  }

}

int Foe::collision(Hero &perso){
  int res;

  if ((m_pos.x==FX-1)||(m_pos.x==0)||(m_pos.y==FY-1)||(m_pos.y==0))
    res=1;
  else if (m_pos==perso.getPosShield()) {
    res=2;
  } else if (m_pos==perso.getPos()) {
    res=3;
  }

  return res;
}

int Foe::manage1Foe(Foe &opp, Hero &perso){
  int hit;
  opp.advance(); // execute movement
  hit=opp.collision(perso); // check consequences
  if (hit==3) {
    perso.takeDamage(opp.getAttack());
  }
  return hit;
}

void Foe::manageFoes(Hero &perso, int loop, std::vector<Foe*> &vFoe) {
  bool del=false; // will check if you have deleted the current explored foe
//?  std::vector<Foe*> vFoe;

  // generation of foes
  for (size_t i = 0; i < Foe::popSlowFactor*sqrt(loop)+1; i++) {
    vFoe.push_back(new Foe(perso));
  }

  for (size_t i=0; i<vFoe.size(); i++) {
    do {
      del=(manage1Foe(*vFoe[i], perso)>0); // here foe moves and deals damage
      if (del) {
        if (i<vFoe.size()-1){
          delete(vFoe[i]);
          vFoe[i]=vFoe[vFoe.size()-1];
        }
        delete(vFoe[vFoe.size()-1]);
        vFoe.pop_back();
      }
    } while(del);
  }
}

void Foe::getState(){
  std::cout << "Ori (" << m_origin.x <<","<< m_origin.y<<")" << std::endl;
  std::cout << "Pos (" << m_pos.x <<","<< m_pos.y<<")" << std::endl;
  std::cout << "Slope: " << m_slope << std::endl;
}
