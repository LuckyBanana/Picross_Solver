#include "liste.h"
#include <stdio.h>
#include <stdlib.h>


liste ajouterEnTete (liste L, int valeur)
{
    cell *nouvelListe = malloc (sizeof(cell) );
    nouvelListe->info=valeur;
    nouvelListe->succ=L;
    return nouvelListe;

}

liste ajouterEnFin(liste L, int valeur)
{
    cell *nouvelElement = malloc(sizeof(cell));

    nouvelElement->info = valeur;

    nouvelElement->succ = NULL;

    if(L == NULL)
    {
        return nouvelElement;
    }
    else
    {
        cell* temp=L;
        while(temp->succ != NULL)
        {
            temp = temp->succ;
        }
        temp->succ = nouvelElement;

        return L;
    }
}

void afficherListe(liste L)
{
    cell *temp=L;
    printf("(");
    while(temp != NULL)
    {

        printf("  %d  ",temp->info);
        temp=temp->succ;
    }
    printf(")\n");
}

int nbElements(liste m_liste){

liste copie_liste;
int cpt=0;
copie_liste=m_liste;
while(copie_liste != NULL){
cpt++;
copie_liste=copie_liste->succ;
}

return cpt;
}

int somElements(liste m_liste){

liste copie_liste;
int cpt=0;
copie_liste=m_liste;
while(copie_liste != NULL){
cpt=cpt+copie_liste->info;
copie_liste=copie_liste->succ;
}

return cpt;
}

int elementMax(liste L)
{
    int a;
    a=L->info;
    while (L!=NULL)
    {
        if (a<(L->info)) a=(L->info);
        L=L->succ;
    }
    return a;
}

int elementMin(liste L)
{
    int a;
    a=L->info;
    while (L!=NULL)
    {
        if (a>(L->info)) a=(L->info);
        L=L->succ;
    }
    return a;
}

