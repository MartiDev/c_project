double frand_a_b(double a, double b){

    return ( rand()/(double)RAND_MAX ) * (b-a) + a;
}

double generate_rand_value(){
    double number = frand_a_b(0.0, 1.0);
    //printf("%0.8f\n", number);
    return number;
}

double generate_expo_value(){
    return -log(1 - generate_rand_value())/LAMBA; //Probabilité qu'on compare à un seuil
}

int generate_uniq_id(){
    FILE *fic;
    // printf("Load\n");
    int uniq_id;

    fic = fopen(NOM_FIC_UNIQ_ID, "r");
    // printf("Test\n");
    while (fscanf(fic, "%d", &uniq_id) != EOF)
    {
        //printf("%d\n", uniq_id);
    }
    uniq_id = uniq_id + 1;
    fic = fopen(NOM_FIC_UNIQ_ID, "w");
    //fwrite(uniq_id , 1 , sizeof(int) , fic );
    fprintf(fic, "%d", uniq_id);
    fclose(fic);
    return uniq_id;
}


int list_taille(Voiture* tete)
{
    Voiture* voit = tete;
    int size = 0;

    while (voit != NULL)
    {
        ++size;
        voit = voit->suiv;
    }

    return size;
}

void enregistrement_taille_file(Voiture* tete){
    FILE* fic;
    fic = fopen(NOM_FIC_TAILLE_FILE, "a+");
    fprintf(fic, "%d\n", list_taille(tete));
    fclose(fic);
}

bool find_index_liste(Voiture* tete, int index, int value_to_reach){
    Voiture* voit = tete;
    if(voit != NULL){
        if(voit->pos_route + index == value_to_reach){
            return true;
        }
    }
    while (voit != NULL)
    {
        voit = voit->suiv;
        if(voit != NULL){
            if(voit->pos_route + index == value_to_reach){
                return true;
            }
        }
    }
    return false;
}

bool find_index_liste_top(Voiture* tete, int index, int value_to_reach){
    Voiture* voit = tete;
    if(voit != NULL){
        if( index - voit->pos_route == value_to_reach){
            return true;
        }
    }
    while (voit != NULL)
    {
        voit = voit->suiv;
        if(voit != NULL){
            if(index - voit->pos_route == value_to_reach){
                return true;
            }
        }
    }
    return false;
}

