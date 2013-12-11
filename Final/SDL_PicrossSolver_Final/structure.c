#include <stdlib.h>
#include <stdio.h>
#include "structure.h"
#include "picross.h"

//LIGNES

//Fonction indiquant si une ligne est complete (aucune case grise) ou non.
int ligneFinie(ligne m_ligne, int longueur_ligne)
{
    int i=0;
    while (i<longueur_ligne)
    {
        if (m_ligne[i]==gris)
        {
            return 0;
        }
        i++;
    }
    return 1;
}

//Fonction indiquant si une ligne est complete (aucune case grise) et respecte les indices.
int ligneSolution(ligne m_ligne, liste ind_lignes, int longueur_ligne)
{

    liste indices = ind_lignes;//copie de la liste d'indices
    int i=0; //position sur la ligne
    int cpt; //compteur de cases pleines

//afficherListe(indices);

    while (indices != NULL)
    {
        while (i < longueur_ligne && m_ligne[i] == blanc/*vide*/)
        {
            i++;//on passe toutes les cases vides au debut de la ligne // et les cases blanches entre chaque groupe de cases pleines

        }

        cpt=0;
        while (i < longueur_ligne && m_ligne[i] == noir/*plein*/)
        {
            cpt++;//on compte le nombre de cases pleines consecutives
            i++;
        }

        if (cpt != indices->info) return 0;//renvoie 0 si le nombre de cases consecutives ne correspond pas à l'indice de la liste
        indices = indices->succ;//on passe a l'indice suivant dans la liste
    }

    while (i < longueur_ligne && m_ligne[i] == blanc/*vide*/)
    {

        i++;//on passe les cases restantes jusqu'a la fin de la ligne
    }


    if (i != longueur_ligne) return 0;
    /*on verifie que l'on est bien a la fin de la ligne
    (ne renvoie jamais 0 normalement puisque que la ligne
    doit etre correctement formee pour arriver a ce
    point de l'algorithme)*/
    else return 1;//renvoie true

}

//Fonction calculant le nombre minimum de cases devant être coloriées pour completer une ligne,
//la fonction renvoie la difference entre la longueur de la ligne et le nombre sus-cite.
int degreLiberte(liste indices, int tailleLigne)
{

    int dLiberte=0;
    liste tempIndices;
    tempIndices = indices;
    dLiberte=tailleLigne-(somElements(tempIndices)+nbElements(tempIndices)-1);
    return dLiberte;

}

//GRILLE

picross Initialisation (int choix)
{
    picross picross1;
    int i,j,valeur_lue,nb_indices;
    FILE* fichier=NULL;
    /* On charge une variable fichier qui va contenir notre fichier txt, puis on l'ouvre grÃ¢ce Ã  fopen */
    if (choix ==0 )
    {

    fichier=fopen("Initialisation.txt","r+");
    }
    if (choix==1)
    {
    fichier=fopen("Initialisation.txt.55","r+");
    }
    if (choix==2)
    {
        fichier=fopen("Initialisation.txt.1010","r+");
    }

    /* Si on a bien reussi a ouvrir le fichier, alors on peut travailler dessus */
    if (fichier != NULL)
    {picross1.transpose=0;
        /* On lit les deux premieres valeurs du fichier initialisation.txt, qui sont les nb de lignes et nb de colonnes. On les affiche */
        fscanf(fichier, "%d %d \n\n",&picross1.nb_lignes, &picross1.nb_colonnes);
     //   printf("Votre grille Picross a %d lignes et %d colonnes.\n\n",picross1.nb_lignes,picross1.nb_colonnes);

        /* Malloc des tableaux contenant les listes d'indices */
        picross1.ind_lignes=malloc((picross1.nb_lignes)*sizeof(cell));
        picross1.ind_colonnes=malloc((picross1.nb_colonnes)*sizeof(cell));

        /* On initialise les listes d'indices sur lignes Ã  NULL */
        for(i=0;i<=picross1.nb_lignes;i++)
        {
            picross1.ind_lignes[i]=NULL;
        }

        /* On initialise les listes d'indices sur colonnes Ã  NULL */
        for(i=0;i<=picross1.nb_colonnes;i++)
        {
            picross1.ind_colonnes[i]=NULL;
        }

        /* On va parcourir le fichier initialisation.txt. Tant que la valeur lue est diffÃ©rente de -1, alors on ajoute en fin de la liste d'indice correspondante
            la valeur, puis on scan la valeur d'aprÃ¨s... On fait une fois pour les lignes, une autre pour les colonnes.*/

        //printf("  Liste des indices : \n\n");

        /* Pour les lignes:   */
        for(i=0; i<picross1.nb_lignes; i++)
        {
            nb_indices=0;
            valeur_lue=0;
            int somme_ind_ligne=0;


            while(valeur_lue != -1)
            {
                nb_indices++;
                fscanf(fichier, "%d", &valeur_lue);
                if( valeur_lue!= -1)
                {
                    picross1.ind_lignes[i]=ajouterEnFin(picross1.ind_lignes[i],valeur_lue);
                    somme_ind_ligne=somme_ind_ligne + valeur_lue;
                }
            }
            //                                                  ²   ²   ²   ²       ²   +-if (somme_ind_ligne >picross1.nb_lignes ) { *verif=0;}
           // printf("La ligne %d a %d indices.\n", i+1, nb_indices-1);
        }


        //printf("\n\n");


        /* Pour les colonnes :   */
        for(i=0; i<picross1.nb_colonnes; i++)
        {
            nb_indices=0;
            valeur_lue=0;
            int somme_ind_col=0;

            while(valeur_lue != -1)
            {
                nb_indices++;
                fscanf(fichier, "%d", &valeur_lue);

                if (valeur_lue != -1)
                {
                    picross1.ind_colonnes[i]=ajouterEnFin(picross1.ind_colonnes[i],valeur_lue);
                    somme_ind_col=somme_ind_col + valeur_lue;
                }
            }
            //if (somme_ind_col > picross1.nb_colonnes) { *verif=0;}
            //printf("La colonne %d a %d indices.\n", i+1, nb_indices-1);

        }
       // printf(" \n");

    }

    /* Sinon, on affiche un message d'erreur */
    else
    {
        printf("Impossible d'ouvrir le fichier Initialisation...");
    }

    fclose(fichier); //on libÃ¨re la mÃ©moire associÃ©e au fichier


    /* On initialise la grille Ã  GRIS partout !  TrÃ¨s IMPORTANT sinon on peut pas travailler dessus  */
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

//Fonction chargée d'afficher une grille de picross au sein d'une console.
void afficherGrille(picross picross1)
{

    printf("\n\nVotre grille Picross a %d lignes et %d colonnes.\n\n\n",picross1.nb_lignes,picross1.nb_colonnes);



    int i, j;
    for (i=0; i<picross1.nb_lignes;i++)
    {
        for (j=0; j<picross1.nb_colonnes;j++)
        {

            if (picross1.grille[i][j]==gris)
            {
                printf(" ? ");
            }
            if (picross1.grille[i][j]==noir)
            {
                printf(" X ");
            }
            if (picross1.grille[i][j]==blanc)
            {
                printf(" 0 ");
            }
        }
        printf("\n");
    }
}

//Fonction chargée de transposer la grille de picross.
picross transposer(picross picross1)
{

    int i, j, temp;
    box tempB;

    int nb_lig=picross1.nb_lignes;
    int nb_col=picross1.nb_colonnes;

//nb_lig reçoit le max de nbLignes, nbColonnes
    if (nb_lig > nb_col)
    {
        temp=nb_col;
        nb_col =nb_lig;
        nb_lig=temp;
    }

//Echange des valeurs dans les cases
    for (i=0;i<nb_lig;i++)
    {
        for (j=i+1;j<nb_col;j++)
        {
            tempB=picross1.grille[i][j];
            picross1.grille[i][j]=picross1.grille[j][i];
            picross1.grille[j][i]=tempB;
        }
    }

//Mise à jour de la variable transpose dans la structure du picross
    picross1.transpose++;
    return picross1;

}

//Fonction verifiant si une grille de picross est complete (aucune case grise) et respecte les indices
int verification(picross solution)
{

    int i;

//Verification de toutes les lignes.
    for (i=0;i<solution.nb_lignes;i++)
    {
//Si une ligne n'est pas correcte alors la grille n'est pas correcte.
        if (ligneSolution(solution.grille[i], solution.ind_lignes[i], solution.nb_colonnes) == 0)
        {
            return 0;
        }
    }

    solution=transposer(solution);

//Idem pour les colonnes.
    for (i=0;i<solution.nb_colonnes;i++)
    {

        if (ligneSolution(solution.grille[i], solution.ind_colonnes[i], solution.nb_lignes) == 0)
        {

            return 0;
        }
    }

    solution=transposer(solution);

//Renvoie vrai car une grille de picross a par definition une unique solution.
    return 1;

}

//Fonction chargée de recopier un picross.
picross copierPicross(picross source)
{
    int i,j;
    picross copie;
            copie.ind_lignes=malloc((source.nb_lignes)*sizeof(cell));
        copie.ind_colonnes=malloc((source.nb_colonnes)*sizeof(cell));
        copie.grille=malloc((source.nb_lignes)*sizeof(ligne));
                for (i=0; i<source.nb_lignes;i++)
        {
            copie.grille[i]=malloc((source.nb_colonnes)*sizeof(box));

        }

    copie.transpose=source.transpose;
    copie.nb_lignes=source.nb_lignes;
    copie.nb_colonnes=source.nb_colonnes;
    copie.ind_lignes=source.ind_lignes;
    copie.ind_colonnes=source.ind_colonnes;
    for (i=0;i<copie.nb_lignes;i++)
    {
        for (j=0;j<copie.nb_colonnes;j++)
        {
            copie.grille[i][j]=source.grille[i][j];
        }
    }
    return copie;
}

int picrossFini(picross pic)
{
    int i,j;
    for(i=0;i<pic.nb_lignes;i++)
    {
        for(j=0;j<pic.nb_colonnes;j++)
        {
            if (pic.grille[i][j]==gris)
            {
                return 0;
            }
        }
    }
    return 1;
}

//JOBLIST


//Fonction chargée d'initialiser la structure gérant l'envoi des lignes au regles de resolution (JobList)
JobList initJobList(picross pic1)
{

    JobList joblist1;
    int i=0;

    joblist1.nb_lignes=0;
    joblist1.nb_colonnes=0;


    joblist1.prioriteLigne=malloc((pic1.nb_lignes)*sizeof(int));

    for (i=0;i<=pic1.nb_lignes-1;i++)
    {
        joblist1.prioriteLigne[i]=1;
        joblist1.nb_lignes++;
    }

    joblist1.prioriteColonne=malloc((pic1.nb_colonnes)*sizeof(int));
    for (i=0;i<=pic1.nb_colonnes-1;i++)
    {
        joblist1.prioriteColonne[i]=1;
        joblist1.nb_colonnes++;
    }


    prioriteup(joblist1.prioriteLigne, pic1.ind_lignes, pic1.nb_lignes);
    prioriteup(joblist1.prioriteColonne, pic1.ind_colonnes, pic1.nb_colonnes);


    return joblist1;

}

void prioriteup(int *prio, liste *indices, int nb_elem)
{

    int i;


    for (i=0;i<nb_elem;i++)
    {

        if (degreLiberte(indices[i], nb_elem) == 0) prio[i]+=3;
        if (degreLiberte(indices[i], nb_elem) == 1) prio[i]+=2;
        if (degreLiberte(indices[i], nb_elem) == 2) prio[i]+=1;

    }

}

prioEtInd prioMax(int *prio, int taille)
{

    prioEtInd pei;
    int i=0;
    pei.indice=0;
    pei.priorite=0;

    while (i<taille)
    {

        if (prio[i]>pei.priorite)
        {
            pei.priorite=prio[i];
            pei.indice=i;
        }

        i++;
    }

    return pei;
}

void majJobList(int *prio, liste indices)
{

    liste temp=indices;

    while (temp != NULL)
    {

        prio[temp->info]++;
        temp=temp->succ;

    }
}

int resolution(JobList joblist1, picross picross1)
{

    liste indicesModifies=NULL;
    int ligneatraiter=0;
    int check=0;


    while (prioMax(joblist1.prioriteLigne,joblist1.nb_lignes).priorite > 0 || prioMax(joblist1.prioriteColonne, joblist1.nb_colonnes).priorite > 0)
    {

        while (prioMax(joblist1.prioriteLigne,joblist1.nb_lignes).priorite > 0)
        {

            check=0;
            indicesModifies=NULL;
            ligneatraiter=prioMax(joblist1.prioriteLigne, joblist1.nb_lignes).indice;


            check=caseMinMax(picross1.ind_lignes[ligneatraiter], picross1.grille[ligneatraiter], picross1.nb_colonnes, &indicesModifies);

            if (check==0)
            {
                printf("Faute : caseMinMax sur ligne : %i\n",ligneatraiter);
                return 0;
            }

            check=0;
            check=box_blanc(picross1.grille[ligneatraiter],picross1.ind_lignes[ligneatraiter],picross1.nb_colonnes, &indicesModifies);

            if (check==0)
            {
                printf("Faute : box_blanc sur ligne : %i\n",ligneatraiter);
                return 0;
            }


            check=bord_box_blanc(picross1.grille[ligneatraiter],picross1.ind_lignes[ligneatraiter],picross1.nb_colonnes, &indicesModifies);

            if (check==0)
            {
                printf("Faute : bbb sur ligne : %i\n",ligneatraiter);
                return 0;
            }

           check=minimal_box_blanc(picross1.grille[ligneatraiter],picross1.ind_lignes[ligneatraiter],picross1.nb_colonnes, &indicesModifies);

            if (check==0)
            {
               printf("Faute : minimal_box_blanc sur ligne : %i\n",ligneatraiter);
                return 0;
            }



            joblist1.prioriteLigne[ligneatraiter]=0;
            if (indicesModifies!=NULL)
            {
                joblist1.prioriteLigne[ligneatraiter]=1;
            }
            majJobList(joblist1.prioriteColonne, indicesModifies);



        }



        picross1=transposer(picross1);




        while (prioMax(joblist1.prioriteColonne,joblist1.nb_colonnes).priorite > 0)
        {


            check=0;
            indicesModifies=NULL;
            ligneatraiter=prioMax(joblist1.prioriteColonne, joblist1.nb_colonnes).indice;


            check=caseMinMax(picross1.ind_colonnes[ligneatraiter], picross1.grille[ligneatraiter], picross1.nb_lignes, &indicesModifies);

            if (check==0)
            {
              printf("Faute : caseMinMax sur ligne : %i\n",ligneatraiter);
                return 0;
            }

            check=0;
            check=box_blanc(picross1.grille[ligneatraiter],picross1.ind_colonnes[ligneatraiter],picross1.nb_lignes, &indicesModifies);

            if (check==0)
            {
                printf("Faute : box_blanc sur ligne : %i\n",ligneatraiter);
                return 0;
            }


            check=bord_box_blanc(picross1.grille[ligneatraiter],picross1.ind_colonnes[ligneatraiter],picross1.nb_lignes, &indicesModifies);

            if (check==0)
            {
                printf("Faute : bbb sur ligne : %i\n",ligneatraiter);
                return 0;
            }

            check=minimal_box_blanc(picross1.grille[ligneatraiter],picross1.ind_colonnes[ligneatraiter],picross1.nb_lignes, &indicesModifies);

            if (check==0)
            {
                printf("Faute : minimal_box_blanc sur ligne : %i\n",ligneatraiter);
                return 0;
            }

            joblist1.prioriteColonne[ligneatraiter]=0;
            if (indicesModifies!=NULL)
            {
                joblist1.prioriteColonne[ligneatraiter]=1;
            }
            majJobList(joblist1.prioriteLigne, indicesModifies);
        }


        picross1=transposer(picross1);


    }
    return 1;
}

//HYPOTHESES

int premCaseGrise(int *lig, int *col, picross pic)
{
    int i, j;
    for (i=0;i<pic.nb_lignes;i++)
    {
        for (j=0;j<pic.nb_colonnes;j++)
        {
            if (pic.grille[i][j]==gris)
            {
                *lig=i;
                *col=j;
                return 1;
            }
        }
    }
    return 0;
}

int generateurHypo(picross test, picross *source, int *compt)
{
    int i, j, check, hypo;
    *compt=*compt+1;
    if (*compt>1)
    {
        check=resolution(initJobList(test),test);
        if (check==0)
        {
            return 0;
        }
    }
    if (picrossFini(test)==1)
    {
        if (verification(test)==1)
        {
            *source=copierPicross(test);
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        picross test1;
        test1=copierPicross(test);
        hypo=premCaseGrise(&i,&j,test);
        if (hypo==0)
        {
            return 0;
        }
        test1.grille[i][j]=noir;
        hypo=generateurHypo(test1, source, compt);
        if (hypo!=1)
        {
            free(test1.grille);
            test1=copierPicross(test);
            test1.grille[i][j]=blanc;
            return generateurHypo(test1, source, compt);
        }
        else
        {
            return 1;
        }
    }
}

void resolveur(picross picross1)
{


    JobList jobl1;

    jobl1=initJobList(picross1);

    resolution(jobl1, picross1);


   if ((picross1.transpose%2)==1) picross1=transposer(picross1);


    picross pictest;
    pictest=copierPicross(picross1);
    int compt=0;
    generateurHypo(pictest,&picross1,&compt);

    if((picross1.transpose%2)==1) picross1=transposer(picross1);



}
