#include "foe.h"

using namespace std;
const float Foe::popFactor=1; /// AAaH a global variable /o/ run4urLaif


position Foe::randomFoePos(){ //initial random position generator (for Constructor)
  position randPos; // pop to return
  int redge(rand()%4); // random edge to pop to
  // pairing edges with integers: let 0:UP, 1:DOWN; 2:LEFT, 3:RIGHT

  switch (redge) {
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
  if (redge>1) // we are either L or R, need an x
    randPos.x=rand()%FX;
  else
    randPos.y=rand()%FY;

  return randPos;

}


// Constructor using m_target based on Hero position
Foe::Foe(const Hero &perso) {
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

  if (abs((m_origin.y-m_pos.y-m_delta.y*m_speed)/float(m_origin.x-m_pos.x)-m_slope)<abs((m_origin.y-m_pos.y)/float(m_origin.x-m_pos.x-m_delta.x*m_speed)-m_slope)) {
    m_pos.y+=m_delta.y*m_speed;
  } else
    m_pos.x+=m_delta.x*m_speed;
}

int Foe::collision(Hero &perso){
  int res;

  if ((m_pos.x>=FX)||(m_pos.x<=-1)||(m_pos.y>=FY)||(m_pos.y<=-1)) // if we get out of field
    res=1;
  else if (m_pos==perso.getPosShield()) {
    res=2;
  } else if (m_pos==perso.getPos()) {
    res=3;
  }
  std::cout << "hit " << res << std::endl;
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

bool Foe::generator(const int &loop){
  return (floor(sqrt(loop-1))<floor(sqrt(loop)));
}

void Foe::manageFoes(Hero &perso, int loop, std::vector<Foe*> &vFoe) {
  bool del=false; // will check if you have deleted the current explored foe

  // generation of foes
  if (Foe::generator(loop)) // if foe generator deems generation necessary
    vFoe.push_back(new Foe(perso));


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
