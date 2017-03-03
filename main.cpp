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
  int millisec(1); // loop slow factor

//: window definition, SFML initializations
debug(); // Somehow gets sprite display to work
sf::RenderWindow window(sf::VideoMode(1920, 1080), "Starob");
window.setFramerateLimit(60);
sf::Event event;
sf::Texture textureBG;
sf::Sprite spriteBG(loadBG(textureBG));



//: Main variables.
  int loop(0);         // number of loops (for Foe generation)
  bool end;            // take info about escaping the main

  // Objects, variables concerning classes
  Hero arob;
  std::vector<Foe*> vFoe;
  Foe::loadText(Foe::m_texture, Foe::m_image);
  sf::Texture textureLife;
  int sizelife=32; // size of textlife
  sf::Sprite spriteLife(loadLife(textureLife, arob, sizelife));






// ----------- main loop -------------///

  while (window.isOpen()){ /// Window loop
    do { /// Fight loop

      // --- begin time management --- //
     elapsed = clock.restart();
     loop++;

     // --- window --- //
     window.clear(sf::Color::Black);
     window.draw(spriteBG);

     // --- objects management --- //
     Hero::manageHero(arob);
     try{ Foe::manageFoes(arob, loop, vFoe, window); // display - warning exception!
     }  catch (std::exception e) {std::cout << e.what() << std::endl;}

    // --- Display --- //
     window.draw(arob.getSpriteShield());
     window.draw(arob.getSpriteHero());
     spriteLife.setTextureRect(sf::IntRect(0, 0, sizelife*arob.getLife(), sizelife));
     window.draw(spriteLife);
     window.display();


     // --- end time management --- //
     elapsed=clock.getElapsedTime();
     if (clock.getElapsedTime().asMilliseconds()<millisec)
     usleep(millisec*1000-elapsed.asMilliseconds());

    // --- Miscellaneous closing conditions --- //
     end=abortGame();
     while (window.pollEvent(event))
     {
       if (event.type == sf::Event::Closed){
         end=true;
       }
     }
   } while(!arob.dead()&&(!end));
  window.close(); // if we got out by regular end of game
  }

return 0;
}
