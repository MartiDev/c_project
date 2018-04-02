#ifndef VOITURE_H
#define VOITURE_H

Voiture* create_voiture();
Voiture* insererVoiture(Voiture *tete, Voiture *voiture);
void afficherVoiture(Voiture *voiture);
void afficherListeVoiture(Voiture* tete);
Voiture* supprimerVoiture(Voiture *tete);
Voiture* passage_voiture(Voiture *tete, bool statique);
void avancement_voiture(Axe* axe1, bool statique);
void enregistrement_donnee_voiture(Voiture *voiture);

#include "voiture.c"

#endif // VOITURE_H
