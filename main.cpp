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
//spriteBG=sBackground();
sf::Texture textureBG;
string nameBGtexture("sprites/background.jpg");
if (!textureBG.loadFromFile(nameBGtexture)){std::cout << "Error loading file: Background" << std::endl;}
// sprite definition & load
spriteBG.setTexture(textureBG);
spriteBG.setScale(sf::Vector2f(1.f, FX/1200.f)); // absolute scale factor



//: Main variables.
  int loop(0);         // number of loops (for Foe generation)
  bool end;            // take info about escaping the main
  char field[FX][FY];  // char field where the fight unfolds
  initField(field);    // and its initialization

  // Objects, variables concerning classes
  Hero arob;
  std::vector<Foe*> vFoe;
  Foe::loadText(Foe::m_texture, Foe::m_image);






// main loop
/// Window loop
  while (window.isOpen()){
 /// Fight loop
    do {

      elapsed = clock.restart(); // time management
      loop++;


   /// update information
    //  try{ updateField(field, arob, vFoe);}
    //  catch (std::exception e) {std::cout << e.what() << std::endl;}

    //  displayFieldConsole(field);
    // displayLife(arob);
    //  std::cout << "loop:" << loop << std::endl;


     window.clear(sf::Color::Black);
     window.draw(spriteBG);

     /// Hero & Foes management
       Hero::manageHero(arob);
       try{ Foe::manageFoes(arob, loop, vFoe, window);
       }  catch (std::exception e) {std::cout << e.what() << std::endl;}

     window.draw(arob.getSpriteShield());
     window.draw(arob.getSpriteHero());
     window.display();


     elapsed=clock.getElapsedTime();
     if (clock.getElapsedTime().asMilliseconds()<30)
     usleep(30000-elapsed.asMilliseconds());

    /// Miscellaneous closing conditions
     end=abortGame();
     std::cout << "end inloop: " << end << std::endl;
     while (window.pollEvent(event))
     {
       if (event.type == sf::Event::Closed){
         end=true;
         std::cout << "pollEvent" << std::endl;
       }
     }

   } while(!arob.dead()&&(!end));
   std::cout << "end before close: " << end << std::endl;
   window.close(); // if we got out by regular end of game
  }

  // testSFML();
std::cout << "end:" << end << std::endl;
std::cout << "dead:" << arob.dead() << std::endl;

return 0;
}
