#ifndef INITIALISATION_H_INCLUDED
#define INITIALISATION_H_INCLUDED
#include "liste.h"

typedef enum box box ;
enum box
{
    noir, blanc, gris
};

typedef box *ligne;

typedef struct picross picross ;
struct picross
{
    int transpose;
    int nb_lignes;
    int nb_colonnes;

    liste *ind_lignes;

    liste *ind_colonnes;

    ligne *grille;
};

typedef struct JobList{ // Gère les prioritées, changement probable de place.

int *prioriteLigne; //init a 1

int *prioriteColonne; //idem

int nb_lignes;

int nb_colonnes;

int taille;

}JobList;

picross Initialisation ();

void afficherGrille(picross);

#endif // INITIALISATION_H_INCLUDED
