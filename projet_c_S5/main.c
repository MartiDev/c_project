#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>




#define TIMER_JAUNE 3
#define TIMER_VERT 12
#define TIMER_ROUGE 15

typedef struct _Feu
{
    int etat; // 1 vert - 2 jaune - 3 rouge
    int timerCourant;
    int timerRouge;
    int timerVert;
    int timerJaune;
} Feu;

typedef struct _Voitures {
    int uniq_id;
    double ecart;
    int temps_attente;
    int temps_arrive;
    int temps_passage;
    int pos_route;
    int temps_reponse;
    struct _Voitures *suiv;
} Voiture;


typedef struct {
    double taille_moy_file;
    double taille_max_file;
    double temps_moy_rep;
    double temps_moy_att;
    double temps_moy_arr;
    double temps_moy_pass;
    double taille_moy_file_att;
} Indicateur;

typedef struct _Axe {
    Feu *feu1;
    Feu *feu2;
    Voiture *v1;
    Voiture *v2;
} Axe;

#include "axe.h"
#include "voiture.h"
#include "indicateurs.h"
#include "utils.h"
#include "game.h"



void choix_menu(){
    int choix;
    printf("\n1 Lancer la simulation\n");
    printf("2 afficher les indicateurs clés\n");
    printf("choix : ");
    scanf("%d", &choix);
    switch (choix)
    {
      case 1 :
         initialisation();
        break;
      case 2 :
        launch_indicateurs();
        break;
    }
}

int main()
{

   choix_menu();


    return 0;
}
