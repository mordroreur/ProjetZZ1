#include "render.h"

void mainRendering(ecran *screen){
  switch(screen->etapeDuJeu){
  case 1: loadingScreen(screen);break;
  case 2: DrawMenu(screen);break;
  default: loadingScreen(screen);break;
  }
}


void DrawMenu(ecran *screen){
  int posMX, posMY;
  //  int nbT = SDL_GetTicks()/500;
  SDL_GetMouseState(&posMX, &posMY);

  SDL_SetRenderDrawColor(screen->renderer, 255, 255, 255, 0);
  SDL_RenderFillRect(screen->renderer, NULL);
  SDL_Rect rect;
  
  
  if(isInButton(25, 50, 50, 100, 'c', posMX, posMY, screen)){
    SDL_SetRenderDrawColor(screen->renderer, 0, 255, 0, 0);
    rect.x = 0;
    rect.y = 0;
    rect.w = screen->sizeX/2;
    rect.y = screen->sizeY;
    SDL_RenderFillRect(screen->renderer, &rect);
    DrawString("HOST", 25, 25, 10, 'c', 0, 0, 0, screen);
  }else if(isInButton(75, 50, 50, 100, 'c', posMX, posMY, screen)){
    SDL_SetRenderDrawColor(screen->renderer, 0, 0, 255, 0);
    rect.x = screen->sizeX/2;
    rect.y = 0;
    rect.w = screen->sizeX;
    rect.y = screen->sizeY;
    SDL_RenderFillRect(screen->renderer, &rect);
    DrawString("JOIN", 75, 25, 10, 'c', 0, 0, 0, screen);
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
