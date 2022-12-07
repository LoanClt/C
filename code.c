#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> /*Permet de créer des fonctions de type bool*/
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

/*Permet de vérifier si le fichier est bien de type PGM, il manque la vérif de ¨P*/
bool fichierPGM(char extensionP, int extension2){
    if (extension2 == 2){
        return true;
    }
    else{
        return false;
    }
}

void affichageTableau(int tableau[], int dim){
    for (int i=0; i<dim; i++){
        printf("Valeur %d: %d\n", i, tableau[i]);
    }
}

int maxTableau(int tableau[], int dim){
    int a = tableau[0];
    for (int i = 0; i<dim; i++){
        if (tableau[i] > a) {
            a = tableau[i];
        }
    }
    return a;
}

int nombreNuance(int tableau[], int dim){
    int cpt = 0;
    for (int i = 0; i<dim; i++){
        if (tableau[i] != 0) {
            cpt++;
        }
    }
    return cpt;
}

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

int couleurPlusPresente(int tableau[], int dim){
    int a = tableau[0];
    int indice = 0;
    for (int i = 0; i<dim; i++){
        if (tableau[i] > a) {
            indice = i;
        }
    }
    return indice;
}

int main()
{
    char extensionP;
    int extension2;
    int niveauMax;
    int niveauActuel;
    int longueurLargeur[2];
    int seuil;
    char reponse;
    char reponsePos = 'y';

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


    FILE* fichier = fopen("tigre.pgm","r");
    FILE* imageSeuil = fopen("image_seuillee.pgm","w");

    if (!fichierTrouvable(fichier)){
        printf("Fichier introuvable.\n");
    }

    fscanf(fichier,"%c",&extensionP);
    fscanf(fichier,"%d",&extension2);

    if (!fichierPGM(extensionP, extension2)){
        printf("Le type de fichier est invalide (PGM).\n");
    }

    printf("0  | Fichie ASCII trouve\n");


    for (int i=0; i<2; i++){
        fscanf(fichier,"%d",&longueurLargeur[i]);
    }

    int dim = longueurLargeur[0]*longueurLargeur[1]; // Colone * Ligne

    printf("1  | Voulez vous seuillez l'image ? (y/n) ");
    scanf("%c", &reponse);
    if (reponse == reponsePos){
        char nom[20] = {0};
        printf("1-1| Quelle est la valeur du seuil ? ");
        scanf("%d", &seuil);
        fprintf(imageSeuil, "P2\n%d %d\n255\n",longueurLargeur[0], longueurLargeur[1]);
    }

    fscanf(fichier,"%d",&niveauMax);

    int comptage[niveauMax+1]; /*+1 car il y a le niveau 0. Le compileur remplie le reste de 0*/

    for (int k=0; k<niveauMax +1; k++){
        comptage[k] = 0;

    }


    for (int j = 0; j<dim; j++){
        fscanf(fichier,"%d",&niveauActuel);
        if (reponse == reponsePos){
            if (niveauActuel > seuil) {
                fprintf(imageSeuil, " 255 ");
            } else {
                fprintf(imageSeuil, " 0 ");
            }
        }
        comptage[niveauActuel]++;
    }


    /*NORMALISER LIMAGE*/
    int longueurAbs = 500;
    int occurenceMax = comptage[couleurPlusPresente(comptage, niveauMax+1)];
    int comptageNormal[niveauMax+1];

    for (int i = 0; i<niveauMax + 1; i++) {
        comptageNormal[i] = comptage[i] * longueurAbs / occurenceMax;
    }

    /*On débute avec un dim, à remplacer par max*/
    int colone_diag = maxTableau(comptageNormal, niveauMax + 1); //256 nuances de gris


    char nom[20] = {0};
    printf("2  | Quel est le nom du fichier dans lequel l'histogramme sera enregistre? ");
    scanf("%s", nom);
    if (reponse == reponsePos){
        printf("3  | Creation de l'histogramme et de l'image seuillee a partir du fichier ASCII...\n");
    } else {
        printf("3  | Creation de l'histogramme a partir du fichier ASCII...\n");
    }


    clock_t t;
    t = clock();


    FILE* diagramme = fopen(nom,"w");
    fprintf(diagramme, "P2\n%d %d\n255\n",colone_diag + 120, niveauMax + 1 + 120); //colonne/ligne
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
            fprintf(diagramme, "255 255 255 255 255 255 255 255 0 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255  255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 0 255 255 255 255 255 255 255 255 255 255 255 255 255 0 255 255 255 255 255  255 255 255 255 255 255 255 255 255 255 255 255 255 0 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 ");
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

    int absi = 0;
    FILE* abscisse = fopen("text.pgm","r");
    for (int j = 0; j<620*120; j++){
        scanf(abscisse,"%d",&absi);
        if (absi == 0) {
            fprintf(diagramme, " 0 ");
        } else {
            fprintf(diagramme, " 255 ");
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
}
