#include "foe.h"

using namespace std;
const int Foe::constantPop=100; // Foes will pop constantly after that much loops
const float Foe::foesPerLoop=1/1.; /// 1/Number of foe popping per loop
int Foe::counter=0;

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

  m_number=counter;
  // SFML
  m_char='o';
  m_image="foe.jpg";
}
Foe::~Foe(){}

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
  int hit;

  if ((m_pos.x>=FX)||(m_pos.x<=-1)||(m_pos.y>=FY)||(m_pos.y<=-1)) // if we get out of field
    hit=1;
  else if (m_pos==perso.getPosShield()) {
    hit=2;
  } else if (m_pos==perso.getPos()) {
    hit=3;
  }
  return hit;
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

void Foe::manageFoes(Hero &perso, int loop, std::vector<Foe*> &vFoe) {
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
  }
}

void Foe::getState(){
  std::cout << "Origin (" << m_origin.x <<","<< m_origin.y<<"), ";
  std::cout << "Position (" << m_pos.x <<","<< m_pos.y<<"), ";
  std::cout << "Pop number: " << m_number << ", " ;
}
