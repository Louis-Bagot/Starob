#ifndef MMI_DEFINE
#define MMI_DEFINE
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <time.h>
#include "fundations.h"
#include "hero.h"
#include "foe.h"

// library for game Starob: Man-Machine Interface

// SFML: keyboard & background
bool abortGame();
void debug();
sf::Sprite loadBG(sf::Texture &textureBG);
sf::Sprite loadLife(sf::Texture &textureLife, const Hero &perso, const int &sizelife);


#endif //MMI_DEFINE
