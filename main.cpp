#include <iostream>
#include <cmath>
#include <chrono>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include "fundations.h"
#include "hero.h"
#include "foe.h"
#include "mmi.h"
using namespace std;

int main () {
//: Time, random initialization
  srand(time(NULL));
  sf::Clock clock;
  sf::Time elapsed = clock.restart();

//: window definition, SFML initializations
debug(); // Somehow gets sprite display to work
sf::RenderWindow window(sf::VideoMode(1920, 1080), "Starob");
window.setFramerateLimit(60);
sf::Event event;
sf::Sprite spriteBG;
sf::Texture textureBG;
string nameBGtexture("sprites/background.jpg");
if (!textureBG.loadFromFile(nameBGtexture)){std::cout << "Error loading file: Background" << std::endl;}
// sprite definition & load
spriteBG.setTexture(textureBG);

// Hero
sf::Texture m_texture;
sf::Sprite m_sprite;
std::string m_image;
m_image="sprites/testarob.png";
if (!m_texture.loadFromFile(m_image)){std::cout << "Error loading file: Hero." << std::endl;}
m_texture.setSmooth(true);
m_sprite.setPosition(sf::Vector2f((FY)/2, (FX)/2)); // absolute position
m_sprite.setTexture(m_texture);


//: Main variables.
  int loop(0);         // number of loops (for Foe generation)
  bool end;            // take info about escaping the main
  char field[FX][FY];  // char field where the fight unfolds
  initField(field);    // and its initialization

  // Objects, variables concerning classes
  Hero arob;
  std::vector<Foe*> vFoe;






// main loop
/// Window loop
  while (window.isOpen()){
 /// Fight loop
    do {

      elapsed = clock.restart(); // time management
      loop++;

    /// Hero management
      arob.manageShield();
      arob.manageMovement();

    /// Foes management
      try{ Foe::manageFoes(arob, loop, vFoe);
      }  catch (std::exception e) {std::cout << e.what() << std::endl;}

   /// update information
      try{ updateField(field, arob, vFoe);}
      catch (std::exception e) {std::cout << e.what() << std::endl;}

    //  displayFieldConsole(field);
     displayLife(arob);
    //  std::cout << "loop:" << loop << std::endl;


     window.clear(sf::Color::Black);
     window.draw(spriteBG);
     window.draw(arob.getSprite());
     window.draw(m_sprite);
     window.display();


     elapsed=clock.getElapsedTime();
     if (clock.getElapsedTime().asMilliseconds()<100)
     usleep(100000-elapsed.asMilliseconds());

    /// Miscellaneous closing conditions
     end=abortGame();
     while (window.pollEvent(event))
     {
       if (event.type == sf::Event::Closed)
       end=true;
     }

   } while(!arob.dead()&&(!end));

   window.close(); // if we got out by end of game
  }

  // testSFML();


return 0;
}
