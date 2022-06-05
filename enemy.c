#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <time.h>
#include <SDL/SDL_ttf.h>
#include "enemy.h"
/** 
* @file enemy.c
* @brief Testing Program
* @author C Team
* @version 0.1
* @date Apr21 2022
*/
/**
* @file enemy.c
*/
/**
* @brief to initialize the enemy
* @param e for the enemy
* @return Nothing
*/

void initEnemy(enemy *e)
{
 srand(time(NULL));
 e->imgR=IMG_Load("all.png");
 e->dir=rand()%2;
 e->max=700;
 e->min=100;
 if(e->dir==0)
  {
    e->pos.x=200;
  }
 else 
  if(e->dir==1)
  {
   e->pos.x=700;
  }
  e->pos.y=470;
  e->rectangle=0;
  e->Mhp=15000;//23
  e->hp=e->Mhp;
  e->state=WAITING;
  e->folie=0;
  e->dep=1;
  //e->a=0;
}
/**
* @brief Pour afficher un ennemi selon sa position
* @param e for the ennemy
* @param screen pour l'ecran ou en affiche l'ennemi
* @return Nothing
*/
void displayEnemy(enemy e,SDL_Surface screen)
{
  if(e->dir==0)//left
 {
   if(e->folie==1)
   {SDL_BlitSurface(e->imgR,&e->carre2[e->rectangle],screen,&e->pos);}
   else
   if(e->folie==0)
   {SDL_BlitSurface(e->imgR,&e->carre[e->rectangle],screen,&e->pos);}
   SDL_Flip(screen);
   e->rectangle++;
   if (e->rectangle==4)
   e->rectangle=0;
 }
  if(e->dir==1)//right
 {
   if(e->folie==0)
   {SDL_BlitSurface(e->imgR,&e->carre1[e->rectangle],screen,&e->pos);} 
   else
   if(e->folie==1)
   {SDL_BlitSurface(e->imgR,&e->carre3[e->rectangle],screen,&e->pos);}
   SDL_Flip(screen);
   e->rectangle++;
   if (e->rectangle==4)
   e->rectangle=0;
 }
 SDL_Delay(50);
 }
/**
* @brief Animer le joueur:pour que la photo change de position lors d'un deplacement 
* @param e for the ennemy
* @return Nothing
*/
void animateX(enemy *e)
{
int c;
 for(c=0;c<4;c++)
 {
  e->carre[c].x=0+c*100;
  e->carre[c].y=0;
  e->carre[c].w=100;
  e->carre[c].h=100;
  e->carre1[c].x=0+c*100;
  e->carre1[c].y=100;
  e->carre1[c].w=100;
  e->carre1[c].h=100;
  e->carre2[c].x=0+c*100;
  e->carre2[c].y=200;
  e->carre2[c].w=100;
  e->carre2[c].h=100;
  e->carre3[c].x=0+c*100;
  e->carre3[c].y=300;
  e->carre3[c].w=100;
  e->carre3[c].h=100;
 }
}
/**
* @brief Pour que l'ennemi  ne reste pas stable sans se deplacer 
* @param e for the ennemy
* @return Nothing
*/
void moveEnnemyX(enemy *e)
{
 if (e->dep==1)
 {if (e->pos.x>e->max)
 {
  e->dir=1;
 }
  if (e->pos.x<e->min)
 {
  e->dir=0;
 }
 if(e->dir==0)
 {
 e->pos.x=e->pos.x+10;
 }
 else if (e->dir==1)
 {
 e->pos.x=e->pos.x-10;
 }
 }
}
/**
* @brief detecter un contact entre l'ennnemi et le personnage 
* @param e for the ennemy
* @return entier{0,1}
*/
int collisionBB(personne p,enemy e)
{
 if ((p.psObstacle.x+p.psObstacle.w<=e.pos.x)||(p.psObstacle.x>=e.pos.x+e.pos.w)||(p.psObstacle.y+p.psObstacle.h<=e.pos.y)||(p.psObstacle.y>=e.pos.y+e.pos.h))
 {
 return 0;
 }
 else 
 {
 return 1;
 }
}

void updateEnnemiState (enemy* e,int dist)
{
switch(e->state)
{
case WAITING:
if(dist<100 && dist>50)
{e->state=FOLLOWING;}
else if (dist>100)
{e->state=WAITING;}
break;
case FOLLOWING:
if (dist<50)
{e->state=ATTACKING;}
else if (dist>100)
{e->state=WAITING;}
else if(dist<100 && dist>50)
{e->state=FOLLOWING;}
break;

case ATTACKING:
if(dist<100 && dist>50)
{e->state=FOLLOWING;}
else 
if(dist>100)
{e->state=WAITING;}
else 
if (dist<50)
{e->state=ATTACKING;}
break;
}
}
void accelerer(enemy *e)
{

 if (e->pos.x>e->max )
 {
  e->dir=1;
 }
  if (e->pos.x<e->min )
 {
  e->dir=0;
 }
 if(e->dir==0)
 {
 e->pos.x=e->pos.x+15;
 }
 else if (e->dir==1)
 {
 e->pos.x=e->pos.x-15;
 }
 
}
void mouvement(enemy* e,SDL_Rect posPerso)
{
int largeur;
largeur=180;
if(e->pos.x==posPerso.x-50)
{e->dir=1;}
if(e->pos.x==posPerso.x+largeur+20)
{e->dir=0;}
if(e->dir==0)
{
e->pos.x=e->pos.x+5;
}
else 
if(e->dir==1)
{e->pos.x=e->pos.x-5;}
}
void moveIA(enemy *e,SDL_Rect posPerso)
{
 int dist;
 dist=e->pos.x-(posPerso.x+posPerso.w/2);
 if(e->state==ATTACKING)
 {
  e->min=posPerso.x;
  e->max=posPerso.x+180;
 }
  if(dist<0)
  {dist=-dist;}
 updateEnnemiState(&(*e),dist);
}
