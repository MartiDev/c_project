#ifndef UTILS_H
#define UTILS_H


#define NOM_FIC "feux.txt"
#define NOM_FIC_UNIQ_ID "uniq.txt"

#define RAND_MAX 15
#define SEUIL 0.5
#define LAMBA 0.1


double frand_a_b(double a, double b);
double generate_rand_value();
double generate_expo_value();
int generate_uniq_id();
int list_taille(Voiture* tete);
void enregistrement_taille_file(Voiture* tete);
bool find_index_liste(Voiture* tete, int index, int value_to_reach);
bool find_index_liste_top(Voiture* tete, int index, int value_to_reach);

#include "utils.c"

#endif // UTILS_H
