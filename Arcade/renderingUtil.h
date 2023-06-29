#ifndef RENDERING_UTIL_HEADER_
#define RENDERING_UTIL_HEADER_

#include <SDL2/SDL.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

typedef struct Ecran{

  SDL_Window *window;
  SDL_Renderer *renderer;


  int isFullScreen;
  int sizeX;
  int sizeY;
  int otherX;
  int otherY;

  int etapeDuJeu;
  
}ecran;

typedef struct player
{
    int x;
    int y;
    int pioche;
    int mur;
    int vitesse;
    int coffre;
    int nbrLingo;
    int kill;
    int mort;
    char nom[20];
} player;

typedef struct laby
{
    int size;
    int ** ter;
} laby;

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
