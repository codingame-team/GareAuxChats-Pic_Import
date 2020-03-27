//
//  souris3.c
//  gare_aux_chats
//
//  Created by Philippe Mourey on 26/03/2020.
//  Copyright © 2020 Philippe Mourey. All rights reserved.
//

#include "../source/fonctions.h"
#include <math.h>

#define DISTANCE_COIN 3
#define DISTANCE_BORD 3

typedef struct Coordonnees position;
struct Coordonnees
{
    int x;
    int y;
};
typedef struct TableauChats TableauChats;
struct TableauChats
{
    position *chat1;
    position *chat2;
};

double calculDistance(position souris, position chat )
{
    return sqrt(pow(chat.x-souris.x,2)+pow(chat.y-souris.y,2));
}

position *positionSouris(int **monde, int idSouris)
{
    position *positionSouris;
    position pos;
    int i, j;

    positionSouris = malloc(sizeof(position));

    for(i=0; i<HEIGHT; i++)
    {
        for(j=0; j<WIDTH; j++)
        {
            if ( monde[i][j] == idSouris )
            {
                positionSouris->x = i;
                positionSouris->y = j;
                break;
            }
        }
    }
    pos = *positionSouris;

    return positionSouris;
}

TableauChats *positionChatsProche(int **monde, position *positionSouris)
{
    TableauChats *positionChatTab;
    //position *positionChatProche = NULL;
    //position *positionChatProcheOld = NULL;
    position *positionChat;
    int i, j;
    double distance, minDistance;

    positionChat = malloc(sizeof(position));
    positionChatTab = malloc(sizeof(TableauChats));

    positionChatTab->chat1 = NULL;
    positionChatTab->chat2 = NULL;

    minDistance = sqrt(pow(WIDTH,2)+pow(HEIGHT,2));

    for(i=0; i<HEIGHT; i++)
    {
        for(j=0; j<WIDTH; j++)
        {
            if ( monde[i][j] == CHAT )
            {
                if ( positionChatTab->chat1 == NULL ) // si il y a au moins un chat sur le plateau, on alloue la mémoire au pointeur
                    positionChatTab->chat1 = malloc(sizeof(position));
                positionChat->x = i;
                positionChat->y = j;
                distance = calculDistance(*positionSouris, *positionChat);
                if ( distance < minDistance )
                {
                    if ( positionChatTab->chat2 == NULL ) // si il y a au moins un chat sur le plateau, on alloue la mémoire au pointeur
                        positionChatTab->chat2 = malloc(sizeof(position));
                    minDistance = distance;
                    (positionChatTab->chat2)->x = (positionChatTab->chat1)->x;
                    (positionChatTab->chat2)->y = (positionChatTab->chat1)->y;
                    (positionChatTab->chat1)->x = positionChat->x;
                    (positionChatTab->chat1)->y = positionChat->y;
                }
            }
        }
    }

    free(positionChat);
    free(positionChatTab);

    //free(positionChatProche);
    //free(positionChatProcheOld);

    return positionChatTab;
}

int randomDirection (int direction1, int direction2)
{
    int randomInt = 1 + rand()%2;
    int direction;

    if ( randomInt == 1 )
        direction = direction1;
    else
        direction = direction2;

    return direction;
}

int randomTroisDirection (int direction1, int direction2, int direction3)
{
    int randomInt = 1 + rand()%3;
    int direction;

    if ( randomInt == 1 )
        direction = direction1;
    else if ( randomInt == 2 )
        direction = direction2;
    else
        direction = direction3;

    return direction;
}

/*
    But de la fonction: déterminer la meilleure direction en fonction des paramètres suivants:
    - position Souris par rapport aux bords de la grille: on essaye de s'en éloigner si pas de chats à proximité (sinon longer le bord pour leur échapper plus loin)
    - position des 2 chats les plus proches: on essaye de s'éloigner des chats les plus menaçants pour ne pas se faire encercler.
      Pour affiner l'algorithme, on pourrait déterminer des zones à risques (densité de chats) par quadrant
*/

int calculDirection (position *pSouris, TableauChats *pChatTab, int direction1, int direction2)
{
    double distance_bord_haut, distance_bord_droit, distance_bord_bas, distance_bord_gauche;
    int randomInt = 1 + rand()%2;
    int direction;
    double distance_chat1_souris, distance_chat2_souris;
    position *pChat1, *pChat2;

    distance_bord_haut = pSouris->x;
    distance_bord_droit = HEIGHT - pSouris->y;
    distance_bord_bas = WIDTH - pSouris->x;
    distance_bord_gauche = pSouris->y;

    pChat1 = pChatTab->chat1;
    pChat2 = pChatTab->chat2;
    distance_chat1_souris = calculDistance(*pSouris, *pChat1);
    distance_chat2_souris = calculDistance(*pSouris, *pChat2);

    // Si pas de chat à proximité, on s'éloigne des bords
    if  ( distance_chat1_souris > 2)
    {
        if ( distance_bord_haut <= DISTANCE_BORD )
        {
            if ( direction1 == UP)
            {
                if ( direction2 != 0 )
                    direction = direction2;
                else
                    direction = randomTroisDirection(LEFT,RIGHT,DOWN); // cas où la souris a déjà été coincée sur un bord... on essaye de la faire sortir!
                //direction = DOWN; // cas où la souris a déjà été coincée sur un bord... on essaye de la faire sortir!
            }
            else if ( direction2 == UP )
                direction = direction1;
        }
        else if ( distance_bord_droit <= DISTANCE_BORD )
        {
            if ( direction1 == DOWN )
            {
                if ( direction2 != 0 )
                    direction = direction2;
                else
                    direction = randomTroisDirection(LEFT,RIGHT,UP); // cas où la souris a déjà été coincée sur un bord... on essaye de la faire sortir!
                //direction = UP; // cas où la souris a déjà été coincée sur un bord... on essaye de la faire sortir!
            }
            else if ( direction2 == DOWN )
                direction = direction1;
        }
        else if ( distance_bord_bas <= DISTANCE_BORD )
        {
            if ( direction1 == RIGHT )
            {
                if ( direction2 != 0 )
                    direction = direction2;
                else
                    direction = randomTroisDirection(LEFT,DOWN,UP); // cas où la souris a déjà été coincée sur un bord... on essaye de la faire sortir!
                //direction = LEFT; // cas où la souris a déjà été coincée sur un bord... on essaye de la faire sortir!
            }
            else if ( direction2 == RIGHT )
                direction = direction1;
        }
        else if ( distance_bord_gauche <= DISTANCE_BORD )
        {
            if ( direction1 == LEFT )
            {
                if ( direction2 != 0 )
                    direction = direction2;
                else
                    direction = randomTroisDirection(DOWN,RIGHT,UP); // cas où la souris a déjà été coincée sur un bord... on essaye de la faire sortir!
                //direction = RIGHT; // cas où la souris a déjà été coincée sur un bord... on essaye de la faire sortir!
            }
            else if ( direction2 == LEFT )
                direction = direction1;
        }
        else
        {
            if ( direction2 == 0 )
                direction = direction1;
            else
            {
                if ( randomInt == 1 )
                    direction = direction1;
                else
                    direction = direction2;
            }
        }
    }
    // Si au moins un chat est à proximité
    else
    {
        // si la souris est sur un bord et entourée par 2 chats menaçants, alors elle quitte le bord, si seulement un chat menaçant, elle continue à longer le bord...
        if ( distance_chat1_souris <= 2)
        {
            if ( distance_bord_haut == 0 && pChat1->x == 0 && pChat2->x == 0 )
            {
                if ( distance_chat2_souris <= 3 )
                    direction = DOWN;
                else
                {
                    if ( pSouris->y < pChat2->y && pSouris->y > pChat1->y )    // C1--S----C2
                        direction = RIGHT;
                    else
                        direction = LEFT;
                }
            }
            else if ( distance_bord_droit == 0 && pChat1->y == WIDTH-1 && pChat2->y == WIDTH-1 )
            {
                if ( distance_chat2_souris <= 3 )
                    direction = LEFT;
                else
                {
                    if ( pSouris->x < pChat2->x && pSouris->x > pChat1->x )    // C1--S----C2
                        direction = DOWN;
                    else
                        direction = UP;
                }
            }
            else if ( distance_bord_bas == 0 && pChat1->x == HEIGHT-1 && pChat2->x ==  HEIGHT-1 )
            {
                if ( distance_chat2_souris <= 3 )
                    direction = UP;
                else
                {
                    if ( pSouris->y < pChat2->y && pSouris->y > pChat1->y )    // C1--S----C2
                        direction = RIGHT;
                    else
                        direction = LEFT;
                }
            }
            else if ( distance_bord_gauche == 0 && pChat1->y == 0 && pChat2->y == 0 )
            {
                if ( distance_chat2_souris <= 3 )
                    direction = RIGHT;
                else
                {
                    if ( pSouris->x < pChat2->x && pSouris->x > pChat1->x )    // C1--S----C2
                        direction = DOWN;
                    else
                        direction = UP;
                }
            }
        }
        else
        {
            if ( direction2 == 0 )
                direction = direction1;
            else
            {
                if ( randomInt == 1 )
                    direction = direction1;
                else
                    direction = direction2;
            }
        }
    }
    return direction;
}

int fuireCoins(position *pSouris)
{
    int direction;
    position coinQ1, coinQ2, coinQ3, coinQ4;
    double d1, d2, d3, d4;

    coinQ1.x = 0;
    coinQ1.y = 0;
    coinQ2.x = 0;
    coinQ2.y = WIDTH-1;
    coinQ3.x = HEIGHT-1;
    coinQ3.y = WIDTH-1;
    coinQ4.x = HEIGHT-1;
    coinQ4.y = 0;

    d1 = calculDistance(*pSouris, coinQ1);
    d2 = calculDistance(*pSouris, coinQ2);
    d3 = calculDistance(*pSouris, coinQ3);
    d4 = calculDistance(*pSouris, coinQ4);

    if ( d1 <= DISTANCE_COIN )
        direction = randomDirection(DOWN,RIGHT);
    else if ( d2 <= DISTANCE_COIN )
        direction = randomDirection(LEFT,DOWN);
    else if ( d3 <= DISTANCE_COIN )
        direction = randomDirection(LEFT,UP);
    else if ( d4 <= DISTANCE_COIN )
        direction = randomDirection(UP,RIGHT);
    else
        direction = SPOT;

    return direction;
}

/*  Voici mes instructions de survie:
    - Eviter absolument les coins (voies de repli divisé par 2!) quelles que soient les menaces à proximité
    - Si pas de chats trop menaçants, s'éloigner le plus possible des bords (voies de repli diminuant de 25%!)
    - Sinon se déplacer en direction opposé du chat le plus proche
    - Si la souris se retrouve coincée entre 2 chats menaçants sur un bord, quitter le bord



        0 -------------------------> Y (WIDTH)
        |
        | (X1,Y1)---(X1,y)------(X1,Y2)
        |   |   Q1    |     Q2     |
        |   |         |            |
        | (x,Y1)----(x,y)-------(x,Y2)
        |   |         |            |
        |   |   Q4    |     Q3     |
        | (X2,Y1)---(X2,y)------(X2,Y2)
        v
(HEIGHT) X
*/

int souris3(int **monde)
{
    int i, j;
    int x, y, X, Y;
    position *pChat, *pChat2, *pSouris, pCat, pCat2;
    int mouvement, directionFuite;
    TableauChats *positionChatTab;

    pSouris = positionSouris(monde, SOURIS3);
    positionChatTab = positionChatsProche(monde, pSouris);
    pChat = positionChatTab->chat1;
    pChat2 = positionChatTab->chat2;

    directionFuite = fuireCoins(pSouris);
    if ( directionFuite != SPOT ) // on vérifie d'abord si la souris n'est pas proche d'un bord...
        mouvement = directionFuite;
    else
    {
        if ( pChat != NULL ) // s'il y a au moins un chat sur le plateau
        {
            pCat = *pChat;
            pCat2 = *pChat2;
            x = pSouris->x;
            y = pSouris->y;
            X = pChat->x;
            Y = pChat->y;

            if ( x > X && y > Y ) // Quadrant n°1 (Nord/Ouest)
                mouvement = calculDirection(pSouris,positionChatTab,DOWN,RIGHT);
            else if ( x > X && y < Y ) // Quadrant n°2 (Nord/Est)
                mouvement = calculDirection(pSouris,positionChatTab,DOWN,LEFT);
            else if ( x < X && y < Y ) // Quadrant n°3 (Sud-Est)
                mouvement = calculDirection(pSouris,positionChatTab,UP,LEFT);
            else if ( x < X && y > Y ) // Quadrant n°4 (Sud-Ouest)
                mouvement = calculDirection(pSouris,positionChatTab,UP,RIGHT);
            else if ( x == X )
            {
                if ( y < Y )
                    mouvement = calculDirection(pSouris,positionChatTab,LEFT,0);
                else
                    mouvement = calculDirection(pSouris,positionChatTab,RIGHT,0);
            }
            else if ( y == Y )
            {
                if ( x < X )
                    mouvement = calculDirection(pSouris,positionChatTab,UP,0);
                else
                    mouvement = calculDirection(pSouris,positionChatTab,DOWN,0);
            }
            else
                mouvement = SPOT; // là ma souris est très mal et il est déjà trop tard... (pSouris == pChat) :-DDDDD
        }
        else
            mouvement = SPOT;
    }

    free(pChat);
    free(pChat2);
    free(pSouris);

    return mouvement;
}
