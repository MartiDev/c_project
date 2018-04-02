void launch_indicateurs(){
    FILE* fic;
    char text[100];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(text, sizeof(text)-1, "%d_%m_%Y.txt", t); //C'ets intéressant puisque du coup automatiquement demain cela créera un nouveau fichier. Bien pour journaliser.
    //printf("Current Date: %s", text);
    fic = fopen(text, "r");

    int uniq_id;
    int temps_attente;
    int temps_arrive;
    int temps_passage;
    int temps_reponse;
    int taille_file_att;
    int TT_taille_file_att= 0;
    int TT_temps_attente = 0;
    int TT_temps_arrive = 0;
    int TT_temps_passage = 0;
    int TT_temps_reponse = 0;
    int cmpt = 0;
    int cmpt2 = 0;
    while (fscanf(fic, "%d %d %d %d %d", &uniq_id, &temps_attente, &temps_arrive, &temps_passage, &temps_reponse) != EOF)
    {
        TT_temps_attente += temps_attente;
        TT_temps_arrive += temps_arrive;
        TT_temps_passage += temps_passage;
        TT_temps_reponse += temps_reponse;
        cmpt++;
    }
    fic = fopen(NOM_FIC_TAILLE_FILE, "r");
    while (fscanf(fic, "%d", &taille_file_att) != EOF){
        TT_taille_file_att += taille_file_att;
        cmpt2++;
    }
    fclose(fic);

    Indicateur* indics = NULL;
    indics = (Indicateur*)malloc(sizeof(Indicateur));
    indics->temps_moy_arr = TT_temps_arrive / cmpt;
    indics->temps_moy_att = TT_temps_attente / cmpt;
    indics->temps_moy_pass = TT_temps_passage / cmpt;
    indics->temps_moy_rep = TT_temps_passage / cmpt;
    indics->taille_moy_file_att = TT_taille_file_att /cmpt2;
    printf("Indicateurs :\n");
    printf("Temps moyen arrivé : %0.3f s\n", indics->temps_moy_arr);
    printf("Temps moyen attendu : %0.3f s.\n", indics->temps_moy_att);
    printf("Temps moyen passage : %0.3f s.\n", indics->temps_moy_pass);
    printf("Temps moyen de réponse : %0.3f s.\n", indics->temps_moy_rep);
    printf("Taille moyenne de la file : %0.3f v.\n", indics->taille_moy_file_att);

}
