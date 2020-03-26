//
//  chats.c
//  gare_aux_chats
//
//  Created by Pierrick Delrieu on 18/03/2020.
//  Copyright © 2020 Pierrick Delrieu. All rights reserved.
//

#include "fonctions.h"



void random_ajout_chat(int ***monde)
{
    int haut_droite;
    int bas_droite;
    int haut_gauche;
    int bas_gauche;
    
    haut_droite = 1 + (rand() % 4);
    bas_droite = 1 + (rand() % 4);
    haut_gauche = 1 + (rand() % 4);
    bas_gauche = 1 + (rand() % 4);
    
    if(haut_droite == 1)
    {
        *(*(*monde) + (WIDTH-1)) = CHAT;
    }
    
    if(bas_droite == 1)
    {
        *(*(*monde + (HEIGHT-1)) + (WIDTH-1)) = CHAT;
    }
    
    if(haut_gauche == 1)
    {
        *(*(*monde)) = CHAT;
    }
    
    if(bas_gauche == 1)
    {
        *(*(*monde + (HEIGHT-1))) = CHAT;
    }
}

int case_valide_chat(int i, int j, int **monde)
{
    // 1 si plateau[i][j] valide et 0 sinon

    int valide = 0;

    if((i<HEIGHT) && (j<WIDTH) && (i>=0) && (j>=0))
    {
        valide = 1;
    }

    if((valide == 1) && (monde[i][j] != CHAT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


void deplacement_chat(int ***monde)
{
    //1-droite; 2-gauche; 3-haut; 4-bas; 5-bouge pas
    
    int i,j;
    int position = 0;
    
    for(i=0; i<HEIGHT; i++)
    {
        for(j=0; j<WIDTH; j++)
        {
            if(i == 0)
            {
                do{
                    position = 1 + (rand() % 4);
                }while(position == 2);
            }
            if(i == HEIGHT-1)
            {
                do{
                    position = 1 + (rand() % 4);
                }while(position == 3);
            }
            if(j == 0)
            {
                do{
                    position = 1 + (rand() % 4);
                }while(position == 1);
            }
            if(j == WIDTH-1)
            {
                do{
                    position = 1 + (rand() % 4);
                }while(position == 4);
            }
            if((i == 0) && (j == 0))
            {
                while((position == 2) || (position == 3))
                {
                    position = 1 + (rand() % 4);
                }
            }
            if((i == 0) && (j == WIDTH-1))
            {
                while((position == 1) || (position == 3))
                {
                    position = 1 + (rand() % 4);
                }
            }
            if((i == HEIGHT-1) && (j == 0))
            {
                while((position == 2) || (position == 4))
                {
                    position = 1 + (rand() % 4);
                }
            }
            if((i == HEIGHT-1) && (j == WIDTH-1))
            {
                while((position == 1) || (position == 4))
                {
                    position = 1 + (rand() % 4);
                }
            }
            
            if((i != 0) && (i != HEIGHT-1) && (j != 0) && (j != WIDTH-1))
            {
                position = 1 + (rand() % 4);
            }
            
            
            if(*(*(*monde + i)+j) == CHAT)
            {
                if((case_valide_chat(i, j+1, *monde) == 1) && (position == 1)) //droite
                {
                    *(*(*monde + i)+j) = CASE_VIDE;
                    *(*(*monde + i)+(j+1)) = NX_CHAT;
                }
                else if((case_valide_chat(i, j-1, *monde) == 1) && (position == 2)) //gauche
                {
                    *(*(*monde + i)+j) = CASE_VIDE;
                    *(*(*monde + i)+(j-1)) = NX_CHAT;
                }
                else if((case_valide_chat(i-1, j, *monde) == 1) && (position == 3)) //haut
                {
                    *(*(*monde + i)+j) = CASE_VIDE;
                    *(*(*monde + (i-1))+j) = NX_CHAT;
                }
                else if((case_valide_chat(i+1, j, *monde) == 1) && (position == 4)) //bas
                {
                    *(*(*monde + i)+j) = CASE_VIDE;
                    *(*(*monde + (i+1))+j) = NX_CHAT;
                }
            }
        }
    }
}


void reabilitation_valeur_chat(int ***monde)
{
    int i,j;
    
    for(i=0; i<HEIGHT; i++)
    {
        for(j=0; j<WIDTH; j++)
        {
            if(*(*(*monde + i)+j) == NX_CHAT)
            {
                *(*(*monde + i)+j) = CHAT;
            }
        }
    }
}
