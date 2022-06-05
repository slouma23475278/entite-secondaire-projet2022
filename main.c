/** 
* @file main.c
* @brief Testing Program
* @author C Team
* @version 0.1
* @date Apr21 2022
* @param argc argv 
* @return 0
*/
/*



Remarque 
general,general1,general2
les 3 fichiers .wav 
+
music 
n existent pas donc vous pouver installer vous meme 
des chansons de votre choix 
pour le wav vous puver tt simplement prendre une chanson de youtube
et la convertir 



*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "enemy.h"
int main(int argc,char** argv)
{
int c1=0,dist;
personne p;
enemy e;
SDL_Surface *screen=NULL,*image=NULL;
SDL_Rect position;
Mix_Music *music,*music1,*music2;
//Mix_Chunk* son0;
Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
music=Mix_LoadMUS("general.mp3");
music1=Mix_LoadMUS("general1.mp3");
music2=Mix_LoadMUS("general2.mp3");
//son0=Mix_LoadWAV("death0.wav");
int c=0;
position.x=0;
position.y=0;
p.psObstacle.x=100;
p.psObstacle.y=350;
p.psObstacle.h=180;
p.psObstacle.w=200;
SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER);
screen=SDL_SetVideoMode(800,600,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
if(screen==NULL)
{
printf("un probleme au niveau de l'ecran %s \n",SDL_GetError());
}
initEnemy(&e);
image=IMG_Load("bg.png");
p.obstacle=IMG_Load("o.png");
animateX(&e);
Mix_PlayMusic(music,-1);
while(c==0)
{
SDL_BlitSurface(image,NULL,screen,&position);
SDL_BlitSurface(p.obstacle,NULL,screen,&p.psObstacle);
p.psObstacle.x=p.psObstacle.x+5;
if(p.psObstacle.x>600)
 p.psObstacle.x=p.psObstacle.x-5;
if(e.state==WAITING)
{
e.folie=0;
moveEnnemyX(&e);
moveIA(&e,p.psObstacle);//perso
displayEnemy(&e,screen);
}
else if(e.state==FOLLOWING)
{
e.folie=0;
moveEnnemyX(&e);
moveIA(&e,p.psObstacle);//perso
displayEnemy(&e,screen);
}
else if(e.state==ATTACKING)
{
printf("*");
e.folie=1;
//accelerer(&e);
moveIA(&e,p.psObstacle);//perso
displayEnemy(&e,screen);
}
SDL_Flip(screen);
c=collisionBB(p,e);
if (c==1)
{
 if (e.hp!=0)
 { 
 e.hp--;
 c=0;
 }
 }

SDL_Event event;
while(SDL_PollEvent(&event))
{
switch(event.type)
{
case SDL_KEYDOWN:
switch(event.key.keysym.sym)
{
case SDLK_a:
Mix_PauseMusic();
Mix_PlayMusic(music,-1);
break;
case SDLK_z:
Mix_PauseMusic();
Mix_PlayMusic(music1,-1);
break;
case SDLK_e:
Mix_PauseMusic();
Mix_PlayMusic(music2,-1);
break;
case  SDLK_ESCAPE:
c=1;
c1=1;
break;
}
break;
}
}

}

Mix_PauseMusic();
Mix_Chunk* son;
if(c1==0)
{
son=Mix_LoadWAV("death.wav");
Mix_PlayChannel(-1,son,0);
SDL_Delay(3000);
}

Mix_FreeMusic(music);
Mix_FreeMusic(music1);
Mix_FreeMusic(music2);
Mix_FreeChunk(son);
SDL_FreeSurface(image);
SDL_FreeSurface(e.imgR);
SDL_FreeSurface(p.obstacle);
Mix_CloseAudio();
SDL_Quit();
return 0;
}
