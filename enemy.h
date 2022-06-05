/** 
* @file enemy.h
* @brief Testing Program
* @author C Team
* @version 0.1
* @date Apr21 2022
*/
/**
* @struct personne
* @brief struct sur le personnage principale du jeu
*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>
typedef enum STATE STATE;
enum STATE{WAITING,FOLLOWING,ATTACKING,ESCAPING};
typedef struct 
{
SDL_Rect psObstacle;
SDL_Surface *obstacle;
}personne;
/**
* @struct enemy
* @brief struct pour  enemy
*/
typedef struct 
{
SDL_Rect pos;/*!< current positon*/
SDL_Surface *imgR;
SDL_Surface *imgL;
//int marge;
int hp;
int Mhp;
int dir;
int max;
int min;
int dep;
int rectangle;
SDL_Rect carre[6];
SDL_Rect carre1[6];
SDL_Rect carre2[6];
SDL_Rect carre3[6];
STATE state;
int folie;
}enemy;
void initEnemy(enemy *e);
void displayEnemy(enemy e,SDL_Surface screen);
void animateX(enemy *e);
void moveEnnemyX(enemy *e);
int collisionBB(personne p,enemy e);
void updateEnnemiState (enemy* e,int dist);
void accelerer(enemy *e);
void mouvement(enemy* e,SDL_Rect posPerso);
void displayAttack(enemy *e,SDL_Rect posPerso);
void moveIA(enemy *e,SDL_Rect posPerso);
