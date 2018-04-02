void initialisation(){
    Voiture *v1_tete = NULL;
    Voiture *v2_tete = NULL;
    Voiture *v3_tete = NULL;
    Voiture *v4_tete = NULL;
    v1_tete = (Voiture *)malloc(sizeof(Voiture));
    v1_tete->uniq_id = generate_uniq_id();
    v1_tete->ecart = 12.3;
    v1_tete->temps_arrive = 0;
    v1_tete->temps_attente = 0;
    v1_tete->temps_passage = 0;
    v1_tete->temps_reponse = 0;
    v1_tete->suiv = NULL;
    v1_tete->pos_route = 1;
    v2_tete = NULL;
    v3_tete = NULL;
    v4_tete =  NULL;

    Voiture *v_test =NULL;
    v_test = (Voiture *)malloc(sizeof(Voiture));
    v_test->uniq_id =generate_uniq_id();
    v_test->suiv = NULL;
    v_test->pos_route = 2;
    v_test->temps_arrive = 0;
    v_test->temps_attente = 0;
    v_test->temps_passage = 0;
    v_test->temps_reponse = 0;

    v1_tete = insererVoiture(v1_tete, v_test);



    //v1_tete = supprimerVoiture(v1_tete);

    //afficherListeVoiture(v1_tete);

    Feu *feu1 = NULL;
    Feu *feu2 = NULL;
    Feu *feu3 = NULL;
    Feu *feu4 = NULL;

    feu1 = (Feu *)malloc(sizeof(Feu));
    feu2 = (Feu *)malloc(sizeof(Feu));
    feu3 = (Feu *)malloc(sizeof(Feu));
    feu4 = (Feu *)malloc(sizeof(Feu));

    feu1->etat = 1;
    feu2->etat = 1;
    feu3->etat = 3;
    feu4->etat = 3;
    feu1->timerJaune = TIMER_JAUNE;
    feu2->timerJaune = TIMER_JAUNE;
    feu3->timerJaune = TIMER_JAUNE;
    feu4->timerJaune = TIMER_JAUNE;

    feu1->timerVert = TIMER_VERT;
    feu2->timerVert = TIMER_VERT;
    feu3->timerVert = TIMER_VERT;
    feu4->timerVert = TIMER_VERT;

    feu1->timerRouge = TIMER_VERT + TIMER_JAUNE;
    feu2->timerRouge = TIMER_VERT + TIMER_JAUNE;
    feu3->timerRouge = TIMER_VERT + TIMER_JAUNE;
    feu4->timerRouge = TIMER_VERT + TIMER_JAUNE;

    feu1->timerCourant = TIMER_VERT;
    feu2->timerCourant = TIMER_VERT;
    feu3->timerCourant = TIMER_ROUGE;
    feu4->timerCourant = TIMER_ROUGE;


    Axe *axe1 = NULL;
    Axe *axe2 = NULL;

    axe1 = (Axe *)malloc(sizeof(Axe));
    axe2 = (Axe *)malloc(sizeof(Axe));


    axe1->feu1 = feu1;
    axe1->feu2 = feu2;
    axe1->v1 = v1_tete;
    axe1->v2 = v2_tete;

    axe2->feu1 = feu3;
    axe2->feu2 = feu4;
    axe2->v1 = v3_tete;
    axe2->v2 = v4_tete;

    launch_program(axe1, axe2);

}

void changement_feux (Axe *axe1, Axe *axe2, int feu_suivant){
    /*
     *  Ici on va gérer l'alternance du feu en cours
     */
    if(axe1->feu1->timerCourant > 1 && axe1->feu2->timerCourant > 1){
        axe1->feu1->timerCourant = axe1->feu1->timerCourant - 1;
        axe1->feu2->timerCourant = axe1->feu2->timerCourant - 1;

    } else {
        axe1->feu1->etat = feu_suivant;
        axe1->feu2->etat = feu_suivant;
        switch(feu_suivant){
        case 1 :
            axe1->feu1->timerCourant = TIMER_VERT;
            axe1->feu2->timerCourant = TIMER_VERT;
            break;
        case 2 :
            axe1->feu1->timerCourant = TIMER_JAUNE;
            axe1->feu2->timerCourant = TIMER_JAUNE;
            break;
        case 3 :
            axe1->feu1->timerCourant = TIMER_JAUNE + TIMER_VERT;
            axe1->feu2->timerCourant = TIMER_JAUNE + TIMER_VERT;
            axe2->feu1->etat = 1;
            axe2->feu2->etat = 1;
            break;
        default :
            break;
        }
    }
}

void launch_program(Axe *axe1, Axe *axe2){
    int timer_next_car_v1 = 0;
    int timer_next_car_v2 = 0;
    int timer_next_car_v3 = 0;
    int timer_next_car_v4 = 0;

    while(true){

        //Find the green
        if(axe1->feu1->etat == 1 && axe1->feu2->etat == 1 && axe2->feu1->etat == 3 && axe2->feu2->etat == 3){
            //printf("Les feus axe 1 sont verts !!\n");
            enregistrement_taille_file(axe1->v1);
            enregistrement_taille_file(axe1->v2);
            avancement_voiture(axe1, false);
            avancement_voiture(axe2, true); // On avance les voitures statiques sans les faire passer

            changement_feux (axe1, axe2, 2);

        } else if (axe1->feu1->etat == 2 && axe1->feu2->etat == 2 && axe2->feu1->etat == 3 && axe2->feu2->etat == 3){
           // printf("Les feus axe 1 sont Jaunes !!\n");

            avancement_voiture(axe1, false);
            avancement_voiture(axe2, true); // On avance les voitures statiques sans les faire passer

            changement_feux (axe1, axe2,3);

        } else if(axe1->feu1->etat == 3 && axe1->feu2->etat == 3 && axe2->feu1->etat == 1 && axe2->feu2->etat == 1){
            //printf("Les feus axe 2 sont verts !!\n");
            enregistrement_taille_file(axe2->v1);
            enregistrement_taille_file(axe2->v2);
            avancement_voiture(axe2, false);
            avancement_voiture(axe1, true); // On avance les voitures statiques sans les faire passer

            changement_feux (axe2, axe1, 2);

        } else if(axe1->feu1->etat == 3 && axe1->feu2->etat == 3 && axe2->feu1->etat == 2 && axe2->feu2->etat == 2){
           // printf("Les feus axe 2 sont Jaunes !!\n");

            avancement_voiture(axe2, false);
            avancement_voiture(axe1, true); // On avance les voitures statiques sans les faire passer

            changement_feux (axe2, axe1, 3);

        } else {
           //printf("Oula situation inconnue !!\n");
        }

        /*
         *  Ici, on va gérer la génération des voitures.
         */

        if(timer_next_car_v1 == 0){
            axe1->v1 = insererVoiture(axe1->v1, create_voiture());
            timer_next_car_v1 = generate_expo_value();
            axe1->v1->temps_arrive = timer_next_car_v1;
        } else {
            timer_next_car_v1 = timer_next_car_v1 - 1;
        }

        if(timer_next_car_v2 == 0){
            axe1->v2 = insererVoiture(axe1->v2, create_voiture());
            timer_next_car_v2 = generate_expo_value();
            axe1->v2->temps_arrive = timer_next_car_v2;
        } else {
            timer_next_car_v2 = timer_next_car_v2 - 1;
        }
        // on vérifie les valeurs des timers pour les changements d'états

        if(timer_next_car_v3 == 0){
            axe2->v1 = insererVoiture(axe2->v1, create_voiture());
            timer_next_car_v3 = generate_expo_value();
            axe2->v1->temps_arrive = timer_next_car_v3;
        } else {
            timer_next_car_v3 = timer_next_car_v3 - 1;
        }

        if(timer_next_car_v4 == 0){
            axe2->v2 = insererVoiture(axe2->v2, create_voiture());
            timer_next_car_v4 = generate_expo_value();
            axe2->v2->temps_arrive = timer_next_car_v4;
        } else {
            timer_next_car_v4 = timer_next_car_v4 - 1;
        }
        // on vérifie les valeurs des timers pour les changements d'états

        printRoad(axe1, axe2);
        struct timespec tim, tim2;
        tim.tv_sec = 1;
        tim.tv_nsec = 0L;
        nanosleep(&tim , &tim2);
    }
}

void printRoad(Axe* axe1, Axe* axe2){
    const char *h = "  |_o*!#@";

    for(int i = 0; i < 24; ++i)
    {
       for(int j = 0; j < 38 ; ++j)
       {
          if((j == 13 || j == 17) && (i < 11 || i > 14)){
                printf("%c", h[2]);
          } else if (i != 11 && i != 14 && !(j == 12 && i == 10) && !(j == 11 && i == 15)){
                printf("%c",h[0]);
          }

          if( (j == 14 && i<=10) && find_index_liste(axe1->v1, i, 10)){
              printf("%c",h[4]);
          }
          if(j == 11 && i == 10){
              switch (axe1->feu1->etat) {
              case 1:
                  printf("%c", h[7]);
                  break;
              case 2:
                  printf("%c", h[8]);
                  break;
              case 3 :
                  printf("%c", h[6]);
              default:
                  break;
              }
          }

          if(j == 19 && i == 11){
              switch (axe2->feu1->etat) {
              case 1:
                  printf("%c", h[7]);
                  break;
              case 2:
                  printf("%c", h[8]);
                  break;
              case 3 :
                  printf("%c", h[6]);
              default:
                  break;
              }
          }

          if(j == 18 && i == 15){
              switch (axe1->feu2->etat) {
              case 1:
                  printf("%c", h[7]);
                  break;
              case 2:
                  printf("%c", h[8]);
                  break;
              case 3 :
                  printf("%c", h[6]);
              default:
                  break;
              }
          }

          if(j == 11 && i == 15){
              switch (axe2->feu2->etat) {
              case 1:
                  printf("%c", h[7]);
                  break;
              case 2:
                  printf("%c", h[8]);
                  break;
              case 3 :
                  printf("%c", h[6]);
              default:
                  break;
              }
          }

          if( (j == 14 && i>=14) && find_index_liste_top(axe1->v2, i, 14)){
              printf("%c",h[4]);
          }

          if((i == 11 || i == 14) && (j < 21 || j > 24)){
                printf("%c", h[3]);
          }
          if(i == 14 && j<=13 && find_index_liste(axe2->v1, j, 10)){
                printf("%c",h[5]);
          }
          if(i == 12 && j>=17 && find_index_liste_top(axe2->v1, j, 14)){
                printf("%c",h[5]);
          }
       }

    printf("\n");
    }
}
