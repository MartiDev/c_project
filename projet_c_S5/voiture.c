Voiture* create_voiture(){
    Voiture* voit= NULL;
    voit = (Voiture*) malloc(sizeof(Voiture));
    voit->uniq_id = generate_uniq_id();
    voit->suiv = NULL;
    voit->pos_route = -10;
    voit->temps_arrive = 0;
    voit->temps_attente = 0;
    voit->temps_passage = 0;
    voit->temps_reponse = 0;
    return voit;
}

Voiture* insererVoiture(Voiture *tete, Voiture *voiture)
{
    if(tete == NULL){
        tete=voiture;
        tete->pos_route = 10;
        // printf("coucou tete null");
        return tete;
    }
    if(tete->pos_route < 10 && voiture->pos_route == -10){
        voiture->pos_route = 10;
    } else if (tete->pos_route >= 10){
        voiture->pos_route = tete->pos_route + 1;
    }
    voiture->suiv =tete;
    //printf("%d\n", voiture->suiv->couleur);
    //printf("%d\n", tete->couleur);
    tete = voiture;
    return tete;
    //printf("%d\n", tete->suiv->couleur);
}

void afficherVoiture(Voiture *voiture)
{
    printf("%d\n", voiture->uniq_id);
}

void afficherListeVoiture(Voiture* tete){
    Voiture *voit = tete;
    // printf("%d\n", tete->suiv->couleur);

    while (voit != NULL)
    {
        afficherVoiture(voit);
        voit = voit->suiv;
        //printf("TOP\n");
    }
}

Voiture* supprimerVoiture(Voiture *tete){
    Voiture *temp =tete;
    Voiture *t;
    if(tete->suiv==NULL)
    {
        enregistrement_donnee_voiture(tete);
        free(tete);
        tete=NULL;
    }
    else
    {
        while(temp->suiv != NULL)
        {
            t=temp;
            temp=temp->suiv;
        }
        enregistrement_donnee_voiture(t->suiv);
        free(t->suiv);
        t->suiv=NULL;
    }
    return tete;
}

Voiture* passage_voiture(Voiture *tete, bool statique){
    Voiture* voit = tete;
    while (voit != NULL){
        //printf("%d POS \n", voit->pos_route);
        if(statique){
            if(voit->pos_route > 1){
                if(voit->suiv != NULL){
                    int ecart = voit->pos_route - voit->suiv->pos_route;
                    if(ecart > 1){ // Si l'écart est supérieur à un (aucune voiture est devant
                        voit->pos_route = voit->pos_route - 1;
                        //printf("AVANCEMENT STATIQUE: %d\n", voit->pos_route);
                    } else { // Sinon, on attend
                        voit->temps_attente = voit->temps_attente +1;
                    }
                } else {
                    voit->pos_route = voit->pos_route - 1;
                    //printf("AVANCEMENT STATIQUE: %d\n", voit->pos_route);
                }
            } else{
                voit->temps_attente = voit->temps_attente +1;
            }
            voit = voit->suiv;
        } else{
            voit->pos_route = voit->pos_route - 1; // Ici on a un problème car à un instant T on se retrouve avec deux voitures à la même position.
            voit->temps_passage = voit->temps_passage + 1; // ici, la voiture avance donc on incrèmente son temps de passage
            if(voit->pos_route < 0){
                //printf("Supprimé !!\n");
                tete = supprimerVoiture(tete);
            }
            voit = voit->suiv;
        }
    }
    return tete;
}

void avancement_voiture(Axe* axe1, bool statique){
    /*
     *  Ici, on va gérer le passage des voitures.
     */

    if(axe1->v1 != NULL){
       // printf("first pos : %d\n", axe1->v1->pos_route);
        //printf("Il y a une voiture dans la voie 1!!\n");
        //afficherListeVoiture(axe1->v1);

        axe1->v1 = passage_voiture(axe1->v1, statique);
    } else {
       // printf("Il n'y a pas de voiture dans la voie 1 !! \n");
    }
    if(axe1->v2 != NULL){
        //printf("Il y a une voiture dans la voie 2!!\n");
        //afficherListeVoiture(axe1->v2);
        axe1->v2 = passage_voiture(axe1->v2, statique);
    }else {
        //printf("Il n'y a pas de voiture dans la voie 2 !! \n");
    }
}

void enregistrement_donnee_voiture(Voiture *voiture){
    voiture->temps_reponse = voiture->temps_arrive - voiture->temps_passage;
    FILE* fic;
    //fic = fopen("test.txt", "a+");
    char text[100];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);


    strftime(text, sizeof(text)-1, "%d_%m_%Y.txt", t); //C'ets intéressant puisque du coup automatiquement demain cela créera un nouveau fichier. Bien pour journaliser.
    //printf("Current Date: %s", text);
    fic = fopen(text, "a+");
    fprintf(fic, "%d %d %d %d %d\n", voiture->uniq_id, voiture->temps_attente, voiture->temps_arrive, voiture->temps_passage, voiture->temps_reponse);
    fclose(fic);

}
