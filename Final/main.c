#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "picross.h"



int main()
{
    printf("Entrez le nom du fichier du picross a resoudre : ");
    char nom[30];
    scanf("%s",nom);
    printf("\n");
    resolveur(nom);
    //system("PAUSE");
    return 0;
}
