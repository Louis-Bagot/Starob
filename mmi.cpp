#include "mmi.h"

using namespace std;
// source for mmi(: man-machine interface)

void initField(char field[FX][FY]){
  for (size_t i = 0; i < FX; i++) {
    for (size_t j = 0; j < FY; j++) {
      field[i][j]='.';
    }
  }
}

void updateField(char field[FX][FY], const Hero &perso, const std::vector<Foe*> &vFoe){
  initField(field);
  for (size_t i = 0; i < vFoe.size(); i++) {
    field[vFoe[i]->getPos().x][vFoe[i]->getPos().y]=vFoe[i]->getChar();
  }
  field[perso.getPos().x][perso.getPos().y]=perso.getChar();
  field[perso.getPosShield().x][perso.getPosShield().y]=perso.getCharShield();
}


void displayFieldConsole(char const field[FX][FY]){
  system("clear");
  for (size_t i = 0; i < FX; i++) {
    for (size_t j = 0; j < FY; j++) {
      cout << field[i][j];
    }
    cout << endl;
  }

}

void displayLife(const Hero &perso){
  for (size_t i = 0; i < (unsigned)perso.getLife(); i++) {
    std::cout << "|";
  }
  std::cout << "" << std::endl;
}

bool abortGame(){
  return ((sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))||(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)));
}


void debug() {
  sf::RenderWindow window(sf::VideoMode(1920, 1200), "");

  sf::Texture textureBG;
  if (!textureBG.loadFromFile("sprites/background.jpg")){}
  sf::Texture textureHero;
  if (!textureHero.loadFromFile("sprites/starob.png")){}

  while (window.isOpen()) window.close();
}

sf::Sprite sBackground(){
  sf::Texture textureBG;
  sf::Sprite spriteBG;
  string nameBGtexture("sprites/background.jpg");
  if (!textureBG.loadFromFile(nameBGtexture)){std::cout << "Error loading file: Background" << std::endl;}
  // sprite definition & load
  spriteBG.setTexture(textureBG);
  return spriteBG;
}

void testSFML(){
  // wtf debug: (load texture before you load if for real)
debug();

  sf::Clock clock;
  // window
       sf::RenderWindow window(sf::VideoMode(1920, 1080), "Starob");
       // texture definition & load
       sf::Texture textureFond;
       string nomTextureFond("sprites/fond.jpg");
       if (!textureFond.loadFromFile(nomTextureFond)){std::cout << "Error loading file: Fond" << std::endl;}
       // sprite definition & load
       sf::Sprite spriteFond;
       spriteFond.setTexture(textureFond);
       spriteFond.setScale(sf::Vector2f(1.f, 1080/1200.f)); // absolute scale factor

       // Hero
       sf::Texture textureHero;
       string nomTextureHero("sprites/starob.png");
       if (!textureHero.loadFromFile(nomTextureHero)){std::cout << "Error loading file: Hero." << std::endl;}
       textureHero.setSmooth(true);
       sf::Sprite spriteHero;
       spriteHero.setPosition(sf::Vector2f((1920-128)/2, (1080-128)/2)); // absolute position
       spriteHero.setTexture(textureHero);



       sf::Event event;
       window.setFramerateLimit(60);

       // main loop
    while (window.isOpen())
    {
               while (window.pollEvent(event))
               {
                       if (event.type == sf::Event::Closed)
                       window.close();
               }

       window.clear(sf::Color::Black);
       window.draw(spriteFond);
       window.draw(spriteHero);
       window.display();

    }
}
