#ifndef RENDERING_UTIL_HEADER_
#define RENDERING_UTIL_HEADER_

#include <SDL2/SDL.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define WAITTIME 30

typedef struct Ecran{

  SDL_Window *window;
  SDL_Renderer *renderer;


  int isFullScreen;
  int sizeX;
  int sizeY;
  int otherX;
  int otherY;

  int etapeDuJeu;

  int taille_Ter_x;
  int taille_Ter_y;
  int tailleSerp;
  int **Ter;
  int serpX;
  int serpY;
  int lastDep;
  int serpDir;

  int time;
  
}ecran;


long int getTime();
void DrawString(char *s, float x, float y, float size, char center, int R, int G, int B, ecran *screen);
void InitImage();
void freeImageMalloc();
void DrawImage(int imagenb, float x, float y, float sizeX, float sizeY, char center, int etatPremier, float TimebeforeNext, int flip, int angle, ecran *screen);

#endif /* RENDERING_UTIL_HEADER_ */
