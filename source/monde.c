//
//  monde.c
//  gare_aux_chats
//
//  Created by Pierrick Delrieu on 18/03/2020.
//  Copyright © 2020 Pierrick Delrieu. All rights reserved.
//

#include "fonctions.h"


int ** creation_monde_vide(int hauteur, int largeur)
{
    int **monde = NULL;
    int i;
    
    //Allocation espace dynamique
    monde = (int **) malloc(hauteur * sizeof(int *));
    
    for(i=0; i<hauteur; i++)
    {
        monde[i] = (int *) calloc(largeur, sizeof(int));
    }

    return(monde);
}

void affichage_monde(int **monde)
{
    int i,j;
    
    for(i=0; i<HEIGHT; i++)
    {
        for(j=0; j<WIDTH; j++)
        {
            if(monde[i][j] == CHAT)
            {
                printf("C ");
            }
            else if(monde[i][j] == CASE_VIDE)
            {
                printf("  ");
            }
            else
            {
                printf("%d ",monde[i][j]);
            }
        }
        printf("\n");
    }
}


void desalocation_monde(int **monde)
{
    int i;
    for(i=0; i<HEIGHT; i++)
    {
        free(monde[i]);
    }
    
    free(monde);
}

void supr_console()
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

int condition_arret_partie(int **monde)
{
    int i,j;
    int retour = 0; //0 si arret de partie et 1 sinon
    
    for(i=0; i<HEIGHT; i++)
    {
        for(j=0; j<WIDTH; j++)
        {
            if((monde[i][j] == SOURIS1) || (monde[i][j] == SOURIS2) || (monde[i][j] == SOURIS3) || (monde[i][j] == SOURIS4) || (monde[i][j] == SOURIS5))
            {
                retour = 1;
            }
        }
    }
    
    return (retour);
}
