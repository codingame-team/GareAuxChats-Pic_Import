//
//  fonctions.h
//  gare_aux_chats
//
//  Created by Pierrick Delrieu on 18/03/2020.
//  Copyright © 2020 Pierrick Delrieu. All rights reserved.
//

#ifndef fonctions_h
#define fonctions_h

//PLAYER
void position_initial_souris(int ***monde, int position_joueur1[2], int position_joueur2[2],int position_joueur3[2],int position_joueur4[2],int position_joueur5[2]);
int souris1(int **monde);
int souris2(int **monde);
int souris3(int **monde);
int souris4(int **monde);
int souris5(int **monde);




#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> //pour le sleep

//MONDE
#define HEIGHT 20 //hauteur (ligne)
#define WIDTH 20 //largeur (colonne)

#define CASE_VIDE 0
#define CHAT 6
int ** creation_monde_vide(int hauteur, int largeur);
void affichage_monde(int **monde);
void supr_console(void);
void desalocation_monde(int **monde);
int condition_arret_partie(int **monde);




//CHATS
#define NX_CHAT 7
void random_ajout_chat(int ***monde);
int case_valide_chat(int i, int j, int **monde);
void deplacement_chat(int ***monde);
void reabilitation_valeur_chat(int ***monde);


//SOURIS
#define NOMBRE_DE_SOURIS 5
#define SOURIS1 1
#define SOURIS2 2
#define SOURIS3 3
#define SOURIS4 4
#define SOURIS5 5

int case_valide_souris(int i, int j, int **monde);
void position_souris(int **monde, int souris, int position[2]);
void deplacement_souris(int ***monde, int souris, int position [2], int mouvement);
int condition_vie_souris(int ***monde, int souris, int position_joueur[2]);


//Deplacement
#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define SPOT 5






#endif /* fonctions_h */
