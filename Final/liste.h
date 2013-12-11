#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

typedef struct cell cell ;
struct cell
{
    int info;
    cell *succ;
};

typedef cell* liste;

liste ajouterEnTete(liste, int);    //fonction qui rajoute un entier en tete d'une liste

liste ajouterEnFin(liste, int);     //fonction qui rajoute un entier en fin d'une liste

void afficherListe(liste);          //fonction qui affiche une liste

int nbElements(liste);              //fonction qui renvoie le nombre d'elements d'une liste

int somElements(liste);             //fonction qui renvoie la somme des elements d'une liste

int elementMax(liste);              //fonction qui renvoie l'element maximum d'une liste

int elementMin(liste);              //fonction qui renvoie l'element minimum d'une liste

#endif // LISTE_H_INCLUDED
