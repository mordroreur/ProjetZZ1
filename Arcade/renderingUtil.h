#ifndef RENDERING_UTIL_HEADER_
#define RENDERING_UTIL_HEADER_

#include <SDL2/SDL.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


typedef struct Rect{
  float x;
  float y;
  float w;
  float h;
}frect;

typedef struct boule
{
  int vie;
  frect pos;
  int speed;
  int vitX;
  int vitY;
} boule;

typedef struct player
{

  int input[5];
  frect pos;
  float vitesse;
  
  int kill;
  int mort;
  int maxBouleVie;
  int vie;

  int nbBoule;
  boule* boubou;
  int dirX;
  int dirY;

  int equipe;
  
  int index;
  int debBoule;
  int nbBouleActive;
  int shoot;
  
} player;


typedef struct objet{
  int id;
  SDL_Rect pos;
}objet;

typedef struct Ecran{

  SDL_Window *window;
  SDL_Renderer *renderer;


  int isFullScreen;
  int sizeX;
  int sizeY;
  int otherX;
  int otherY;

  int etapeDuJeu;

  int whichBack;
  
  player *pla;
  
  int nbObjetsMax;
  objet* tbObjet;

  int modePlay;
  int maxBoule;
  int maxVie;
  int nbPlayer;
  
  
}ecran;

/*player * newPlayer(char * name, int xPos, int yPos, int vitesse)
{
    player * p = (player*) malloc(sizeof(player));
    p->x = xPos;
    p->y = yPos;
    p->pioche = 0;
    p->mur = 0;
    p->vitesse = vitesse;
    p->coffre = 0;
    p->nbrLingo = 0;
    p->kill = 0;
    p->mort = 0;
    sprintf(p->nom, name);
    return p;
}*/

long int getTime();
void DrawString(char *s, float x, float y, float size, char center, int R, int G, int B, ecran *screen);
void InitImage();
void freeImageMalloc();
void DrawImage(int imagenb, float x, float y, float sizeX, float sizeY, char center, int etatPremier, float TimebeforeNext, int flip, int angle, int nbState, int* spriteOrder, ecran *screen);
int isInButton(float x, float y, float sizeX, float sizeY, char center, int posMX, int posMY, ecran *screen);


#endif /* RENDERING_UTIL_HEADER_ */
