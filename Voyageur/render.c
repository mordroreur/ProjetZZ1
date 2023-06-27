#include "render.h"

void mainRendering(ecran *screen){
  switch(screen->etapeDuJeu){
  case 1: loadingScreen(screen);break;
  case 2: drawMenu(screen); break;
  default: loadingScreen(screen);break;
  }
}

void drawMenu(ecran *screen)
{
  
int posMX, posMY;
SDL_GetMouseState(&posMX, &posMY);
  
  DrawString("Voyageur", 50, 10, 25, 'c', 64, 64, 64, screen);
  DrawString("voyage, voyage...", 50, 27, 10, 'c', 64, 64, 64, screen);
  DrawImage(1, 50, 75, 30, 20, 'c', 0, 0, 0, 0, 0, 0, screen);
  DrawImage(2, 10, 90, 7, 7, 'c', 0, 0, 0, 0, 0, 0, screen);

  if (isInButton(50, 50, 30, 20, 'c', posMX, posMY, screen))
  {
    DrawImage(0, 50, 50, 35, 25, 'c', 0, 0, 0, 0, 0, 0, screen);
    printf("OUI\n");
  } else {
    DrawImage(0, 50, 50, 30, 20, 'c', 0, 0, 0, 0, 0, 0, screen);
  }

}

void loadingScreen(ecran *screen){
  
  int nb3 = SDL_GetTicks()/10;
  int nb = (nb3) % 100 - 50;
  int nb2 = (nb3+35)% 98 - 49;
  nb3 = (nb3+65)% 96 - 48;

  
  SDL_SetRenderDrawColor(screen->renderer, 255, 255, 255, 0);
  SDL_RenderFillRect(screen->renderer, NULL);

  //DrawImage(0, 25, 25, 25, 25, 'n', 0, 0, 0, 0, screen);
  
  DrawString("Loading", 50, 50, 10, 'c', 0, 0, 0, screen);
  DrawString("                .", 50, 47.5 + abs(nb)/10.0, 10, 'c', 0, 0, 0, screen);
  DrawString("                  .", 50, 47.5 + abs(nb2)/10.0, 10, 'c', 0, 0, 0, screen);
  DrawString("                    .", 50, 47.5 + abs(nb3)/10.0, 10, 'c', 0, 0, 0, screen);

  //DrawImage(int imagenb, float x, float y, float sizeX, float sizeY, char center, int etatPremier, float TimebeforeNext, int flip, int angle, ecran *screen)
}

int isInButton(int x, int y, int sizeX, int sizeY, char center, int posMX, int posMY, ecran *screen)
{

  if(center == 'c'){
    if(posMX < screen->sizeX*(x+sizeX/2) && posMX > screen->sizeX*(x-sizeX/2) && posMY < screen->sizeY*(y+sizeY/2) && posMY > screen->sizeY*(y-sizeY/2)){
      return 1;
    }
    return 0;
  }
  return 0;
}
