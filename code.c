#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> /*Permet de créer des fonctions de type bool*/


bool fichierTrouvable(FILE* fichier);
bool fichierPGM(char extensionP, int extension2);
void affichageTableau(int tableau[], int dim);

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

int main()
{
    char extensionP;
    int extension2;
    int niveauMax;
    int niveauActuel;
    int longueurLargeur[2];

    FILE* fichier = fopen("damier.pgm","r");

    if (!fichierTrouvable(fichier)){
        printf("Fichier introuvable.\n");
    }

    fscanf(fichier,"%c",&extensionP);
    fscanf(fichier,"%d",&extension2);

    if (!fichierPGM(extensionP, extension2)){
        printf("Le type de fichier est invalide (PGM).\n");
    }

    for (int i=0; i<2; i++){
        fscanf(fichier,"%d",&longueurLargeur[i]);
    }

    int dim = longueurLargeur[0]*longueurLargeur[1];

    fscanf(fichier,"%d",&niveauMax);

    int comptage[niveauMax+1]; /*+1 car il y a le niveau 0. Le compileur remplie le reste de 0*/

    for (int k=0; k<niveauMax +1; k++){
        comptage[k] = 0;

    }

    for (int j = 0; j<dim; j++){
        fscanf(fichier,"%d",&niveauActuel);
        comptage[niveauActuel]++;
    }

    printf("%d", comptage[0]);

    affichageTableau(comptage, niveauMax +1);
}
