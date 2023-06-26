#include "render.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

void mainRendering(ecran *screen){
  switch(screen->etapeDuJeu){
  case 1: loadingScreen(screen);break;
  case 2: DrawTer(screen);break;
  case 3: DrawTer(screen);break;
  default: loadingScreen(screen);break;
  }
}


void DrawTer(ecran *screen){
  SDL_SetRenderDrawColor(screen->renderer, 0, 200, 0, 0);
  SDL_RenderFillRect(screen->renderer, NULL);

  SDL_Rect rect;
  rect.h = ((float)(screen->sizeY) / screen->taille_Ter_y) * 0.9;
  rect.w = ((float)(screen->sizeX) / screen->taille_Ter_x) * 0.9;

  
  for(int i = 0; i < screen->taille_Ter_x; i++){
    for(int j = 0; j < screen->taille_Ter_y; j++){
      if(screen->Ter[i][j] == -1){
	SDL_SetRenderDrawColor(screen->renderer, 255, 0, 0, 0);
	rect.x = ((float)(screen->sizeX) / screen->taille_Ter_x)*i;
	rect.y = ((float)(screen->sizeY) / screen->taille_Ter_y)*j;
	SDL_RenderFillRect(screen->renderer, &rect);
      }else if (screen->Ter[i][j] == 1) {
	SDL_SetRenderDrawColor(screen->renderer, 0, 90, 0, 0);
	rect.x = ((float)(screen->sizeX) / screen->taille_Ter_x)*i;
	rect.y = ((float)(screen->sizeY) / screen->taille_Ter_y)*j;
	SDL_RenderFillRect(screen->renderer, &rect);
      }else if (screen->Ter[i][j] > 1) {
	SDL_SetRenderDrawColor(screen->renderer, 0, 130, 0, 0);
	rect.x = ((float)(screen->sizeX) / screen->taille_Ter_x)*i;
	rect.y = ((float)(screen->sizeY) / screen->taille_Ter_y)*j;
	SDL_RenderFillRect(screen->renderer, &rect);
      }
    }
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
