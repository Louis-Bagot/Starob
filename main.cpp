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

//: Main variables.
  int loop(0);
  bool end;            // take info about escaping the main
  char field[FX][FY];  // char field where the main unfolds
  initField(field);    // and its initialization

  // Objects, variables concerning classes
  Hero arob;
  std::vector<Foe*> vFoe;

  // main loop
  do {
    elapsed = clock.restart();
    loop++;

    arob.manageShield();
    arob.manageMovement();

    try{
      Foe::manageFoes(arob, loop, vFoe);
    }
    catch (std::exception e) {
      std::cout << e.what() << std::endl;
    }
    try{
      updateField(field, arob, vFoe);
    }
    catch (std::exception e) {
      std::cout << e.what() << std::endl;
    }
    displayFieldConsole(field);
    displayLife(arob);
    std::cout << "loop:" << loop << std::endl;
    end=abortGame();

    elapsed=clock.getElapsedTime();
    if (clock.getElapsedTime().asMilliseconds()<100)
              usleep(100000-elapsed.asMilliseconds());
  } while(!arob.dead()&&(!end));

// testSFML();


return 0;
}
