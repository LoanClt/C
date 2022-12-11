#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> /*Permet de créer des variables et fonctions de type bool*/
#include <time.h>


bool fichierTrouvable(FILE* fichier);
bool fichierPGM(char extensionP, int extension2);
void affichageTableau(int tableau[], int dim);
int maxListe(int tableau[], int dim);
int nombreNuance(int tableau[], int dim);
int couleurMoyenne(int tableau[], int dim);
int couleurPlusPresente(int tableau[], int dim);

/*Permet de vérifier si le fichier existe*/
bool fichierTrouvable(FILE* fichier){
    if (fichier != NULL) {
        return true;
    }
    else {
        return false;
    }
}

/*Permet de vérifier si le fichier est bien de type PGM de type P2 (et non P5, qui ne serait pas lisible par Histiogs*/
bool fichierPGM(char extensionP, int extension2){
    if (extension2 == 2){
        return true;
    }
    else{
        return false;
    }
}

/*Fonction de débug qui permet d'afficher toutes les valeurs d'un tableau*/
void affichageTableau(int tableau[], int dim){
    for (int i=0; i<dim; i++){
        printf("Valeur %d: %d\n", i, tableau[i]);
    }
}

/*Fonction qui retourne le maximum d'un tableau*/
int maxTableau(int tableau[], int dim){
    int a = tableau[0];
    for (int i = 0; i<dim; i++){
        if (tableau[i] > a) {
            a = tableau[i];
        }
    }
    return a;
}

/*Fonction qui compte le nombre de nuances ayant un nombre de pixel > 0; Retourne le nombre de nuance d'une image*/
int nombreNuance(int tableau[], int dim){
    int cpt = 0;
    for (int i = 0; i<dim; i++){
        if (tableau[i] != 0) {
            cpt++;
        }
    }
    return cpt;
}

/*Fonction qui calcule la moyenne d'un tableau donné*/
int couleurMoyenne(int tableau[], int dim){
    double nombreTotalCouleur = 0;

    for (int i =0; i<dim; i++) {
        nombreTotalCouleur += tableau[i];
    }

    double nuancePondere = 0;
    for (int i = 0; i<dim; i++){
        nuancePondere += i*tableau[i];
    }
    return nuancePondere/nombreTotalCouleur;
}

/*Fonction qui retourne l'indice du maximum d'un tableau*/
int couleurPlusPresente(int tableau[], int dim){
    int a = tableau[0];
    int indice = 0;
    for (int i = 0; i<dim; i++){
        if (tableau[i] > a) {
            a = tableau[i];
            indice = i;
        }
    }
    return indice;
}

int main()
{
    /*Définition des variables*/
    char extensionP;
    int extension2;
    int niveauMax;
    int dim;
    int niveauActuel;
    int longueurLargeur[2];
    int seuil;
    char reponse;
    char reponsePos = 'y';
    bool next = true;

    /*ASCII Art, car c'est stylé*/
    printf(" _   _ _     _   _                  \n");
    printf("| | | (_)   | | (_)                 \n");
    printf("| |_| |_ ___| |_ _  ___   ___   ___  \n");
    printf("|  _  | / __| __| |/ _ \\ / _ \\ / __| \n");
    printf("| | | | \\__ \\ |_| | (_) | (_| \\__ \\ \n");
    printf("\\_| |_/_|___/\\__|_|\\___/ \\__, |___/ \n");
    printf("                          __/ |     \n");
    printf("                         |___/      \n");
    printf("\n");
    printf("0                                   255\n");
    printf("<------------------------------------->\n");
    printf("Noir                               Blanc\n");
    printf("\n");


    FILE* fichier = fopen("robot_mall.pgm","r");
    FILE* imageSeuil = fopen("image_seuillee.pgm","w");

    /*Vérifie si le fichier existe et informe l'utilisateur*/
    if (!fichierTrouvable(fichier)){
        printf("/!\\| Fichier introuvable.\n");
        next = false;
    }

    /*Recherche de la première lettre ainsi que du premier nombre pour vérifier si il s'agit bien d'un type P2, et non P5*/
    fscanf(fichier,"%c",&extensionP);
    fscanf(fichier,"%d",&extension2);

    /*Vérifie si le fichier est bien un PGM P2 et informe l'utilisateur*/
    if (!fichierPGM(extensionP, extension2)){
        printf("/!\\| Le type de fichier est invalide (PGM P2).\n");
        next = false;
    }

    /*Si tous les fichiers necessaires ont été trouvés*/
    if (next){

        printf("0  | Fichie ASCII trouve\n");


        /*Récupération des dimensions de l'image*/
        for (int i=0; i<2; i++){
            fscanf(fichier,"%d",&longueurLargeur[i]);
        }

        /*Affectation de la dimension totale de l'image*/
        dim = longueurLargeur[0]*longueurLargeur[1]; // Colone * Ligne

        printf("1  | Voulez vous seuillez l'image ? (y/n) ");
        scanf("%c", &reponse);
        if (reponse == reponsePos){
            char nom[20] = {0};
            printf("1-1| Quelle est la valeur du seuil ? ");
            scanf("%d", &seuil);
            /*Ecris les fondations de l'image seuillé (P2, dimensions, niveau MAX (ici forcément 255) ...*/
            fprintf(imageSeuil, "P2\n%d %d\n255\n",longueurLargeur[0], longueurLargeur[1]);
            printf("1-1| Votre image seuillee va apparaitre (image_seuillee.pgm) a la fin\n\n");
        }

        /*Récupère la 3è et dernière information de l'image : le niveau Max*/
        fscanf(fichier,"%d",&niveauMax);

        int comptage[niveauMax+1]; /*+1 car il y a le niveau 0.*/

        /*On remplie d'office toutes les nuances de 0, si elles ne sont pas incrémentées ultérierement, elles seront d'offices à 0*/
        for (int k=0; k<niveauMax +1; k++){
            comptage[k] = 0;

        }


        for (int j = 0; j<dim; j++){
            fscanf(fichier,"%d",&niveauActuel);
            /*printf("%d / %d\n", j, niveauActuel);*/
            if (reponse == reponsePos){
                if (niveauActuel > seuil) {
                    fprintf(imageSeuil, " 255 ");
                } else {
                    fprintf(imageSeuil, " 0 ");
                }
            }
            comptage[niveauActuel]++; /*Parcours toute l'image, on incrémente la valeur associée à la nuance dans l'image de manière à avoir un tableau contenant 256 valeurs, avec le nombre des 256 nuances*/
        }


        /*NORMALISER LIMAGE*/
        int longueurAbs = 500;
        int occurenceMax = comptage[couleurPlusPresente(comptage, niveauMax+1)];
        int comptageNormal[niveauMax+1];

        /*Produit en croix classique*/
        for (int i = 0; i<niveauMax + 1; i++) {
            comptageNormal[i] = comptage[i] * longueurAbs / occurenceMax;
        }

        /*On débute avec un dim, à remplacer par max*/
        int colone_diag = longueurAbs; //256 nuances de gris, le nombre de colones est forcément longueurAbs*/


        char nom[20] = {0};
        printf("2  | Quel est le nom du fichier dans lequel l'histogramme sera enregistre? ");
        scanf("%s", nom);
        if (reponse == reponsePos){
            printf("3  | Creation de l'histogramme et de l'image seuillee a partir du fichier ASCII...\n");
        } else {
            printf("3  | Creation de l'histogramme a partir du fichier ASCII...\n");
        }


        /*Début du décompte pour la création du fichier ascii ...*/
        clock_t t;
        t = clock();


        FILE* diagramme = fopen(nom,"w");
        FILE* abscisse = fopen("svp.pgm","r");
        if (!fichierTrouvable(abscisse)){
            printf("\n/!\\| Fichier pour afficher correctement les axes absent !\n\n");
            fprintf(diagramme, "P2\n%d %d\n255\n",colone_diag + 120, niveauMax + 1); /*Si pas de fichier pour l'abs, on ajoute pas 120 pixels à l'image (lignes)*/
        } else {
            fprintf(diagramme, "P2\n%d %d\n255\n",colone_diag + 120, niveauMax + 1 + 120); //colonne/ligne
        }
        for (int i = 0; i<256; i++) {
            if (i == 2 || i == 20) {
                fprintf(diagramme, "255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255  255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255  255 255 255 255 255 255 255 255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 ");
            } else if (i > 2 && i < 20) {
                fprintf(diagramme, "255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255  255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255  255 255 255 255 255 255 255 255 0 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 0 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 ");
            } else if (i == 222 || i == 232 || i == 242) {
                fprintf(diagramme, "255 255 255 255 255 255 255 255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 255 255  255 255 255 255 255 255 255 255  255 255  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 255 255 255 255 255 255 255 255 255 255 255 255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 ");
            } else if (i > 222 && i < 232) {
                fprintf(diagramme, "255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 0 255 255 255 255 255 255 255 255 255 255 255 255  255 0 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 0 255 255 255 255 255  255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 ");
            } else if (i > 232 && i < 242) {
                fprintf(diagramme, "255 255 255 255 255 255 255 255 0 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255  255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 0 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255  255 255 255 255 255 255 255 255 255 255 255 255 255 0 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 ");
            }
            else {
                fprintf(diagramme, "255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255  255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255  255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 ");
            }
            if (comptageNormal[i] == 0) {
                for (int j = 0; j<colone_diag; j++) {
                    fprintf(diagramme, "255 ");
                }
                fprintf(diagramme, "\n");
            } else {
                for (int j = 0; j< colone_diag; j++) {
                    if (j < comptageNormal[i]) {
                        fprintf(diagramme, "0 ");
                    } else {
                        fprintf(diagramme, "255 ");
                    }
                }
                fprintf(diagramme, "\n");
            }
        }

        /* Finalement, on ajoute les axes*/
        int absi = 0;
        if (fichierTrouvable(abscisse)){
            for (int j = 0; j<620*120; j++){
                fscanf(abscisse,"%d",&absi);
                if (absi == 0) {
                    fprintf(diagramme, " 0 ");
                } else {
                    fprintf(diagramme, " 255 ");
                }
            }
        }


        t = clock() - t;
        double time_taken = ((double)t)/CLOCKS_PER_SEC;
        printf("4  | Histogramme genere en %f seconde\n", time_taken);
        printf("\n");
        printf("5  | Informations relatives a l'histogramme:\n");
        printf("5-1| Nombre total de pixels: %d\n", dim);
        printf("5-2| Nombre de nuances de gris: %d\n", nombreNuance(comptage, niveauMax+1));
        printf("5-3| Nuance moyenne: %d\n", couleurMoyenne(comptage, niveauMax+1));
        printf("5-4| Nuance la plus presente: %d (%d)\n", couleurPlusPresente(comptage, niveauMax+1), comptage[couleurPlusPresente(comptage, niveauMax+1)]);

    } else {
        printf("/!\\| Fin du processus ...\n");
    }
}
