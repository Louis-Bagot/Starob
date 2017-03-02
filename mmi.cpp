#include "mmi.h"

using namespace std;
// source for mmi(: man-machine interface)


bool abortGame(){
  return ((sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))||(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)));
}


void debug() {
  sf::RenderWindow window(sf::VideoMode(1920, 1200), "");

  sf::Texture textureBG;
  if (!textureBG.loadFromFile("sprites/background.png")){}
  sf::Texture textureHero;
  if (!textureHero.loadFromFile("sprites/starob.png")){}

  while (window.isOpen()) window.close();
}

sf::Sprite loadBG(sf::Texture &textureBG){
  sf::Sprite spriteBG;
  string nameBGtexture("sprites/background.png");
  if (!textureBG.loadFromFile(nameBGtexture)){std::cout << "Error loading file: Background" << std::endl;}
  // sprite definition & load
  spriteBG.setTexture(textureBG);
  spriteBG.setScale(sf::Vector2f(1.f, FX/1200.f)); // absolute scale factor
  return spriteBG;
}
