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

    fscanf(fichier,"%d",&niveauMax);

    int comptage[niveauMax+1]; /*+1 car il y a le niveau 0. Le compileur remplie le reste de 0*/

    for (int k=0; k<niveauMax +1; k++){
        comptage[k] = 0;

    }

    for (int j = 0; j<dim; j++){
        fscanf(fichier,"%d",&niveauActuel);
        comptage[niveauActuel]++;
    }

    /*On débute avec un dim, à remplacer par max*/
    int colone_diag = maxTableau(comptage, niveauMax + 1); //256 nuances de gris


    char nom[20] = {0};
    printf("1  | Quel est le nom du fichier dans lequel l'histogramme sera enregistre? (s'il existe deja, il sera remplace)\n");
    scanf("%s", nom);
    printf("2  | Creation de l'histogramme a partir du fichier ASCII...\n");


    clock_t t;
    t = clock();


    FILE* diagramme = fopen(nom,"w");
    fprintf(diagramme, "P2\n%d %d\n255\n",colone_diag, niveauMax +1); //colonne/ligne
    for (int i = 0; i<256; i++) {
        if (comptage[i] == 0) {
            for (int j = 0; j<colone_diag; j++) {
                fprintf(diagramme, " 255 ");
            }
            fprintf(diagramme, "\n");
        } else {
            for (int j = 0; j< colone_diag; j++) {
                    if (j < comptage[i]) {
                        fprintf(diagramme, " 0 ");
                    } else {
                        fprintf(diagramme, " 255 ");
                    }
            }
            fprintf(diagramme, "\n");
        }
    }

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("3  | Histogramme genere en %f seconde\n", time_taken);
    printf("\n");
    printf("4  | Informations relatives a l'histogramme:\n");
    printf("4-1| Nombre total de pixels: %d\n", dim);
    printf("4-2| Nombre de nuances de gris: %d\n", nombreNuance(comptage, 256));
    printf("4-3| Nuance moyenne: %d\n", couleurMoyenne(comptage, 256));
    printf("4-4| Nuance la plus presente: %d (%d)\n", couleurPlusPresente(comptage, 256), comptage[couleurPlusPresente(comptage, 256)]);
}
