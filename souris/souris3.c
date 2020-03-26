//
//  souris3.c
//  gare_aux_chats
//
//  Created by Philippe Mourey on 26/03/2020.
//  Copyright © 2020 Philippe Mourey. All rights reserved.
//

#include "../source/fonctions.h"
#include <math.h>

typedef struct Coordonnees position;
struct Coordonnees
{
    int x;
    int y;
};

double calculDistance(position souris, position chat )
{
    return sqrt((chat.x-souris.x)^2+(chat.y-souris.y)^2);
}

position *positionSouris(int **monde, int idSouris)
{
    position *positionSouris, pos;
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

position *positionChatProche(int **monde, position *positionSouris)
{
    position *positionChat, *positionChatProche = NULL;
    int i, j;
    double distance, minDistance;

    positionChat = malloc(sizeof(position));

    minDistance = sqrt(WIDTH^2+HEIGHT^2);

    for(i=0; i<HEIGHT; i++)
    {
        for(j=0; j<WIDTH; j++)
        {
            if ( monde[i][j] == CHAT )
            {
                if ( positionChatProche == NULL ) // si il y a au moins un chat sur le plateau, on alloue la mémoire au pointeur
                    positionChatProche = malloc(sizeof(position));
                positionChat->x = i;
                positionChat->y = j;
                distance = calculDistance(*positionSouris, *positionChat);
                if ( distance < minDistance )
                {

                    minDistance = distance;
                    positionChatProche->x = positionChat->x;
                    positionChatProche->y = positionChat->y;
                }
            }
        }
    }

    free(positionChat);

    return positionChatProche;
}

int fuireBords(position *pSouris)
{
    int direction;

    // Bord extérieur Quadrant Q1
    if ( pSouris->x == 0 && pSouris->y == 1 )
        direction = DOWN;
    else if ( pSouris->x == 1 && pSouris->y == 0 )
        direction = RIGHT;
    // Bord extérieur Quadrant Q2
    else if ( pSouris->x == 0 && pSouris->y == WIDTH-1 )
        direction = DOWN;
    else if ( pSouris->x == 1 && pSouris->y == WIDTH-1 )
        direction = LEFT;
    // Bord extérieur Quadrant Q3
    else if ( pSouris->x == HEIGHT-1 && pSouris->y == WIDTH-2 )
        direction = UP;
    else if ( pSouris->x == HEIGHT-2 && pSouris->y == WIDTH-1 )
        direction = LEFT;
     // Bord extérieur Quadrant Q4
    else if ( pSouris->x == HEIGHT-2 && pSouris->y == 0 )
        direction = RIGHT;
    else if ( pSouris->x == HEIGHT-1 && pSouris->y == 1 )
        direction = LEFT;
    else
        direction = SPOT;

    return direction;
}

    /*      0 -------------------------> Y (WIDTH)
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
    position *pChat, *pSouris;
    int mouvement, directionFuiteBords;

    pSouris = positionSouris(monde, SOURIS3);
    pChat = positionChatProche(monde, pSouris);

    directionFuiteBords = fuireBords(pSouris);
    if (directionFuiteBords != SPOT )
        mouvement = directionFuiteBords;
    else
    {
        if ( pChat != NULL ) // s'il y a au moins un chat sur le plateau
        {
            x = pSouris->x;
            y = pSouris->y;
            X = pChat->x;
            Y = pChat->y;

            if ( x > X && y > Y ) // Quadrant n°1 (Nord/Ouest)
                {
                    if ( abs(X - x) > abs(Y - y) )
                        mouvement = DOWN;
                    else
                        mouvement = RIGHT;
                }
                else if ( x < X && y > Y ) // Quadrant n°2 (Nord/Est)
                {
                    if ( abs(X - x) > abs(Y - y) )
                        mouvement = LEFT;
                    else
                        mouvement = DOWN;
                }
                else if ( x < X && y < Y ) // Quadrant n°3 (Sud-Est)
                {
                    if ( abs(X - x) > abs(Y - y) )
                        mouvement = UP;
                    else
                        mouvement = LEFT;
                }
                else if ( x < X && y > Y ) // Quadrant n°4 (Sud-Ouest)
                {
                    if ( abs(X - x) > abs(Y - y) )
                        mouvement = UP;
                    else
                        mouvement = RIGHT;
                }
                else if ( x == X )
                {
                    if ( y < Y )
                        mouvement = LEFT;
                    else
                        mouvement = RIGHT;
                }
                else if ( y == Y )
                {
                    if ( x < X )
                        mouvement = UP;
                    else
                        mouvement = DOWN;
                }
                else
                    mouvement = SPOT; // là ma souris est très mal et il est déjà trop tard... (pSouris == pChat) :-DDDDD
        }
        else
            mouvement = SPOT;
    }

    free(pChat);
    free(pSouris);

    return mouvement;
}
