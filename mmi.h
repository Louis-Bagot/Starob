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

/// Field handling
void initField(char field[FX][FY]);
void updateField(char field[FX][FY], const Hero &perso, const std::vector<Foe*> &vFoe);
void displayFieldConsole(const char field[FX][FY]);
void displayLife(const Hero &perso);
void testSFML();

/// Keyboard entries
bool abortGame();


#endif //MMI_DEFINE
