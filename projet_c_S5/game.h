#ifndef GAME_H
#define GAME_H


void initialisation();
void changement_feux (Axe *axe1, Axe *axe2, int feu_suivant);
void launch_program(Axe *axe1, Axe *axe2);
void printRoad(Axe* axe1, Axe* axe2);

#include "game.c"

#endif // GAME_H
