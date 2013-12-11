#include <stdio.h>
#include <stdlib.h>
#include "initialisation.h"
#include "liste.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>


void afficherGrille(picross picross1)
{

    printf("\n\n Votre grille Picross a %d lignes et %d colonnes.\n\n\n",picross1.nb_lignes,picross1.nb_colonnes);



    int i, j;
    for (i=0; i<picross1.nb_lignes;i++)
    {
        for(j=0; j<picross1.nb_colonnes;j++)
        {

            if (picross1.grille[i][j]==gris)
            {
                printf("\t ? \t");
            }
            if (picross1.grille[i][j]==noir)
            {
                printf("\t X \t");
            }
            if (picross1.grille[i][j]==blanc)
            {
                printf("\t 0 \t");
            }
        }
        printf("\n\n");
    }
}

picross Initialisation ()
{
    picross picross1;
    int i,j,valeur_lue,nb_indices;

    /* On charge une variable fichier qui va contenir notre fichier txt, puis on l'ouvre grâce à fopen */
    FILE* fichier=NULL;
    fichier=fopen("Initialisation.txt","r+");

    /* Si on a bien reussi a ouvrir le fichier, alors on peut travailler dessus */
    if (fichier != NULL)
    {
        /* On lit les deux premieres valeurs du fichier initialisation.txt, qui sont les nb de lignes et nb de colonnes. On les affiche */
        fscanf(fichier, "%d %d \n\n",&picross1.nb_lignes, &picross1.nb_colonnes);
        printf("Votre grille Picross a %d lignes et %d colonnes.\n\n",picross1.nb_lignes,picross1.nb_colonnes);

        /* Malloc des tableaux contenant les listes d'indices */
        picross1.ind_lignes=malloc((picross1.nb_lignes)*sizeof(cell));
        picross1.ind_colonnes=malloc((picross1.nb_colonnes)*sizeof(cell));

        /* On initialise les listes d'indices sur lignes à NULL */
        for(i=0;i<=picross1.nb_lignes;i++)
        {
            picross1.ind_lignes[i]=NULL;
        }

        /* On initialise les listes d'indices sur colonnes à NULL */
        for(i=0;i<=picross1.nb_colonnes;i++)
        {
            picross1.ind_colonnes[i]=NULL;
        }

        /* On va parcourir le fichier initialisation.txt. Tant que la valeur lue est différente de -1, alors on ajoute en fin de la liste d'indice correspondante
            la valeur, puis on scan la valeur d'après... On fait une fois pour les lignes, une autre pour les colonnes.*/

        printf("  Liste des indices : \n\n");

        /* Pour les lignes:   */
        for(i=0; i<picross1.nb_lignes; i++)
        {
            nb_indices=0;
            valeur_lue=0;

            while(valeur_lue != -1)
            {
                nb_indices++;
                fscanf(fichier, "%d", &valeur_lue);
                if( valeur_lue!= -1)
                {
                    picross1.ind_lignes[i]=ajouterEnFin(picross1.ind_lignes[i],valeur_lue);
                }
            }
            printf("La ligne %d a %d indices.\n", i+1, nb_indices-1);
        }

        printf("\n\n");


        /* Pour les colonnes :   */
        for(i=0; i<picross1.nb_colonnes; i++)
        {
            nb_indices=0;
            valeur_lue=0;

            while(valeur_lue != -1)
            {
                nb_indices++;
                fscanf(fichier, "%d", &valeur_lue);

                if (valeur_lue != -1)
                {
                    picross1.ind_colonnes[i]=ajouterEnFin(picross1.ind_colonnes[i],valeur_lue);
                }
            }
            printf("La colonne %d a %d indices.\n", i+1, nb_indices-1);

        }
        printf(" \n");

    }

    /* Sinon, on affiche un message d'erreur */
    else
    {
        printf("Impossible d'ouvrir le fichier Initialisation...");
    }

    fclose(fichier); //on libère la mémoire associée au fichier


    /* On initialise la grille à GRIS partout !  Très IMPORTANT sinon on peut pas travailler dessus  */
    picross1.grille=malloc((picross1.nb_lignes)*sizeof(ligne));


        for (i=0; i<picross1.nb_lignes;i++)
        {
            picross1.grille[i]=malloc((picross1.nb_colonnes)*sizeof(box));

            for(j=0; j<picross1.nb_colonnes;j++)
            {
                picross1.grille[i][j]=gris;
            }
        }

    return picross1;

}
