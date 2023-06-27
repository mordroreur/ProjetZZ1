#ifndef RENDERING_UTIL_HEADER_
#define RENDERING_UTIL_HEADER_

#include "liste.h"
#include <SDL2/SDL.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <pthread.h>

typedef struct graph{
  int nbSommet;
  float ** arretes;
  int *Sommets[2];
  liste reso;
}graphe;


typedef struct Ecran{

  SDL_Window *window;
  SDL_Renderer *renderer;


  int isFullScreen;
  int sizeX;
  int sizeY;
  int otherX;
  int otherY;

  int etapeDuJeu;

  graphe niveau;

} ecran;



long int getTime();
void DrawString(char *s, float x, float y, float size, char center, int R, int G, int B, ecran *screen);
void InitImage();
void freeImageMalloc();
void DrawImage(int imagenb, float x, float y, float sizeX, float sizeY, char center, int etatPremier, float TimebeforeNext, int flip, int angle, int nbState, int* spriteOrder, ecran *screen);

#endif /* RENDERING_UTIL_HEADER_ */
